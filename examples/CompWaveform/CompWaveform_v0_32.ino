/**
 * @example CompWaveform.ino
 *
 * @par How to Use
 * Show how to use API of class NexWaveform with auto scaling.  
 *
 * @author Jyrki Berg 7/28/2020 (https://github.com/jyberg)
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
 * Declare a Waweform object [nextion instance, page id:0,component id:1, component name: "s0", optional page, low value,  max value, component high]. 
 */
NexWaveform s0 = NexWaveform(next, 0, 1, "s0", -1.1, 1.2, 220, &p0);

float ch0_data{0};
float ch1_data{60};
float ch2_data{180};
float ch3_data{240};

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
    ++ch0_data;
    ++ch1_data;
    ++ch2_data;
    ++ch3_data;
    
    s0.addValue(0, sin(ch0_data * M_PI/180.0));
    s0.addValue(1, sin((ch1_data + random(1,5)) * M_PI/180.0));
    s0.addValue(2, sin((ch2_data + random(10,15)) * M_PI/180.0));
    s0.addValue(3, sin((ch3_data + random(20,25)) * M_PI/180.0));
    
}

