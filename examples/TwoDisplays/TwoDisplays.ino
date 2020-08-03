/**
 * @example TwoDisplays.ino
 *
 * @par How to Use
 * Show how to use API for two displays.
 *
 * @author Jyrki Berg 3/8/2020 (https://github.com/jyberg)
 * 
 * @copyright 2020 Jyrki Berg
 * 
 */ 

#include <SoftwareSerial.h>

#include "Nextion.h"

#ifdef ESP8266
// esp8266 / NodeMCU software serial ports
SoftwareSerial mySerial_D1(D2, D1); // RX, TX
SoftwareSerial mySerial_D2(D4, D3); // RX, TX
#define _DEBUG_HW_SERIAL
#else
// Esure that used board support multiple serial communication ports simultaneusly, especially if software serial is used for multiple displays.
SoftwareSerial mySerial_D1(3,2); // RX, TX
//SoftwareSerial mySerial_D2(5,4); // RX, TX
#define mySerial_D2 Serial // HW serial posrt used Nextion lig DEBUG_SERIAL_ENABLE cant be anabled wit default debug serial definition as Serial port used.
#endif


/*
* Declare Nextion instance
*/
Nextion *ND1 = Nextion::GetInstance(mySerial_D1);
Nextion *ND2 = Nextion::GetInstance(mySerial_D2);


/*
 * Declare a main page object [nextion instance, page id:0, page name: "page0"]. 
 */
NexPage p0_D1(ND1, 0, "page0");
NexPage p0_D2(ND2, 0, "page0");

/*
 * Declare a slider object [nextion instance, page id:0,component id:1, component name: "s0", page]. 
 */
NexSlider sSlider_D1 = NexSlider(ND1, 0, 1, "slider", &p0_D1);
NexSlider sSlider_D2 = NexSlider(ND2, 0, 1, "slider", &p0_D2);

/*
 * Declare a otherValue text object [nextion instance, page id:0,component id:2, component name: "s0", page]. 
 */
NexText othersValue_D1 = NexText(ND1, 0, 2, "othersValue", &p0_D1);
NexText othersValue_D2 = NexText(ND2, 0, 2, "othersValue", &p0_D2);


/*
 * Register object to the touch event list for display 1.  
 */
NexTouch *nex_listen_list_D1[] = 
{
    &sSlider_D1,
    nullptr
};
NexTouch *nex_listen_list_D2[] = 
{
    &sSlider_D2,
    nullptr
};
/*
 * Min slider component pop callback function. 
 * In this example, slider min value is changed based on min slider value. 
 */
void SliderCallback_D1(void *ptr)
{
    uint32_t val;
    if(sSlider_D1.getValue(&val))
    {
         char buf[10] = {0};
        String cmd;
        utoa(val, buf, 10);
        othersValue_D2.setText(buf);
    }
}
void SliderCallback_D2(void *ptr)
{
    uint32_t val;
    if(sSlider_D2.getValue(&val))
    {
         char buf[10] = {0};
        String cmd;
        utoa(val, buf, 10);
        othersValue_D1.setText(buf);
    }
}


void setup(void)
{
#ifdef _DEBUG_HW_SERIAL
    // HW serial used for dobug messages
    //Serial.begin(9600); 
#endif    
    // Initialize Nextion connection wiht selected baud in this case 19200
    if(!ND1->nexInit(19200))
    {
#ifdef _DEBUG_HW_SERIAL
        Serial.println("nextion D1 init fails"); 
#endif
    }
    if(!ND2->nexInit(19200))
    { 
#ifdef _DEBUG_HW_SERIAL
        Serial.println("nextion D2 init fails"); 
#endif
    }
    /* Register the pop event callback function of the dual state button component. */
    sSlider_D1.attachPop(SliderCallback_D1, &sSlider_D1);
    sSlider_D2.attachPop(SliderCallback_D2, &sSlider_D2);

#ifdef _DEBUG_HW_SERIAL
    Serial.println("setup done");
#endif

}

void loop(void)
{
    /*
     * When a pop or push event occured every time,
     * the corresponding component[right page id and component id] in touch event list will be asked.
     */
     ND1->nexLoop(nex_listen_list_D1);
     ND2->nexLoop(nex_listen_list_D2);
}

