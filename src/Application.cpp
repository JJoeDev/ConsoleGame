#include "Application.h"

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

        std::clog << specs.title << " | " << specs.width << 'x' << specs.height << std::endl;
    }

    Application::~Application(){

    }


}