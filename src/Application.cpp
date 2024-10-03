#include "Application.h"

#include "EventHandler.h"

#include <windows.h>
#include <iostream>

namespace Engine {
    Application::Application(const AppSpecifications& specs){
        m_desktopHandle = GetDesktopWindow();
        m_handle = GetConsoleWindow();
        GetWindowRect(m_handle, &m_consoleRect);

        RECT desktopRect;
        GetWindowRect(m_desktopHandle, &desktopRect);

        uint32_t centerX = desktopRect.right / 2 - specs.width / 2;
        uint32_t centerY = desktopRect.bottom / 2 - specs.height / 2;

        SetConsoleTitle(specs.title.c_str());
        MoveWindow(m_handle, centerX, centerY, specs.width, specs.height, true); // Handle, X, Y, Width, Height, Redraw window

        HMENU hmenu = GetSystemMenu(m_handle, FALSE);
        EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);

        if(SetConsoleCtrlHandler(WindowsEventHandler, TRUE)){ // not working correct
            std::cout << "Console CTRL Handler Set\n";
        }

        m_running = true;
        std::clog << specs.title << " | " << specs.width << 'x' << specs.height << std::endl;
    }

    Application::~Application(){

    }

    void Application::Loop(){
        while(!WindowsQuitEvent){

        }

        std::cout << "LOOP CLOSED\n";
    }
}