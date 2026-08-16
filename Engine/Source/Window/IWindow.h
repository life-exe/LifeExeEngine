#pragma once

#include <string>
#include <functional>
#include <cstdint>

#include "Event/Event.h"
#include "Event/InputEvent.h"

namespace LifeExe
{

struct WindowId
{
    uint32_t value{0};
    constexpr explicit WindowId(uint32_t id) : value(id) {}

    constexpr WindowId operator++(int)
    {
        WindowId temp = *this;
        ++value;
        return temp;
    }

    constexpr auto operator<=>(const WindowId&) const = default;
};

struct WindowSettings
{
    std::string title{};
    int width{800};
    int height{600};
    int x{50};
    int y{50};
};

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual void setTitle(const std::string& title) = 0;
    virtual bool isValid() const = 0;
    virtual bool shouldClose() const = 0;
    virtual Event<const InputEvent&>& windowEvent() = 0;
};

}  // namespace LifeExe

namespace std
{
template <>
struct hash<LifeExe::WindowId>
{
    size_t operator()(const LifeExe::WindowId& id) const noexcept  //
    {
        return std::hash<uint32_t>{}(id.value);
    }
};
}  // namespace std