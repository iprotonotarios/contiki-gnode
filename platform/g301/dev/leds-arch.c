/*
 * Copyright (c) 2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Configurable Sensor Network Application
 * Architecture for sensor nodes running the Contiki operating system.
 *
 * Copyright (c) 2012, TNO Technical Sciences
 * Author: Goncalo Bernardo (goncalobernardo@gmail.com)
 * Modifications: Allow for LEDS connected in pins from different ports
 *
 * $Id: leds-arch.c,v 1.1 2006/06/17 22:41:21 adamdunkels Exp $
 *
 * -----------------------------------------------------------------
 *
 * Author  : Adam Dunkels, Joakim Eriksson, Niclas Finne
 * Created : 2005-11-03
 * Updated : $Date: 2006/06/17 22:41:21 $
 *           $Revision: 1.1 $
 */

#include "contiki.h"
#ifdef __IAR_SYSTEMS_ICC__
#include <msp430.h>
#else
#include <io.h>
#endif

#include "dev/leds.h"

/*---------------------------------------------------------------------------*/
void
leds_arch_init(void)
{
  //LEDS_PxDIR |= (LEDS_CONF_RED | LEDS_CONF_GREEN | LEDS_CONF_YELLOW);
  //LEDS_PxOUT |= (LEDS_CONF_RED | LEDS_CONF_GREEN | LEDS_CONF_YELLOW);
  LED_R_PxDIR |= BV(LED_R_PIN);
  LED_Y_PxDIR |= BV(LED_Y_PIN);
  LED_G_PxDIR |= BV(LED_G_PIN);
  LED_R_PxOUT &= ~BV(LED_R_PIN);
  LED_Y_PxOUT &= ~BV(LED_Y_PIN);
  LED_G_PxOUT &= ~BV(LED_G_PIN);
}
/*---------------------------------------------------------------------------*/
unsigned char
leds_arch_get(void)
{
  //return ((LEDS_PxOUT & LEDS_CONF_RED) ? 0 : LEDS_RED)
  //  | ((LEDS_PxOUT & LEDS_CONF_GREEN) ? 0 : LEDS_GREEN)
  //  | ((LEDS_PxOUT & LEDS_CONF_YELLOW) ? 0 : LEDS_YELLOW);
  return ((LED_R_PxOUT & BV(LED_R_PIN)) ? BV(LED_R_PIN) : 0)
    | ((LED_Y_PxOUT & BV(LED_Y_PIN)) ? BV(LED_Y_PIN) : 0)
    | ((LED_G_PxOUT & BV(LED_G_PIN)) ? BV(LED_G_PIN) : 0);
}
/*---------------------------------------------------------------------------*/
void
leds_arch_set(unsigned char leds)
{
  //LEDS_PxOUT = (LEDS_PxOUT & ~(LEDS_CONF_RED|LEDS_CONF_GREEN|LEDS_CONF_YELLOW))
  //  | ((leds & LEDS_RED) ? 0 : LEDS_CONF_RED)
  //  | ((leds & LEDS_GREEN) ? 0 : LEDS_CONF_GREEN)
  //  | ((leds & LEDS_YELLOW) ? 0 : LEDS_CONF_YELLOW);
  LED_R_PxOUT = (LED_R_PxOUT & ~BV(LED_R_PIN)) | ((leds & LEDS_RED)? BV(LED_R_PIN) : 0);
  LED_Y_PxOUT = (LED_Y_PxOUT & ~BV(LED_Y_PIN)) | ((leds & LEDS_YELLOW)? BV(LED_Y_PIN) : 0);
  LED_G_PxOUT = (LED_G_PxOUT & ~BV(LED_G_PIN)) | ((leds & LEDS_GREEN)? BV(LED_G_PIN) : 0);
}
/*---------------------------------------------------------------------------*/
