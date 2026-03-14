#include "WinAPIWindow.h"
#include "Log/Log.h"

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogWinAPIWindow);

WinAPIWindow::WinAPIWindow(const WindowSettings& settings)
{
    LE_LOG(LogWinAPIWindow, Error, "WinAPI window is not implemented!");
}

WinAPIWindow::~WinAPIWindow() {}

void WinAPIWindow::setTitle(const std::string& title) {}

bool WinAPIWindow::isValid() const
{
    return false;
}

bool WinAPIWindow::shouldClose() const
{
    return true;
}
