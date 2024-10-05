#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <cstdint>
#include <array>
#include <memory>
#include <windows.h>

namespace Renderer{
    class RenderEngine{
    public:
        explicit RenderEngine(HWND& window);
        virtual ~RenderEngine();

        void Render();
        void SetCursorPos(uint16_t x, uint16_t y);

    private:
        HWND* m_consoleWindow;
        HANDLE m_consoleHandle;
        RECT m_clientRect;

        CONSOLE_SCREEN_BUFFER_INFO m_csbInfo{};
        const COORD m_topLeft{0, 0};
        uint16_t m_frameX, m_frameY;
        uint32_t m_frameLength;
    };
}

#endif //RENDERENGINE_H
