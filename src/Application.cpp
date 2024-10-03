#include "Application.h"

#include "WindowsEventHandler.h"

#include <windows.h>
#include <iostream>

#include "AppEventManager.h"

namespace Engine {
    Application::Application(const AppSpecifications& specs){
        m_desktopHandle = GetDesktopWindow();
        m_handle = GetConsoleWindow();
        GetWindowRect(m_handle, &m_consoleRect);

        RECT desktopRect;
        GetWindowRect(m_desktopHandle, &desktopRect);

        // Find where the center is and move window to center
        uint32_t centerX = desktopRect.right / 2 - specs.width / 2;
        uint32_t centerY = desktopRect.bottom / 2 - specs.height / 2;

        // Disable maximize and resize border
        LONG style = GetWindowLong(m_handle, GWL_STYLE);
        style &= ~WS_MAXIMIZEBOX;
        style &= ~WS_SIZEBOX;
        SetWindowLong(m_handle, GWL_STYLE, style);
        SetWindowPos(m_handle, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

        // Set title and move & resize window
        SetConsoleTitle(specs.title.c_str());
        MoveWindow(m_handle, centerX, centerY, specs.width, specs.height, true); // Handle, X, Y, Width, Height, Redraw window

        HMENU hmenu = GetSystemMenu(m_handle, FALSE);
        EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);

        SetConsoleCtrlHandler(WindowsEventHandler, TRUE);

        //for(char i = 'A'; i < 'z'; ++i){
        //    fprintf(stdout, "CHAR: %c | HEX: 0x%x\n", i, i);
        //}

        AppEventManager::AddEventKey(VK_ESCAPE, &m_shouldClose);
    }

    Application::~Application(){

    }

    void Application::Loop(){
        while(!m_shouldClose){
            AppEventManager::PollEvents();
        }
    }

}