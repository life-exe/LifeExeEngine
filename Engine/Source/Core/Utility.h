#pragma once

namespace LifeExe
{
class NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(NonCopyable&&) = delete;
};
}  // namespace LifeExe

#if defined(_MSC_VER)
#define PLATFORM_BREAK() __debugbreak()
#else
#include <signal.h>
#define PLATFORM_BREAK() raise(SIGTRAP)
#endif