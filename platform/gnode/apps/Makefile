CONTIKI=../../..

TARGET=gnode
include $(CONTIKI)/Makefile.include

upload:
	lnode-bsl --invert-sda --invert-scl -c /dev/ttyUSB0 -e
	lnode-bsl --invert-sda --invert-scl -c /dev/ttyUSB0 -p blink.gnode
	lnode-bsl --invert-sda --invert-scl -c /dev/ttyUSB0 -r
      
