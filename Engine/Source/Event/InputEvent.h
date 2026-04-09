#pragma once

namespace LifeExe
{
enum class EventType
{
    WindowClose,
    WindowResize,
    MouseMove,
    MouseButton,
    MouseScroll,
    KeyPress
};

using EventData = int;  // temp

struct InputEvent
{
    EventType type;
    EventData data;
};

}  // namespace LifeExe