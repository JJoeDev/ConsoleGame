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
        Utils::FATAL_ASSERT(GetConsoleCursorInfo(m_consoleHandle, &m_ccInfo), "Could not get console cursor info");

        m_ccInfo.bVisible = false;

        Utils::FATAL_ASSERT(SetConsoleCursorInfo(m_consoleHandle, &m_ccInfo), "Could not set console cursor info");

        m_frameX = m_csbInfo.dwSize.X;
        m_frameY = m_csbInfo.srWindow.Bottom - m_csbInfo.srWindow.Top;
        m_frameLength = m_frameX * m_frameY;

        for(int y = 0; y < m_frameY; ++y){
            for(int x = 0; x < m_frameX; ++x){
                if(y == 0 ||y == m_frameY - 1)
                    m_frameStr.push_back((x == 0 || x == m_frameX - 1) ? '+' : '-');
                else
                    m_frameStr.push_back((x == 0 || x == m_frameX - 1) ? '|' : ' ');
            }
        }

        for(int x = 0; x < m_frameX - 1; ++x){
            m_statFrame.push_back(x == m_frameX - 2 ? '|' : '-');
        }
        m_statFrame.push_back('|');
    }

    RenderEngine::~RenderEngine(){
        m_consoleWindow = nullptr;
    }


    void RenderEngine::Render() {
        SetCursorPos(0, 0);

        

        std::cout << m_frameStr.data();
    }

    void RenderEngine::RenderStatusBarContent(const std::string& content){
        SetCursorPos(1, m_frameY - 3);
        std::cout << m_statFrame.data();
        SetCursorPos(1, m_frameY - 2);
        std::cout << content;
    }

    void RenderEngine::RenderResetCursor(){
        SetCursorPos(0, 0);
    }

    void RenderEngine::SetCursorPos(uint16_t x, uint16_t y){
        std::cout.flush();
        const COORD c = {static_cast<short>(x), static_cast<short>(y)};
        SetConsoleCursorPosition(m_consoleHandle, c);
    }
}