#pragma once
#include <functional>
#include <vector>


template<typename... Args>
class FDelegate
{
public:
    void AddListener(const std::function<void(Args...)>& InListener)
    {
        ListenerList.push_back(InListener);
    }

    void Broadcast(Args... InArgs)
    {
        for (auto& Listener : ListenerList)
        {
            Listener(InArgs...);
        }
    }

private:
    std::vector<std::function<void(Args...)>> ListenerList;
};
