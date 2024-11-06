#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>
#include <cstdint>
#include <string>
#include <memory>
#include <chrono>

#include "RenderEngine.h"
#include "Game.h"

#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

namespace Engine {
    struct AppSpecifications{
        tstring title = "Hello, World";
        uint32_t width{500};
        uint32_t height{500};
        uint16_t fpsMillis{32};
    };

    class Application {
    public:
        explicit Application(const AppSpecifications& specs);
        virtual ~Application() = default;

        void Loop();

    private:
        const AppSpecifications m_specs;

        HWND m_handle;
        HWND m_desktopHandle;
        RECT m_consoleRect;

        std::shared_ptr<Renderer::RenderEngine> m_renderer{nullptr};
        std::unique_ptr<Game> m_game{nullptr};

        std::chrono::time_point<std::chrono::system_clock> m_frameStart, m_frameEnd;

        bool m_shouldClose{false};
        bool m_paused{false};
    };

} // Engine

#endif //APPLICATION_H
