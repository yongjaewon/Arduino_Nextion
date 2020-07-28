/**
 * @example CompWaveform.ino
 *
 * @par How to Use
 * Show how to use API of class NexWaveform with auto scaling.  
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/8/11
 * @author Jyrki Berg 7/28/2020 (https://github.com/jyberg)
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * @copyright 2020 Jyrki Berg
 * 
 */ 

#include <SoftwareSerial.h>

#include "Nextion.h"

#ifdef ESP8266
// esp8266 / NodeMCU software serial ports
SoftwareSerial mySerial(D2, D1); // RX, TX
#else
SoftwareSerial mySerial(3,2); // RX, TX
#endif

#define LEVEL_HIGH  180
#define LEVEL_LOW   -150

#define CH0_OFFSET  (40 - LEVEL_HIGH/2)
#define CH1_OFFSET  (CH0_OFFSET + 40 * 1)
#define CH2_OFFSET  (CH0_OFFSET + 40 * 2)
#define CH3_OFFSET  (CH0_OFFSET + 40 * 3)


/*
* Declare Nextion instance
*/
Nextion *next = Nextion::GetInstance(mySerial); // software serial
//Nextion *next = Nextion::GetInstance(Serial); // HW serial


/*
 * Declare a main page object [nextion instance, page id:0, page name: "page0"]. 
 */
NexPage p0(next, 0, "page0");

/*
 * Declare a Waweform object [nextion instance, page id:0,component id:1, component name: "s0", optional page, low value,  max value, component high]. 
 */
NexWaveform s0 = NexWaveform(next, 0, 1, "s0", LEVEL_LOW-70, LEVEL_HIGH+100, 220, &p0);

static int16_t ch0_data = LEVEL_LOW;
static int16_t ch1_data = LEVEL_LOW;
static int16_t ch2_data = LEVEL_LOW;
static int16_t ch3_data = LEVEL_LOW;

void setup(void)
{
    // HW serial used for dobug messages
    Serial.begin(9600); 
    // Initialize Nextion connection wiht selected baud in this case 19200
    if(!next->nexInit(19200))
    {
        Serial.println("nextion init fails"); 
    }

     Serial.println("setup done");
}

void loop(void)
{
    delay(10);
    static uint32_t started = 0;
    if (millis() - started >= 2000)
    {
        started = millis();    
        if (LEVEL_HIGH == ch0_data)
        {
            ch0_data = LEVEL_LOW;
        }
        else
        {
            ch0_data = LEVEL_HIGH;
        }
    }
    
    ch1_data = ch0_data + random(0, 8);
    ch2_data = ch0_data + random(0, 13);
    ch3_data = ch0_data + random(0, 20);
    
    s0.addValue(0, CH0_OFFSET + ch0_data);
    s0.addValue(1, CH1_OFFSET + ch1_data);
    s0.addValue(2, CH2_OFFSET + ch2_data);
    s0.addValue(3, CH3_OFFSET + ch3_data);
    
}

