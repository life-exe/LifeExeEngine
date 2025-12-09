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

#define PLATFORM_BREAK() (__nop(), __debugbreak());

}  // namespace LifeExe