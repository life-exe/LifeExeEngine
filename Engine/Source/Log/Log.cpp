#include "Log.h"

#include <memory>
#include <unordered_map>
#include <filesystem>
#include <chrono>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace LifeExe;
namespace fs = std::filesystem;

namespace
{
const std::unordered_map<LogVerbosity, spdlog::level::level_enum> c_verbosityMap =  //
    {{LogVerbosity::NoLogging, spdlog::level::off},                                 //
        {LogVerbosity::Display, spdlog::level::info},                               //
        {LogVerbosity::Warning, spdlog::level::warn},                               //
        {LogVerbosity::Error, spdlog::level::err},                                  //
        {LogVerbosity::Log, spdlog::level::info},                                   //
        {LogVerbosity::Fatal, spdlog::level::critical}};

constexpr const char* c_logPattern = "[%H:%M:%S.%e] [%^%l%$] %v";
const fs::path c_logDirectory = fs::path("logs");
constexpr const char* c_logFilePrefix = "LifeExe";
constexpr const char* c_logFileExtension = "txt";
constexpr const char* c_timestampFormat = "{:%Y.%d.%m-%H.%M.%S}";
}  // namespace

// pImpl

//           .'\   /`.
//         .'.-.`-'.-.`.
//    ..._:   .-. .-.   :_...
//  .'    '-.(o ) (o ).-'    `.
// :  _    _ _`~(_)~`_ _    _  :
//:  /:   ' .-=_   _=-. `   ;\  :
//:   :|-.._  '     `  _..-|:   :
// :   `:| |`:-:-.-:-:'| |:'   :
//  `.   `.| | | | | | |.'   .'
//    `.   `-:_| | |_:-'   .'
//      `-._   ````    _.-'
//          ``-------''

class Log::Impl
{
public:
    Impl()
    {
        using namespace spdlog;

        const auto consoleSink = std::make_shared<sinks::stdout_color_sink_mt>();
        m_consoleLogger = std::make_unique<logger>("console", consoleSink);
        m_consoleLogger->set_pattern(c_logPattern);

        const auto fileSink = std::make_shared<sinks::basic_file_sink_mt>(makeLogFile().string(), true);
        m_fileLogger = std::make_unique<logger>("file", fileSink);
        m_fileLogger->set_pattern(c_logPattern);
    }

    void log(LogVerbosity verbosity, const std::string& message) const
    {
        if (verbosity == LogVerbosity::NoLogging) return;

        const auto spdLevelIt = c_verbosityMap.find(verbosity);
        if (spdLevelIt == c_verbosityMap.end()) return;

        const auto spdLevel = spdLevelIt->second;
        if (verbosity != LogVerbosity::Log)
        {
            m_consoleLogger->log(spdLevel, message);
        }
        m_fileLogger->log(spdLevel, message);

        if (verbosity == LogVerbosity::Fatal)
        {
            PLATFORM_BREAK();
        }
    }

private:
    std::unique_ptr<spdlog::logger> m_consoleLogger;
    std::unique_ptr<spdlog::logger> m_fileLogger;

    fs::path makeLogFile() const
    {
        fs::create_directory(c_logDirectory);
        const auto now = std::chrono::system_clock::now();
        const auto nowSeconds = std::chrono::floor<std::chrono::seconds>(now);
        const std::string timestamp = std::format(c_timestampFormat, nowSeconds);
        const std::string logName = std::format("{}-{}.{}", c_logFilePrefix, timestamp, c_logFileExtension);
        return c_logDirectory / logName;
    }
};

// interface

Log::Log() : m_pImpl(std::make_unique<Impl>()) {}
Log::~Log() = default;

void Log::log(const LogCategory& category, LogVerbosity verbosity, const std::string& message) const
{
    m_pImpl->log(verbosity, std::format("[{}] {}", category.name(), message));
}
