#pragma once

#include <string>
#include "Log/Log.h"
#include "Event/InputEvent.h"  // !!

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogEvent);

namespace LifeExe
{

template <typename... Args>
class Event
{
public:
    void invoke(Args... args)
    {
        auto printEvent = [](const InputEvent& event)
        {
            std::string eventTypeStr;
            switch (event.type)
            {
                case EventType::WindowClose: eventTypeStr = "WindowClose"; break;
                case EventType::WindowResize: eventTypeStr = "WindowResize"; break;
                case EventType::MouseMove: eventTypeStr = "MouseMove"; break;
                case EventType::MouseButton: eventTypeStr = "MouseButton"; break;
                case EventType::MouseScroll: eventTypeStr = "MouseScroll"; break;
                case EventType::KeyPress: eventTypeStr = "KeyPress"; break;
            }
            LE_LOG(LogEvent, Display, "Event: {}", eventTypeStr);
        };

        (printEvent(args), ...);
    }
};

}  // namespace LifeExe