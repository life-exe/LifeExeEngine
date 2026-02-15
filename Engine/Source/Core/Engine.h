#pragma once
#include <string_view>
#include <memory>
#include "EngineConfig.h"

namespace LifeExe
{

class GLFWWindowManager;

class Engine final
{
public:
    Engine();
    ~Engine();

    void run();

    static constexpr std::string_view version() { return Engine_VERSION_STRING; }

private:
    std::unique_ptr<GLFWWindowManager> m_windowManager;
    bool m_initialized{false};
};

}  // namespace LifeExe