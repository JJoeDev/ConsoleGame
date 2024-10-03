#ifndef APPEVENTMANAGER_H
#define APPEVENTMANAGER_H

#include <cstdint>
#include <unordered_map>

namespace Engine{
    class AppEventManager {
    public:
        static void PollEvents();

        static void AddEventKey(uint32_t, bool* isEventTriggered);

    private:
        static std::unordered_map<uint32_t, bool*> m_eventMap;
    };
}

#endif //APPEVENTMANAGER_H
