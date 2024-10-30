#include "AppEventManager.h"

#include <windows.h>

namespace Engine{
    std::unordered_map<int32_t, AppEventManager::m_KeyStateKeys> AppEventManager::m_eventMap;

    void AppEventManager::PollEvents(){
        for(auto& [key, state] : m_eventMap){
            if(GetAsyncKeyState(key) & 0x8000){
                if(!state.prevState){
                    *state.trigger = !*state.trigger;
                    state.prevState = true;
                }
            }
            else{
                if(state.prevState) state.prevState = false;
            }
        }
    }

    void AppEventManager::AddEventKey(int32_t key, bool* isEventTriggered){
        if(m_eventMap.find(key) == m_eventMap.end()){
            m_eventMap[key] = {isEventTriggered, false};
        }
    }

    void AppEventManager::RemoveEventKey(const int32_t key){
        m_eventMap.erase(key);
    }

}