/**
* @file NexScreen.h
*
* The definition of class NexScreen.
*
* @author Francesco Doni 8/1/2022 (https://github.com/frdoni)
* @date 1/8/2022
*
* @copyright 
* Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
* 
* @copyright 2022 Francesco Doni
*
*/

#pragma once

#include "NexTouch.h"

class Nextion;
class NexObject;

/**
 * @addtogroup Component 
 * @{ 
 */
 
/**
* NexScreen component.
*
*
*/
class NexScreen : public NexTouch
{
	NexScreen()=delete;
	
public: /* methods */

	/**
     * @copydoc NexObject::NexObject(Nextion*, uint8_t, uint8_t, const char*, const NexObject*)
     */
	NexScreen(Nextion *nextion);
	
	/**
	* Set the brightness of the display.
	*
	* @param number (0 - 100).
	* @return true if success, false for failure 
	*/
	bool setBacklightLevel(uint32_t number);
	
	/**
	* Set Nextion sleep mode.
	*
	* @param none
	* @return true if success, false for failure
	*/
	bool invokeScreenSleep();
	
	/**
	* Set Nextion awake mode.
	*
	* @param none
	* @return true if success, false for failure
	*/
	bool invokeScreenWakeup();
	
	/**
	* Set Auto Wake on Touch.
	*
	* @param number, 0 (do not wake), 1 (wake on touch), default 0.
	* @return true if success, false for failure
	*/
	
	bool setScreenAutoWakeup(uint32_t number);
	
	/**
	* Set Sleep on No Touch.
	*
	* @param number of second, 3 - 65535, default 0 (means no timeout)
	* @return true if success, false for failure
	*/
	bool setScreenTouchTimeout(uint32_t number);
	
	/**
	* Sets internal No-serial-then-sleep timer to specified value in seconds.
	*
	* @param number of second, 3 - 65535, default 0 (means no timeout)
	* @return true if success, false for failure
	*/
	bool setSleepOnNoSerial(uint32_t number);
	
	/**
	* Sets if serial data wakes Nextion from sleep mode automatically.
	*
	* @param number, min is 0, max is 1, default 0
	* @return true if success, false for failure
	*/
	bool setWakeOnSerialData(uint32_t number);
	
	/**
	* Display a Resource Picture at specified coordinate.
	*	
	* @x number, the x coordinate of upper left corner where picture hould be drawn
	* @y number, the y coordinate of upper left corner where picture should be drawn
	* @picid number, the number of the Resource Picture in the HMI design
	* @return true if success, false for failure
	*/
	bool drawPicture(uint32_t x, uint32_t y, uint32_t id);

    /**
	* Crop Picture area from Resource Picture using defined area.
	*	
	* @x number, the x coordinate of upper left corner where picture hould be drawn
	* @y number, the y coordinate of upper left corner where picture should be drawn
	* @cw number, the width of the defined crop area
	* @ch number, the height of the defined crop area
	* @picid number, the number of the Resource Picture in the HMI design
	* @return true if success, false for failure
	*/
	bool cropPicture(uint32_t x, uint32_t y, uint32_t cw, uint32_t ch, uint32_t id);
	
	/**
	* Fill a defined area with specified color.
	*	
	* @x number, the x coordinate of upper left corner of defined fill area
	* @y number, the y coordinate of upper left corner of defined fill area
	* @w number, the width of the defined fill area
	* @h number, the height of the defined fill area
	* @color number, fill color
	* @return true if success, false for failure
	*/
	bool fillArea(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
};
/**
* @}
*/

