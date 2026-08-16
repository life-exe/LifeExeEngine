#pragma once

#include <variant>

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

struct MouseMoveEventData
{
    double x;
    double y;
};

struct MouseScrollEventData
{
    double xOffset;
    double yOffset;
};

struct WindowResizeEventData
{
    int width;
    int height;
};

struct WindowCloseEventData
{
    unsigned int id;
};

using EventData = std::variant<std::monostate,  //
    MouseMoveEventData,                         //
    MouseScrollEventData,                       //
    WindowResizeEventData,                      //
    WindowCloseEventData>;

struct InputEvent
{
    EventType type;
    EventData data;
};

}  // namespace LifeExe