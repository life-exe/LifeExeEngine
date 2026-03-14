#pragma once
#include <string_view>
#include <memory>
#include "EngineConfig.h"
#include "Core/Utility.h"

namespace LifeExe
{

class IWindowManager;

class Engine final : public NonCopyable
{
public:
    Engine(std::unique_ptr<IWindowManager> windowManager);
    ~Engine();

    void run();

    static constexpr std::string_view version() { return Engine_VERSION_STRING; }

private:
    const std::unique_ptr<IWindowManager> m_windowManager;
    bool m_initialized{false};
};

}  // namespace LifeExe