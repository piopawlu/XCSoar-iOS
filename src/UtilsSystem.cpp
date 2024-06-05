// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The XCSoar Project

#include "UtilsSystem.hpp"
#include "CommandLine.hpp"
#include "ui/dim/Size.hpp"

#ifdef ANDROID
#include "Android/NativeView.hpp"
#include "Android/Main.hpp"
#endif

#ifdef __APPLE__
#include <SDL2/SDL.h>
#endif

#include <tchar.h>

#ifdef _WIN32
#include <windef.h> // for HWND (needed by winuser.h)
#include <winuser.h>
#endif

#if !defined ANDROID && !defined __APPLE__

[[gnu::const]]
static PixelSize
GetWindowDecorationOverhead() noexcept
{
#ifdef _WIN32
  return {
    2 * GetSystemMetrics(SM_CXFIXEDFRAME),
    2 * GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION),
  };
#else
  return {};
#endif
}

#endif

/**
 * Returns the screen dimension rect to be used
 * @return The screen dimension rect to be used
 */
PixelSize
SystemWindowSize() noexcept
{
#ifdef ANDROID
  return native_view->GetSize();
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE
        SDL_DisplayMode dm;
        SDL_GetDesktopDisplayMode(0, &dm);
        return PixelSize{ dm.w, dm.h};
    #else
        return PixelSize{ CommandLine::width, CommandLine::height } + GetWindowDecorationOverhead();
    #endif
    
    
#else
  /// @todo implement this properly for SDL/UNIX
  return PixelSize{ CommandLine::width, CommandLine::height } + GetWindowDecorationOverhead();
#endif
}
