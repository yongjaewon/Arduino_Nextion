/**
 * @example CompButton.ino
 * 
 * @par How to Use
 * This example shows that when the button component on the Nextion screen is released,
 * the text of this button will plus one every time.      
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/7/10
 * @updated 2016/12/25 bring HMI up to v0.32 to avoid too old issues
 * @convert by Patrick Martin, no other changes made
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
 * Declare a button object [nextion instance, page id:0,component id:1, component name: "b0", pointer to page object: &p0]. 
 */
NexButton b0( next, 0, 1, "b0", &p0);



/*
 * Register a button object to the touch event list.  
 */
NexTouch *nex_listen_list[] = 
{
    &b0,
    nullptr
};

char buffer[100] = {0};

/*
 * Button component pop callback function. 
 * In this example,the button's text value will plus one every time when it is released. 
 */
void b0PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    buffer[0]= 0;

    /* Get the text value of button component [the value is string type]. */
    len = sizeof(buffer);
    if(b0.getText(buffer, len ))
    {
        // increment button value
        number = atoi(buffer);
        number += 1;

        itoa(number, buffer, 10);

        /* Set the text value of button component [the value is string type]. */
        b0.setText(buffer);
    }    
}

void setup(void)
{   
    // HW serial used for dobug messages
    Serial.begin(9600);

    // Initialize Nextion connection wiht selected baud in this case 19200
    if(!next->nexInit(19200))
    {
        Serial.println("nextion init fails"); 
    }
    buffer[0]= 0;

    /* Register the pop event callback function of the current button component. */
    b0.attachPop(b0PopCallback);

    Serial.println("setup done"); 
}

void loop(void)
{   
    /*
     * When a pop or push event occured every time,
     * the corresponding component[right page id and component id] in touch event list will be asked.
     */
    next->nexLoop(nex_listen_list);
}