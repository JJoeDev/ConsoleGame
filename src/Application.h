#ifndef APPLICATION_H
#define APPLICATION_H

#include <windows.h>
#include <cstdint>
#include <string>

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
    };

    class Application {
    public:
        Application(const AppSpecifications& specs);
        virtual ~Application();

        void CloseApplication() {m_shouldClose = true;}
        void Loop();

    private:
        HWND m_handle;
        HWND m_desktopHandle;
        RECT m_consoleRect;

        bool m_shouldClose{false};
    };

} // Engine

#endif //APPLICATION_H
