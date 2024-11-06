#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <windows.h>

namespace Renderer{
    class RenderEngine{
    public:
        explicit RenderEngine(HWND& window);
        virtual ~RenderEngine();

        void Render();
        void RenderStatusBarContent(const std::string& content);
        void RenderResetCursor() const;
        void SetCursorPos(const uint16_t x, const uint16_t y) const;

        void DrawCharAtCursor(const char c);
        void DrawStrAtCursor(const std::string& str);

        [[nodiscard]] uint16_t GetFrameX() const {return m_frameX;}
        [[nodiscard]] uint16_t GetFrameY() const {return m_frameY;}

    private:
        HWND* m_consoleWindow;
        HANDLE m_consoleHandle;
        RECT m_clientRect;

        CONSOLE_SCREEN_BUFFER_INFO m_csbInfo{};
        CONSOLE_CURSOR_INFO m_ccInfo{};

        const COORD m_topLeft{0, 0};
        uint16_t m_frameX, m_frameY;
        uint32_t m_frameLength;

        std::vector<char> m_frameStr;
        std::vector<char> m_statFrame;
    };
}

#endif //RENDERENGINE_H
