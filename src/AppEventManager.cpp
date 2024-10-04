#include "AppEventManager.h"

#include <windows.h>
#include <iostream>

namespace Engine{
    std::unordered_map<uint32_t, bool*> AppEventManager::m_eventMap;

    void AppEventManager::PollEvents(){
        for(auto& [key, ptr] : m_eventMap){
            if(GetAsyncKeyState(key) & 0x8000){
                *ptr = true;
            }
        }
    }

    void AppEventManager::AddEventKey(uint32_t key, bool* isEventTriggered){
        if(m_eventMap.find(key) == m_eventMap.end()){
            m_eventMap[key] = isEventTriggered;
            std::cout << "KEY ADDED: " << key << '\n';
        }
    }
}