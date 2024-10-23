#include "Application.h"

#include "WindowsEventHandler.h"

#include <windows.h>
#include <iostream>
#include <thread>
#include <bits/stl_algo.h>

#include "AppEventManager.h"
#include "Keys.h"

namespace Engine {
    Application::Application(const AppSpecifications& specs) : m_specs(specs){
        m_desktopHandle = GetDesktopWindow();
        m_handle = GetConsoleWindow();
        GetWindowRect(m_handle, &m_consoleRect);

        RECT desktopRect;
        GetWindowRect(m_desktopHandle, &desktopRect);

        // Find where the center is and move window to center
        const int32_t centerX = desktopRect.right / 2 - specs.width / 2;
        const int32_t centerY = desktopRect.bottom / 2 - specs.height / 2;

        // Disable maximize and resize border
        LONG style = GetWindowLong(m_handle, GWL_STYLE);
        style &= ~WS_MAXIMIZEBOX;
        style &= ~WS_SIZEBOX;
        SetWindowLong(m_handle, GWL_STYLE, style);
        SetWindowPos(m_handle, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

        // Set title and move & resize window
        SetConsoleTitle(specs.title.c_str());
        MoveWindow(m_handle, centerX, centerY, static_cast<int32_t>(specs.width), static_cast<int32_t>(specs.height), true); // Handle, X, Y, Width, Height, Redraw window

        HMENU hmenu = GetSystemMenu(m_handle, FALSE);
        EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);

        SetConsoleCtrlHandler(WindowsEventHandler, TRUE);

        AppEventManager::AddEventKey(VK_ESCAPE, &m_shouldClose);

        m_renderer = std::make_unique<Renderer::RenderEngine>(m_handle);
    }

    void Application::Loop(){
        using clock = std::chrono::high_resolution_clock;
        using ms = std::chrono::duration<float, std::milli>;

        int i = 0;

        static std::string statusContent = "";

        while(!m_shouldClose){
            m_frameStart = clock::now();
            i++;

            AppEventManager::PollEvents();

            m_frameEnd = clock::now();
            auto dt = std::chrono::duration_cast<ms>(m_frameEnd - m_frameStart).count();

            m_renderer->Render();
            m_renderer->RenderStatusBarContent(statusContent);

            float realFrameTime = dt + (m_specs.fpsMillis - dt > 0 ? m_specs.fpsMillis - dt : 0);
            float fps = (realFrameTime > 0.0f) ? (1000.0f / realFrameTime) : 0.0f;
            statusContent = std::to_string(fps) + "FPS | FRAMES DRAWN: " + std::to_string(i);

            //m_renderer->RenderResetCursor();

            auto overhead = m_specs.fpsMillis - dt;
            if(overhead > 0){
                std::this_thread::sleep_for(ms(overhead));
            }
        }
    }
}