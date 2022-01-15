/**
 * @file NexScreen.cpp
 *
 * The implementation of class NexScreen. 
 *
 * @author Francesco Doni 8/1/2022 (https://github.com/frdoni)
 * @date 8/1/2022
 * 
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * @copyright 2020 Francesco Doni
 **/
#include "NexScreen.h"
#include "NexHardware.h"

NexScreen::NexScreen(Nextion *nextion)
    :NexTouch(nextion, 0, 0, nullptr, nullptr)
{
}


bool NexScreen::setBacklightLevel(uint32_t number) 
{
	char buf[10] = {0};
    String cmd;    

	if (number < 0) 
		number=0;	
	if (number > 100) 
		number = 100;	
	
    utoa(number, buf, 10);    
    cmd += "dim=";
    cmd += buf;
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexScreen::invokeScreenSleep()
{
	String cmd;
	cmd += "sleep=1";
	sendCommand(cmd.c_str());
	return recvRetCommandFinished();
}

bool NexScreen::invokeScreenWakeup()
{
	String cmd;
	cmd += "sleep=0";
	sendCommand(cmd.c_str());
	return recvRetCommandFinished();
}

bool NexScreen::setScreenAutoWakeup(uint32_t number)
{
	char buf[10] = {0};
    String cmd;    
	
	if (number < 0) 
		number=0;	
	if (number > 1) 
		number = 1;	
	
	utoa(number, buf, 10);    
    cmd += "thup=";
    cmd += buf;
		
	sendCommand(cmd.c_str());
	return recvRetCommandFinished();
}

bool NexScreen::setScreenTouchTimeout(uint32_t number) {
	char buf[10] = {0};
	String cmd;
	
	if (number < 2) 
		return false;
	if (number > 65535) 
		number = 65535;	
			
	utoa(number, buf, 10);    
    cmd += "thsp=";
    cmd += buf;
		
	sendCommand(cmd.c_str());
	return recvRetCommandFinished();
}


bool NexScreen::setSleepOnNoSerial(uint32_t number) {
	char buf[10] = {0};
	String cmd;
	
	if (number < 2) 
		return false;
	if (number > 65535) 
		number = 65535;	
			
	utoa(number, buf, 10);    
    cmd += "ussp=";
    cmd += buf;
		
	sendCommand(cmd.c_str());
	return recvRetCommandFinished();
}



bool NexScreen::setWakeOnSerialData(uint32_t number) {
	char buf[10] = {0};
	String cmd;
	
	if (number < 2) 
		return false;
	if (number > 65535) 
		number = 65535;	
			
	utoa(number, buf, 10);    
    cmd += "usup=";
    cmd += buf;
		
	sendCommand(cmd.c_str());
	return recvRetCommandFinished();
}

