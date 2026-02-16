/*
 * ImNoGui 0.1.0
 *
 * Copyright (c) 2026 Arya Bakhtiari
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* @notes(aabib):
 *
 * - links: ui/window/event/graphics
 * https://github.com/ColleagueRiley/RGFW
 * https://github.com/floooh/sokol
 * https://github.com/glfw/glfw
 * https://github.com/freeglut/freeglut
 * https://docs.rs/winit/latest/winit/platform/index.html
 * https://github.com/nicbarker/clay
 * https://github.com/rxi/microui/
 * https://github.com/ocornut/imgui
 * https://github.com/david-vanderson/dvui
 * https://www.gpui.rs/
 * https://github.com/emilk/egui
 * https://github.com/raysan5/raylib
 * https://github.com/libsdl-org/SDL
 * https://github.com/gfx-rs/wgpu
 * https://github.com/kvark/blade
 *
 * - links: x11
 * https://gitlab.freedesktop.org/xorg/lib/libx11
 * https://www.x.org/releases/current/doc/libX11/libX11/libX11.html
 * https://tronche.com/gui/x/xlib/
 * https://hereket.com/posts/linux_creating_x11_windows/
 * https://www.x.org/wiki/guide/xlib-and-xcb/
 * https://www.x.org/wiki/Development/
 * http://mech.math.msu.su/~vvb/2course/Borisenko/CppProjects/GWindow/xintro.html
 * https://gaultier.github.io/blog/x11_x64.html
 * https://magcius.github.io/xplain/article/index.html
 *
 * - links: win32
 *
 */

// ----------------------------------------------------------------------------
//
// Nile Platforms:
// - [ ] NILE_PLATFORM_WINDOWS
// - [ ] NILE_PLATFORM_LINUX
// - [ ] NILE_PLATFORM_ANDROID
// - [ ] NILE_PLATFORM_MACOS
// - [ ] NILE_PLATFORM_IOS
// - [ ] NILE_PLATFORM_WASM
// - [ ] NILE_PLATFORM_FREEBSD
#if defined(__linux__) || defined(__gnu_linux__)
# define NILE_PLATFORM_LINUX
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
# define NILE_PLATFORM_WINDOWS
#endif

#if defined(__ANDROID__)
# define NILE_PLATFORM_ANDROID
# error "Platform Not implemented Yet!"
#endif
#if defined(__EMSCRIPTEN__)
# define NILE_PLATFORM_WASM
# error "Platform Not implemented Yet!"
#endif

// @brief(aabib): prevent compiling when target platform is not selected!
#if !defined(NILE_PLATFORM_LINUX) && !defined(NILE_PLATFORM_WINDOWS)   \
    && !defined(NILE_PLATFORM_ANDROID) && !defined(NILE_PLATFORM_WASM) \
    && !defined(NILE_PLATFORM_MACOS) && !defined(NILE_PLATFORM_IOS)    \
    && !defined(NILE_PLATFORM_FREEBSD)
# error "No platforms selected!"
#endif

//
// Nile Platforms
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile Platform: Linux
//
#if defined(NILE_PLATFORM_LINUX)

// @brief(aabib): on linux if no windowing api is selected , defaults to x11
# if !defined(NILE_WINDOW_WAYLAND) && !defined(NILE_WINDOW_X11)
#  define NILE_WINDOW_X11
# endif

// @brief(aabib): on linux if no graphics api is selected, defaults to opengl
# if !defined(NILE_GRFX_OPENGL) && !defined(NILE_GRFX_VULKAN) \
     && !defined(NILE_GRFX_OPENGLES)
#  define NILE_GRFX_OPENGL
# endif

# if defined(NILE_WINDOW_X11)
// @note(aabib): X11 headers
// https://tronche.com/gui/x/xlib/introduction/header.html
#  include <X11/X.h>
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>
# endif

# if defined(NILE_WINDOW_WAYLAND)
# endif

#endif
//
// Nile Platform: Linux
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile Platform: Windows
//
#if defined(NILE_PLATFORM_WINDOWS)
// @note(aabib): defining WIN32_LEAN_AND_MEAN will speed build process by excluding less used apis
# define WIN32_LEAN_AND_MEAN
# include <windows.h>

// @brief(aabib): on windows if no graphics api is selected, defaults to opengl
# if !defined(NILE_GRFX_OPENGL) && !defined(NILE_GRFX_VULKAN)       \
     && !defined(NILE_GRFX_OPENGLES) && !defined(NILE_GRFX_DIRECTX)
#  define NILE_GRFX_OPENGL
# endif

#endif
//
// Nile Platform: Windows
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile GRFX: OpenGL
//
#if defined(NILE_GRFX_OPENGL)
# define GLAD_GL_IMPLEMENTATION // Enables Glad Gl

// @brief(aabib): if no opengl version is selected, defaults to opengl v2.1
# if !defined(NILE_GRFX_OPENGL_V10) || !defined(NILE_GRFX_OPENGL_V11) \
     || !defined(NILE_GRFX_OPENGL_V21)                                \
     || !defined(NILE_GRFX_OPENGL_V33)
#  define NILE_GRFX_OPENGL_V21
# endif

# if defined(NILE_GRFX_OPENGL_V10)
#  include "../../vendor-glad/v2.0.8/gl10core.h"
# endif
# if defined(NILE_GRFX_OPENGL_V11)
#  include "../../vendor-glad/v2.0.8/gl11core.h"
# endif
# if defined(NILE_GRFX_OPENGL_V21)
#  include "../../vendor-glad/v2.0.8/gl21core.h"
# endif
# if defined(NILE_GRFX_OPENGL_V33)
#  include "../../vendor-glad/v2.0.8/gl33core.h"
# endif

// @brief(aabib): on linux if opengl(gapi) and x11(wapi) is selected , defaults to glx
# if defined(NILE_PLATFORM_LINUX) && defined(NILE_WINDOW_X11)
#  define GLAD_GLX_IMPLEMENTATION // Enables Glad GLX
#  include "../../vendor-glad/v2.0.8/glx14.h"
# endif

// @brief(aabib): on windows if opengl(gapi) is selected , defaults to wgl
# if defined(NILE_PLATFORM_WINDOWS)
#  define GLAD_WGL_IMPLEMENTATION // Enables Glad WGL
#  include "../../vendor-glad/v2.0.8/wgl10.h"
# endif

#endif
//
// Nile GRFX: OpenGL
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile GRFX: OpenGL ES
//
#if defined(NILE_PLATFORM_LINUX) && defined(NILE_WINDOW_WAYLAND)
# define GLAD_EGL_IMPLEMENTATION             // Enables Glad GLX
# include "../../vendor-glad/v2.0.8/egl15.h" // Glad GLX Headers/Utils/Loaders
#endif
//
// Nile GRFX: OpenGL ES
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile GRFX: Vulkan
//
#if defined(NILE_GRFX_VULKAN)
#endif
//
// Nile GRFX: Vulkan
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile GRFX: Metal
//
// @brief(aabib): metal is only available on MacOs
#if defined(NILE_GRFX_METAL) && !defined(NILE_PLATFORM_MACOS)
# error "Metal Graphics api is only available on MacOs"
#endif
#if defined(NILE_GRFX_METAL)
#endif
//
// Nile GRFX: Metal
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile GRFX: DirectX
//
// @brief(aabib): directx is only available on MacOs
#if defined(NILE_GRFX_DIRECTX) && !defined(NILE_PLATFORM_WINDOWS)
# error "DirectX Graphics api is only available on windows"
#endif
#if defined(NILE_GRFX_DIRECTX) && defined(NILE_PLATFORM_WINDOWS)
#endif
//
// Nile GRFX: DirectX
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Base Core: Header
//
#include <stdint.h>

// VARIABLE/STATIC
#define persist_local  static
#define persist_global static

// FUNCTION
#define fn          // @note(aabib): do we need this?
#define fn_internal static
#define fn_external extern

// UNSIGNED INT
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// SIGNED INT
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// FLOAT INT
typedef float  f32;
typedef double f64;

// BOOL
typedef i8  b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

// Windows UTF-16 related
#if defined(NILE_PLATFORM_WINDOWS)
typedef wchar_t wchar; // wide character , used in win api
typedef int32_t rune;  // unicode codepoint
#endif

// ENUM
#define enum8(type)  u8
#define enum16(type) u16
#define enum32(type) u32
#define enum64(type) u64

// Function prototypes

// @brief(aabib):
// @param:
// @param:
// @param:
// @return:
fn_internal float
clamp(float min, float value, float max);

//
// Base Core: Header
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Base Core: Source
//
fn_internal float
clamp(float min, float value, float max)
{
  if(value < min)
  {
    return min;
  }

  if(value > max)
  {
    return min;
  }

  return value;
}
//
// Base Core: Source
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// SAMPLE
//

//
// SAMPLE
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Linux main
//

// @note(aabib): X11 overview
//
// # links:
// https://hereket.com/posts/linux_creating_x11_windows/
// https://tronche.com/gui/x/xlib/introduction/overview.html
// https://tronche.com/gui/x/xlib/glossary/
// https://docs.rs/winit/latest/winit/platform/x11/index.html
//
// - The X Window System supports one or more screens containing overlapping windows or subwindows.
// - A screen is a physical monitor and hardware, which can be either color, grayscale, or monochrome.
//
// - Each window and pixmap has its own coordinate system. [0, 0] at the upper-left corner
// - Coordinates are integral, in terms of pixels, and coincide with pixel centers.
// - For a window, the origin is inside the border at the inside, upper-left corner.
//
// - X does not guarantee to preserve the contents of windows. When part or all of a window \
// is hidden and then brought back onto the screen, its contents may be lost.
// - The server then sends the client program an `Expose` event to notify it that part or all \
// of the window needs to be repainted.
//
// - X also provides off-screen storage of graphics objects, called pixmaps.
// - Single plane (depth 1) pixmaps are sometimes referred to as bitmaps.
// - Pixmaps can be used in most graphics functions interchangeably with windows and are used in \
// various graphics operations to define patterns or tiles.
// - Windows and pixmaps together are referred to as drawables.
//
// @note(aabib): Naming and Argument Conventions within Xlib
// https://tronche.com/gui/x/xlib/introduction/naming.html
//
// @note(aabib):
// Coordinates and sizes in X are actually 16-bit quantities.
// This decision was made to minimize the bandwidth required for a given level of performance.
// Coordinates usually are declared as an int in the interface.
// Values larger than 16 bits are truncated silently.
// Sizes (width and height) are declared as unsigned quantities.
//
fn_internal int
NILE_createWindowX11()
{
  // @syntax:
  // - Display *XOpenDisplay(display_name);
  // @argument: display_name
  // - char *display_name;
  // - Specifies the hardware display name, which determines the display \
  // and communications domain to be used.
  //  - On a POSIX-conformant system, if the display_name is NULL,
  //  it defaults to the value of the DISPLAY environment variable.
  // @return:
  // - If succeed , returns pointer to a Display (defined in X11/Xlib.h)
  // - If failed , returns NULL
  // https://tronche.com/gui/x/xlib/display/opening.html
  Display *main_display = XOpenDisplay(0);

  return 0;
}

fn_internal int
NILE_checkWindowEventX11()
{
    return 0;
}

//
// Linux main
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Windows main
//
fn_internal int
main_windows()
{
  return 0;
}
//
// Windows main
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// App main
//

typedef struct {
  uint8_t *Memory;
  uint64_t Size;
  uint32_t Width;
  uint32_t Height;
  uint32_t Pitch;
} Buffer;

typedef struct AppWindow {
  u32         x;
  u32         y;
  u32         width;
  u32         height;
  const char *name;
} AppWindow;

persist_global AppWindow app_window = (AppWindow){
    .width  = 1024,
    .height = 512,
    .x      = 0,
    .y      = 0,
    .name   = "Raycaster",
};

int
main()
{

  return 0;
}
//
// App main
// ----------------------------------------------------------------------------
