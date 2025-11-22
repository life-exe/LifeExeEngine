#pragma once

#include <string>
#include <memory>

#include "Core/Utility.h"

namespace LifeExe
{

enum class LogVerbosity : uint8_t
{
    NoLogging = 0,
    Display,
    Warning,
    Error,
    Fatal
};

class Log final : public NonCopyable
{
public:
    static Log& getInstance()
    {
        static Log instance;
        return instance;
    }

    void log(LogVerbosity verbosity, const std::string& message) const;

private:
    Log();
    ~Log();

    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}  // namespace LifeExe