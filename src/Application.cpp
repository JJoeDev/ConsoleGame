#include "Application.h"

#include "WindowsEventHandler.h"

#include <windows.h>
#include <iostream>
#include <thread>

#include "AppEventManager.h"
#include "Keys.h"
#include "Game.h"

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
        AppEventManager::AddEventKey(KEY_P, &m_paused);

        // AppEventManager::RemoveEventKey(VK_ESCAPE);

        m_renderer = std::make_unique<Renderer::RenderEngine>(m_handle);
        m_game = std::make_unique<Game>(m_renderer);
    }

    void Application::Loop(){
        using clock = std::chrono::high_resolution_clock;
        using ms = std::chrono::duration<float, std::milli>;

        int i = 0;

        static std::string statusContent = "";

        while(!m_shouldClose){
            AppEventManager::PollEvents();

            if(m_paused) continue;

            m_frameStart = clock::now();
            i++;

            m_frameEnd = clock::now();
            auto dt = std::chrono::duration_cast<ms>(m_frameEnd - m_frameStart).count();

            m_renderer->Render();
            m_renderer->RenderStatusBarContent(statusContent);

            m_game->Update();
            m_game->Draw();

            float realFrameTime = dt + (m_specs.fpsMillis - dt > 0 ? m_specs.fpsMillis - dt : 0);
            float fps = (realFrameTime > 0.0f) ? (1000.0f / realFrameTime) : 0.0f;
            statusContent = std::to_string(fps) + "FPS | FRAMES DRAWN: " + std::to_string(i);

            auto overhead = m_specs.fpsMillis - dt;
            if(overhead > 0){
                std::this_thread::sleep_for(ms(overhead));
            }
        }
    }
}