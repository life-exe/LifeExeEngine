#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <cstdint>
#include "Log/Log.h"

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogEvent);

namespace LifeExe
{

struct EventHandle
{
    uint64_t value{};
    constexpr explicit EventHandle(uint64_t id = 0) : value(id) {}
    constexpr auto operator<=>(const EventHandle&) const = default;
};

template <typename... Args>
class Event
{
public:
    using Delegate = std::function<void(Args...)>;

    EventHandle add(Delegate delegate)
    {
        const EventHandle handle{m_nextHandleId++};
        m_delegates[handle] = std::move(delegate);
        return handle;
    }

    template <typename ObjType, typename RetType>
    EventHandle add(ObjType* obj, RetType (ObjType::*method)(Args...))
    {
        return add([obj, method](Args... args) { (obj->*method)(args...); });
    }

    void remove(EventHandle handle) { m_delegates.erase(handle); }

    void invoke(Args... args)
    {
        for (const auto& [handle, delegate] : m_delegates)
        {
            delegate(args...);
        }
    }

private:
    std::unordered_map<EventHandle, Delegate> m_delegates;
    uint64_t m_nextHandleId{1};
};

}  // namespace LifeExe

namespace std
{
template <>
struct hash<LifeExe::EventHandle>
{
    size_t operator()(const LifeExe::EventHandle& id) const noexcept  //
    {
        return std::hash<uint64_t>{}(id.value);
    }
};
}  // namespace std