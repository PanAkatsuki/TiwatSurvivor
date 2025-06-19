#pragma once
#include <functional>
#include <vector>


template<typename... Args>
class FDelegate
{
public:
    using HandlerType = std::function<void(Args...)>;

    void AddListener(const HandlerType& InHander)
    {
        ListenerList.push_back(InHander);
    }

    void Broadcast(Args... args)
    {
        for (auto& Listener : ListenerList)
        {
            Listener(args...);
        }
    }

private:
    std::vector<HandlerType> ListenerList;
};