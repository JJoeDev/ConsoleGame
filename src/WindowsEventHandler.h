#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <windows.h>

namespace Engine{ // This event handler makes it so the application cannot be quit by built in events
    static BOOL WINAPI WindowsEventHandler(DWORD eventCode){
		switch(eventCode){
		case CTRL_C_EVENT:
			return TRUE;
			break;
		case CTRL_BREAK_EVENT:
			return TRUE;
			break;
		case CTRL_CLOSE_EVENT:
			return TRUE;
			break;
		default:
			return TRUE;
			break;
		}
    	return FALSE;
    }
}

#endif //EVENTHANDLER_H
