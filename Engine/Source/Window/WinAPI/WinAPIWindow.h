#pragma once
#include <string>
#include <functional>
#include "Window/IWindow.h"

namespace LifeExe
{

class WinAPIWindow final : public IWindow
{
public:
    WinAPIWindow(const WindowSettings& settings);
    ~WinAPIWindow() override;

    void setTitle(const std::string& title) override;
    bool isValid() const override;
    bool shouldClose() const override;
    Event<const InputEvent&>& windowEvent() override;

private:
    Event<const InputEvent&> m_windowEvent;
};

}  // namespace LifeExe