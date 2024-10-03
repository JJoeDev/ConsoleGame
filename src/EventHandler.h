#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <windows.h>

namespace Engine{
    static bool WindowsQuitEvent = false;

    static BOOL WINAPI WindowsEventHandler(DWORD eventCode){
		switch(eventCode){
		case CTRL_C_EVENT:
			std::cout << "CTRL + C EVENT\n";
			return TRUE;
			break;
		case CTRL_BREAK_EVENT:
			std::cout << "CTRL + BREAK EVENT\n";
			return TRUE;
			break;
		case CTRL_CLOSE_EVENT:
			std::cout << "CTRL + CLOSE EVENT\n";
			return TRUE;
			break;
		default:
			return TRUE;
		}
    	return FALSE;
    }
}

#endif //EVENTHANDLER_H
