#ifndef APPEVENTMANAGER_H
#define APPEVENTMANAGER_H

#include <cstdint>
#include <unordered_map>

namespace Engine{
    class AppEventManager {
    public:
        static void PollEvents();

        static void AddEventKey(const int32_t key, bool* isEventTriggered);
        static void RemoveEventKey(const int32_t key);

    private:
        struct m_KeyStateKeys{
            bool* trigger{nullptr};
            bool prevState = false;
        };

        static std::unordered_map<int32_t, m_KeyStateKeys> m_eventMap;
    };
}

#endif //APPEVENTMANAGER_H
