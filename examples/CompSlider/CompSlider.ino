/**
 * @example CompSlider.ino
 *
 * @par How to Use
 * Show how to use API of class fo Slider component.  
 *
 * @author Jyrki Berg 8/2/2020 (https://github.com/jyberg)
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
 * Declare a min slider object [nextion instance, page id:0,component id:4, component name: "s0", page]. 
 */
NexSlider sMin = NexSlider(next, 0, 4, "min", &p0);

/*
 * Declare a max slider object [nextion instance, page id:0,component id:5, component name: "s0", page]. 
 */
NexSlider sMax = NexSlider(next, 0, 5, "max", &p0);

/*
 * Declare a dest slider object [nextion instance, page id:0,component id:3, component name: "s0", page]. 
 */
NexSlider sSlider = NexSlider(next, 0, 3, "slider", &p0);


/*
 * Register object to the touch event list.  
 */
NexTouch *nex_listen_list[] = 
{
    &sMin,
    &sMax,
    nullptr
};

/*
 * Min slider component pop callback function. 
 * In this example, slider min value is changed based on min slider value. 
 */
void MinCallback(void *ptr)
{
    uint32_t val;
    // Get the slider value.
    if(sMin.getValue(&val))
    {
        // set slider minimun value
        sSlider.setMinval(val);
    }
}

/*
 * Max slider component pop callback function. 
 * In this example, slider min value is changed based on min slider value. 
 */
void MaxCallback(void *ptr)
{
    uint32_t val;
    // Get the slider value.
    if(sMax.getValue(&val))
    {
        // set slider maximun value
        sSlider.setMaxval(val);
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
    /* Register the pop event callback function of the dual state button component. */
    sMin.attachPop(MinCallback, &sMin);
    sMax.attachPop(MaxCallback, &sMax);

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

