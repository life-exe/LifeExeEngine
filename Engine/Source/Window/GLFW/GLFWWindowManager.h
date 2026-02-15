#pragma once

#include "GLFWWindow.h"
#include <memory>
#include <unordered_map>
#include <expected>

namespace LifeExe
{

enum WindowCreationError
{
    ManagerIsNotInitialized,
    CreationFailed
};

class GLFWWindowManager final
{
public:
    GLFWWindowManager();
    ~GLFWWindowManager();

    void update();
    bool areAllWindowsClosed() const;

    std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings);
    std::shared_ptr<GLFWWindow> getWindowById(WindowId id) const;

private:
    bool m_initialized{false};
    std::unordered_map<WindowId, std::shared_ptr<GLFWWindow>> m_windows;
    WindowId m_windowIdCounter{1};

    void cleanupClosedWindows();
};

}  // namespace LifeExe