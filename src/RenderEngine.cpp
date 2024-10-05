#include "RenderEngine.h"

#include <cwchar>
#include <iostream>

#include "Assert.h"

namespace Renderer{
    RenderEngine::RenderEngine(HWND& window){
        m_consoleWindow = &window;

        m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        Utils::FATAL_ASSERT(m_consoleHandle, "Could not get handle to console window!");

        Utils::FATAL_ASSERT(GetConsoleScreenBufferInfo(m_consoleHandle, &m_csbInfo), "Could not get console screen buffer info");

        m_frameX = m_csbInfo.dwSize.X;
        m_frameY = m_csbInfo.srWindow.Bottom - m_csbInfo.srWindow.Top;
        m_frameLength = m_frameX * m_frameY;
    }

    RenderEngine::~RenderEngine(){
        m_consoleWindow = nullptr;
    }


    void RenderEngine::Render() {
        SetCursorPos(0, 0);
        std::string drawBuffer;

        for (int y = 0; y < m_frameY; ++y) {
            for (int x = 0; x < m_frameX; ++x) {
                if (y == 0 || y == m_frameY - 1) {
                    drawBuffer += (x == 0 || x == m_frameX - 1) ? '+' : '-';
                } else {
                    drawBuffer += (x == 0 || x == m_frameX - 1) ? '|' : ' ';
                }
            }
        }

        std::cout << drawBuffer;
    }

    void RenderEngine::SetCursorPos(uint16_t x, uint16_t y){
        std::cout.flush();
        const COORD c = {static_cast<short>(x), static_cast<short>(y)};
        SetConsoleCursorPosition(m_consoleHandle, c);
    }
}