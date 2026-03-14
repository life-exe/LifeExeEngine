#pragma once

#include "Window/IWindow.h"
#include <memory>
#include <expected>

namespace LifeExe
{

enum WindowCreationError
{
    ManagerIsNotInitialized,
    CreationFailed
};

class IWindowManager
{
public:
    virtual ~IWindowManager() = default;

    virtual void update() = 0;
    virtual bool areAllWindowsClosed() const = 0;

    virtual std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings) = 0;
    virtual std::shared_ptr<IWindow> getWindowById(WindowId id) const = 0;
};

}  // namespace LifeExe