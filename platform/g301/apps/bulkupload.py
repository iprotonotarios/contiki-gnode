#!/usr/bin/env python

# Copyright (c) 2012, TNO Technical Sciences
# Author: Goncalo Bernardo (goncalobernardo@gmail.com)
# Useful for application bulkupload. All the sensors attached to USB ports get programmed in parallel
# Example usage: $./bulkupload blink

import os
import time
import sys
import glob
import subprocess
from threading import Thread

class uploader(Thread):
   def __init__ (self,port):
      Thread.__init__(self)
      self.port = port
   def run(self):
      os.popen("lnode-bsl --invert-sda --invert-scl -e -c"+self.port+" && sleep 2") # erase
      os.popen("lnode-bsl --invert-sda --invert-scl -c"+self.port+" -p tmpimage.ihex && sleep 2") # program
      os.popen("lnode-bsl --invert-sda --invert-scl -r -c"+self.port) # reset

##>> S C R I P T <<##

# Make target
args = sys.argv
if (len(args) != 2):
  print 'Specify target!'
  exit(0)
subprocess.call(['make',args[1]])
subprocess.call(['cp',args[1]+'.g301','tmpimage.ihex'])

# Bulk upload to all ttyUSB* devices
uploaderList = []
for port in glob.glob('/dev/ttyUSB*'):
   current = uploader(port)
   uploaderList.append(current)
   current.start()
for current in uploaderList:
   current.join()

sys.stdout.write('Programmed ' + str(len(uploaderList)) + ' nodes\n')
