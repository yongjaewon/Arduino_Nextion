/**
 * @example CompDualStateButton.ino
 * 
 * @par How to Use
 * This example shows that when the dual state button component on the Nextion screen is released,
 * the text of Text component will change one every time.      
 *
 * @author  huang xianming (email:<xianming.huang@itead.cc>)
 * @date    2015/11/11
 * @updated 2016/12/25 bring HMI up to v0.32 to avoid too old issues
 * @convert by Patrick Martin, no other changes made
 * @author Jyrki Berg 8/3/2020 (https://github.com/jyberg)

 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * @copyright 2020 Jyrki Berg
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
 * Declare a dual state button object [nextion instance, page id:0,component id:1, component name: "bt0", pointer to page object: &p0]. 
 */
NexDSButton bt0(next, 0, 1, "bt0", &p0);

/*
 * Declare a text object [nextion instance, page id:0,component id:1, component name: "bt0", pointer to page object: &p0]. 
 */
NexText t0(next, 0, 2, "t0", &p0);


/*
 * Declare a reset button object [nextion instance, page id:0,component id:1, component name: "bt0", pointer to page object: &p0]. 
 */
NexDSButton bReset(next, 0, 3, "b0", &p0);



char buffer[100] = {0};

/*
 * Register a dual state button object to the touch event list.  
 */
NexTouch *nex_listen_list[] = 
{
    &bt0,
    &bReset,
    nullptr
};

/*
 * Dual state button component pop callback function. 
 * In this example,the button's text value will plus one every time when it is released. 
 */
void bt0PopCallback(void *ptr)
{
    uint32_t dual_state;
 
    /* Get the state value of dual state button component . */
    bt0.getValue(&dual_state);
    if(dual_state) 
    {
        t0.setText("HI! OPEN STATE");
    }
    else
    {
        t0.setText("HI! OFF STATE");
    }
}

void bResetPopCallBack(void *ptr)
{
    t0.setText("HelloWorld");
    bt0.setValue(1);
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

    /* Register the pop event callback function of the dual state button component. */
    bt0.attachPop(bt0PopCallback, &bt0);
    bReset.attachPop(bResetPopCallBack, &bReset);
    
    dbSerialPrintln("setup done"); 
}

void loop(void)
{   
    /*
     * When a pop or push event occured every time,
     * the corresponding component[right page id and component id] in touch event list will be asked.
     */
     next->nexLoop(nex_listen_list);
}












