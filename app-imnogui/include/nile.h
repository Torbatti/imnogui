/*
 * Nile 0.1.0
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

/*
 *
 * @todo: cpp extern?
 *
 *
 *
 *
 *
 */

/*
 *
 * @links: ui/window/event/graphics
 * - https://github.com/ColleagueRiley/RGFW
 * - https://github.com/floooh/sokol
 * - https://github.com/glfw/glfw
 * - https://github.com/freeglut/freeglut
 * - https://docs.rs/winit/latest/winit/platform/index.html
 * - https://github.com/nicbarker/clay
 * - https://github.com/rxi/microui/
 * - https://github.com/ocornut/imgui
 * - https://github.com/david-vanderson/dvui
 * - https://www.gpui.rs/
 * - https://github.com/emilk/egui
 * - https://github.com/raysan5/raylib
 * - https://github.com/libsdl-org/SDL
 * - https://github.com/gfx-rs/wgpu
 * - https://github.com/kvark/blade
 *
 * @links: x11
 * - https://gitlab.freedesktop.org/xorg/lib/libx11
 * - https://www.x.org/releases/current/doc/libX11/libX11/libX11.html
 * - https://tronche.com/gui/x/xlib/
 * - https://hereket.com/posts/linux_creating_x11_windows/
 * - https://www.x.org/wiki/guide/xlib-and-xcb/
 * - https://www.x.org/wiki/Development/
 * - http://mech.math.msu.su/~vvb/2course/Borisenko/CppProjects/GWindow/xintro.html
 * - https://gaultier.github.io/blog/x11_x64.html
 * - https://magcius.github.io/xplain/article/index.html
 *
 * @links: wayland
 * - https://amini-allight.org/post/using-wayland-with-vulkan
 *
 * @links: win32
 *
 * @links: opengl
 *
 * @links: vulkan
 * - https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html
 *
 *  @links: directx
 *
 */

// https://semver.org/
#define NILE_VERSION_MAJOR 0
#define NILE_VERSION_MINOR 1
#define NILE_VERSION_PATCH 0

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define NILE_fn_internal static
#define NILE_fn_external extern

// ----------------------------------------------------------------------------
// Nile Platforms
//
#if defined(__linux__) || defined(__gnu_linux__)
# define NILE_PLATFORM_LINUX
#endif
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
# define NILE_PLATFORM_WINDOWS
# warning "Platform Not implemented Yet!"
#endif
#if defined(__ANDROID__)
# define NILE_PLATFORM_ANDROID
# warning "Platform Not implemented Yet!"
#endif
#if defined(__EMSCRIPTEN__)
# define NILE_PLATFORM_WASM
# warning "Platform Not implemented Yet!"
#endif
//
// Nile Platforms
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile Results
//
#define NILE_RESULT_SUCCESS 0
#define NILE_RESULT_FAIL    1
//
// Nile Results
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile Platform: Linux
//
#if defined(NILE_PLATFORM_LINUX)

// @todo(aabib): need something like glad for x11 for loading functions/constants
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
# include <tchar.h>
#endif
//
// Nile Platform: Windows
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile GRFX: OpenGL
//
#if defined(NILE_GRFX_OPENGL)

// @note: `GLAD_GL_IMPLEMENTATION` Enables Glad Gl
# define GLAD_GL_IMPLEMENTATION
# if defined(NILE_GRFX_OPENGL_V10)
#  include <glad/gl10core.h>
# endif
# if defined(NILE_GRFX_OPENGL_V11)
#  include <glad/gl11core.h>
# endif
# if defined(NILE_GRFX_OPENGL_V21)
#  include <glad/gl21core.h>
# endif
# if defined(NILE_GRFX_OPENGL_V33)
#  include <glad/gl33core.h>
# endif

// @brief(aabib): on linux if opengl(gapi) and x11(wapi) is selected , defaults to glx
# if defined(NILE_PLATFORM_LINUX) && defined(NILE_WINDOW_X11)
// @note: `GLAD_GLX_IMPLEMENTATION` Enables Glad GLX
#  define GLAD_GLX_IMPLEMENTATION
#  if defined(NILE_GLUE_GLX_LEGACY)
#   include <glad/glx10.h>
#  endif
#  if defined(NILE_GLUE_GLX_BASE)
#   include <glad/glx14.h>
#  endif
#  if defined(NILE_GLUE_GLX_MODERN)
#   include <glad/glx14modern.h>
#  endif
# endif

// @brief(aabib): on windows if opengl(gapi) is selected , defaults to wgl
# if defined(NILE_PLATFORM_WINDOWS)
// @note: `GLAD_WGL_IMPLEMENTATION` Enables Glad WGL
#  define GLAD_WGL_IMPLEMENTATION
#  include <glad/wgl10.h>
# endif

#endif
//
// Nile GRFX: OpenGL
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Nile GRFX: OpenGL ES
//
#if defined(NILE_GRFX_OPENGLES)
# define GLAD_GLES_IMPLEMENTATION // Enables Glad Gles

# if defined(NILE_GRFX_OPENGLES_V20)
#  include <glad/gles20.h>
# endif

# if defined(NILE_WINDOW_X11) || defined(NILE_WINDOW_WAYLAND)
#  define GLAD_EGL_IMPLEMENTATION // Enables Glad GLX
#  include <glad/egl15.h>         // Glad GLX Headers/Utils/Loaders
# endif

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
// Linux main
//
// Window: X11 , Wayland
// GRFX: opengl , opengl es , vulkan , wgpu
// Window Glue: Glx , Egl
// Input:
// Audio: Jack, Pulse , Pipewire
//

#if defined(NILE_PLATFORM_LINUX)

# if defined(NILE_WINDOW_X11)
//
// @todo: better error handling
// @todo: better logging
// @todo: better profiling
//
// @todo: software rendering
// @todo: glx legact and base
// @todo: add more info about glx modern with extension
//
// @todo: better naming for NILE_WindowX11 struct fields and struct name?
//
// @section(x11-):
// @section(x11-sm6sguct): x11-glx-modern create window overview
// - @section(x11-sm6sguct-ms896bep): idk?
// - @section(x11-sm6sguct-dbzvdgqa): create glx context
// - @section(x11-sm6sguct-rkrwvtxe): load gl from gladloader
// @section(x11-x49awnqj): x11-glx close window overview
// @section(x11-yzed2mnd): x11-glx swap window buffer overview

//
// @note(aabib): X11 overview
//
// @links:
// - https://hereket.com/posts/linux_creating_x11_windows/
// - https://tronche.com/gui/x/xlib/introduction/overview.html
// - https://tronche.com/gui/x/xlib/glossary/
// - https://docs.rs/winit/latest/winit/platform/x11/index.html
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
// @links:
// - https://tronche.com/gui/x/xlib/introduction/naming.html
//
// @note(aabib):
// - Coordinates and sizes in X are actually 16-bit quantities.
// - This decision was made to minimize the bandwidth required for a given level of performance.
// - Coordinates usually are declared as an int in the interface.
// - Values larger than 16 bits are truncated silently.
// - Sizes (width and height) are declared as unsigned quantities.
//

//
// @section(x11-sm6sguct-ms896bep): info
//
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
// @links:
// - https://tronche.com/gui/x/xlib/display/opening.html
//
//
// XCreateWindow , XCreateSimpleWindow
// @links:
// - https://tronche.com/gui/x/xlib/window/XCreateWindow.html
//
// Window XCreateWindow(display, parent, x, y, width, height, border_width, depth,
//                        class, visual, valuemask, attributes)
// Display *display;
// Window parent;
// int x, y;
// unsigned int width, height;
// unsigned int border_width;
// int depth;
// unsigned int class;
// Visual *visual
// unsigned long valuemask;
// XSetWindowAttributes *attributes;
//

typedef struct NILE_WindowX11 {
  // void      *_buffer;
  // Window     _root_window;
  Display   *display;
  Window     window;
  GLXContext context;
  Colormap   colormap;
} NILE_WindowX11;

// @section(x11-sm6sguct): start
NILE_fn_internal NILE_WindowX11 *
NILE_createWindow_X11_Modern(NILE_WindowX11 *winx11)
{

  //
  // @note: arena allocator like buffer
  //
  // uint64_t x11_buffer_cap = 4 * 1024 * 1024;
  // uint64_t x11_buffer_pos = 0;
  // void    *x11_buffer     = malloc(x11_buffer_cap);
  //

  // @section(x11-sm6sguct-ms896bep): start
  // @brief:
  Display *main_display = (Display *)XOpenDisplay(0);

  if(main_display == NULL)
  {
    printf("cannot connect to X server\n");
    return NULL;
  }
  int     default_screen = XDefaultScreen(main_display);
  Window  root_window    = XDefaultRootWindow(main_display);
  Visual *default_visual = DefaultVisual(main_display, default_screen);
  if(default_visual == NULL)
  {
    printf("cannot connect to X server\n");
    return NULL;
  }

  Colormap colormap = XCreateColormap(
      main_display, root_window, default_visual, AllocNone
  );

  int                  window_x            = 0;
  int                  window_y            = 0;
  int                  window_width        = 1024;
  int                  window_height       = 512;
  int                  window_border_width = 0;
  int                  window_depth        = CopyFromParent;
  int                  window_class        = CopyFromParent;
  Visual              *window_visual       = CopyFromParent;
  XSetWindowAttributes attributes;
  attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;
  attributes.colormap   = colormap;

  Window window = XCreateWindow(
      main_display, root_window, window_x, window_y, window_width,
      window_height, window_border_width,
      DefaultDepth(main_display, default_screen), InputOutput,
      default_visual, CWColormap | CWEventMask, &attributes
  );

  XMapWindow(main_display, window);
  XStoreName(main_display, window, "[glad] Modern GLX with X11");

  if(!window)
  {
    printf("Unable to create window.\n");
    return NULL;
  }
  // @section(x11-sm6sguct-ms896bep): end

  // @section(x11-sm6sguct-dbzvdgqa): start
  // @brief: glx modern context initialization
  int glx_version = gladLoaderLoadGLX(main_display, default_screen);
  if(!glx_version)
  {
    printf("Unable to load GLX.\n");
    return NULL;
  }
  printf(
      "Loaded GLX %d.%d\n", GLAD_VERSION_MAJOR(glx_version),
      GLAD_VERSION_MINOR(glx_version)
  );

  GLint visual_attributes []
      = {GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_DOUBLEBUFFER, 1, None};

  int          num_fbc = 0;
  GLXFBConfig *fbc     = glXChooseFBConfig(
      main_display, default_screen, visual_attributes, &num_fbc
  );

  GLint context_attributes []
      = {GLX_CONTEXT_MAJOR_VERSION_ARB,
         3,
         GLX_CONTEXT_MINOR_VERSION_ARB,
         3,
         GLX_CONTEXT_PROFILE_MASK_ARB,
         GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
         None};

  GLXContext context = glXCreateContextAttribsARB(
      main_display, fbc [0], NULL, 1, context_attributes
  );
  if(!context)
  {
    printf("Unable to create OpenGL context.\n");
    return NULL;
  }

  glXMakeCurrent(main_display, window, context);
  // @section(x11-sm6sguct-dbzvdgqa): end

  // @section(x11-sm6sguct-rkrwvtxe): start
  // @brief: load gl from gladloader
  int gl_version = gladLoaderLoadGL();
  if(!gl_version)
  {
    printf("Unable to load GL.\n");
    return NULL;
  }
  printf(
      "Loaded GL %d.%d\n", GLAD_VERSION_MAJOR(gl_version),
      GLAD_VERSION_MINOR(gl_version)
  );
  // @section(x11-sm6sguct-rkrwvtxe): end

  XWindowAttributes gwa;
  XGetWindowAttributes(main_display, window, &gwa);
  glViewport(0, 0, gwa.width, gwa.height);

  winx11->window   = window;
  winx11->context  = context;
  winx11->display  = main_display;
  winx11->colormap = colormap;

  return 0;
}
// @section(x11-sm6sguct): end

// @section(x11-x49awnqj): start
NILE_fn_internal int
NILE_closeWindow_X11_Modern(NILE_WindowX11 *win)
{
  glXMakeCurrent(win->display, 0, 0);
  glXDestroyContext(win->display, win->context);

  XDestroyWindow(win->display, win->window);
  XFreeColormap(win->display, win->colormap);
  XCloseDisplay(win->display);

  gladLoaderUnloadGLX();

  return NILE_RESULT_SUCCESS;
}
// @section(x11-x49awnqj): end

// @section(x11-yzed2mnd): start
NILE_fn_internal int
NILE_windowSwapBuffers_X11_Modern(NILE_WindowX11 *win)
{
  glXSwapBuffers(win->display, win->window);
  return 0;
}
// @section(x11-yzed2mnd): end

# endif

# if defined(NILE_WINDOW_WAYLAND)
# endif

#endif // NILE_PLATFORM_LINUX

//
// Linux main
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Windows main
//
#if defined(NILE_PLATFORM_WINDOWS)
NILE_fn_internal int
NILE_createWindow_X11()
{

  return 0;
}
//
// TODO: read what <THIS> does
// MessageBox MSDN
// GetSystemMetrics MSDN :
// // // Determine the resolution of the clients desktop screen.
// // screenWidth  = GetSystemMetrics(SM_CXSCREEN);
// // screenHeight = GetSystemMetrics(SM_CYSCREEN);
//

// NOTE(AABI) : Temporary persist_global
// persist_global BITMAPINFO BitmapInfo;       // TODO(AABI): remove later
// persist_global void      *BitmapMemory;     // TODO(AABI): remove later
// persist_global int        BitmapWidth;      // TODO(AABI): remove later
// persist_global int        BitmapHeight;     // TODO(AABI): remove later
// persist_global int        BytePerPixel = 4; // TODO(AABI): remove later
// persist_global b8         Win32_G_DefaultWindowRunning = true;

//
// ???
//
// NOTE(AABIB):
//   A callback function, that processes messages sent to a window
//   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc
//   https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure
//   https://learn.microsoft.com/en-us/windows/win32/winmsg/window-notifications
//   https://learn.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues#system-defined-messages
//
NILE_fn_internal LRESULT CALLBACK
NILE_win32_defaultWindowCallback(
    HWND Window, UINT Message, WPARAM WParam, LPARAM LParam
)
{
  LRESULT Resault = 0;

  switch(Message)
  {
    case WM_SIZE :
      {
        OutputDebugStringA("WM_SIZE\n");
      }
      break;

    case WM_DESTROY :
      {
        // TODO: Handle this as an error - recreate window
        Win32_G_DefaultWindowRunning = false;
        OutputDebugStringA("WM_DESTROY\n");
      }
      break;

    case WM_CLOSE :
      {
        // TODO: Handle this with a message to the user
        Win32_G_DefaultWindowRunning = false;
        PostQuitMessage(0);

        OutputDebugStringA("WM_CLOSE\n");
      }
      break;

    case WM_ACTIVATEAPP :
      {
        OutputDebugStringA("WM_ACTIVATEAPP\n");
      }
      break;

    // paint when windows is blocking -- hmh ep5 90:20
    case WM_PAINT :
      {
        PAINTSTRUCT Paint;

        HDC DeviceContext = BeginPaint(Window, &Paint);

        LONG X      = Paint.rcPaint.left;
        LONG Y      = Paint.rcPaint.top;
        LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
        LONG Width  = Paint.rcPaint.right - Paint.rcPaint.left;

        RECT ClientRect;
        GetClientRect(Window, &ClientRect);

        //
        //
        //  Win32_DisplayBufferWindow
        int WindowWidth  = ClientRect.right - ClientRect.left;
        int WindowHeight = ClientRect.bottom - ClientRect.top;

        StretchDIBits(
            DeviceContext, 0, 0, WindowWidth, WindowHeight, 0, 0,
            BitmapWidth, BitmapHeight, BitmapMemory, &BitmapInfo,
            DIB_RGB_COLORS, SRCCOPY
        );

        BOOL EndPaintResault = EndPaint(Window, &Paint);
      }
      break;

    default :
      Resault = DefWindowProcA(Window, Message, WParam, LParam);
      break;
  }

  return (Resault);
}

//
// ????
//
// NOTE(AABIB):
//   https://learn.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
//   https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
//
// TODO(AABIB):
//   When can we get a hdc and where do we get it?
//
// @notes:
// - An excerpt from the book Windows Via C/C++ [1]
// - Note As it turns out, HMODULEs and HINSTANCEs are exactly the same thing. If the \
// documentation for a function indicates that an HMODULE is required, you can pass an \
// HINSTANCE and vice versa. There are two data types because in 16-bit Windows HMODULEs \
// and HINSTANCEs identified different things/
// - [1] Richter, Jeffery and Nasarre, Christophe, Windows Via C/C++, 5th ed, Redmond: Microsoft Press 2008, pp. 74
//
// @links:
// - https://stackoverflow.com/questions/2126657/how-can-i-get-hinstance-from-a-dll
// - https://devblogs.microsoft.com/oldnewthing/20040614-00/?p=38903
// - https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlea
//
// @notes: wgl extensions
// - https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
//
int CALLBACK
WinMain(
    HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine,
    int ShowCmd
)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  //
  // Window Base Configs
  //
  u32 WindowWidth  = 1280;
  u32 WindowHeight = 720;

  //
  // Window Class
  //
  // NOTE(AABI):
  //   WNDCLASSEX (A/W) -> RegisterClassEx and GetClassInfoEx
  //   maximum length of lpszClassName is 256
  //   https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa
  //   https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexa
  //
  // NOTE(AABI):
  //   When you create your HWND, you need to make sure that it has the CS_OWNDC set for its style.
  //   https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL)
  //   https://learn.microsoft.com/en-us/windows/win32/api/_opengl/
  //
  WNDCLASSEXA window_class_exa   = {0};
  window_class_exa.cbSize        = sizeof(WNDCLASSEX);
  window_class_exa.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
  window_class_exa.lpfnWndProc   = Win32_DefaultWindowCallback;
  window_class_exa.cbClsExtra    = 0;
  window_class_exa.cbWndExtra    = 0;
  window_class_exa.hInstance     = Instance;
  window_class_exa.hIcon         = 0;
  window_class_exa.hCursor       = 0; // LoadCursor(NULL, IDC_ARROW)
  window_class_exa.hbrBackground = 0; // (HBRUSH) (COLOR_WINDOW + 1);
  window_class_exa.lpszMenuName  = 0;
  window_class_exa.lpszClassName = "MainWindowClass";
  window_class_exa.hIconSm       = 0;

  //
  // Create DIB seaction?
  // DEP: Win32_ResizeDIBSection()
  //
  // NOTE(AABI) : DIB -> device independant bitmap
  // TODO(AABI): WHY bmiheader -height vs +height
  //
  if(BitmapMemory)
  {
    VirtualFree(BitmapMemory, 0, MEM_RELEASE);
  }

  BitmapWidth  = WindowWidth;
  BitmapHeight = WindowHeight;

  BitmapInfo.bmiHeader.biSize          = sizeof(BitmapInfo.bmiHeader);
  BitmapInfo.bmiHeader.biWidth         = BitmapWidth;
  BitmapInfo.bmiHeader.biHeight        = -BitmapHeight;
  BitmapInfo.bmiHeader.biPlanes        = 1;
  BitmapInfo.bmiHeader.biBitCount      = 32;
  BitmapInfo.bmiHeader.biCompression   = BI_RGB;
  BitmapInfo.bmiHeader.biSizeImage     = 0;
  BitmapInfo.bmiHeader.biXPelsPerMeter = 0;
  BitmapInfo.bmiHeader.biYPelsPerMeter = 0;
  BitmapInfo.bmiHeader.biClrUsed       = 0;
  BitmapInfo.bmiHeader.biClrImportant  = 0;

  int BitmapMemorySize = (BitmapWidth * BitmapHeight) * BytePerPixel;
  if(BitmapMemorySize == 0)
  {
    printf("Bitmap memory size SHOULD NOT be 0");
    return (0);
  }

  BitmapMemory
      = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);

  //
  // Register Class
  //
  ATOM registerclass_resault = RegisterClassExA(&window_class_exa);
  if(registerclass_resault == 0)
  {
    // TODO(AABI): you have the error -> handle or print it
    DWORD registerclass_err = GetLastError();
    printf("registerclass failed, err: %lu ", registerclass_err);
    return 0; // exit program if register fails
  }

  //
  // Create Window
  //
  LPCSTR Win32_MainWindowName       = "Main Window";
  HWND   createwindowhandle_resault = CreateWindowExA(
      0, window_class_exa.lpszClassName, Win32_MainWindowName,
      WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, Instance, 0
  );
  if(createwindowhandle_resault == 0)
  {
    // TODO(AABI): you have the error -> handle or print it
    DWORD createwindow_err = GetLastError();
    printf("createwindow failed, err: %lu ", createwindow_err);
    return 0; // exit program if register fails
  }
  HDC DeviceContext = GetDC(createwindowhandle_resault);

  // HWND   hWnd                 = CreateWindow(
  //     MAKEINTATOM(wndclass), window_title, WS_OVERLAPPEDWINDOW,
  //     window_location.x, window_location.y, window_size.cx,
  //     window_size.cy, NULL, NULL, hInstance, NULL
  // );

  //
  // ??????
  //
  if(Win32_G_DefaultWindowRunning == false)
  {
    // NOTE(AABI): this should have not happened
    // TODO(AABI): Add Logging/Assert so we know this went wrong
    Win32_G_DefaultWindowRunning = true;

    printf("err: default running window is false before starting");
    // return 0;
  }

  //
  //
  //
# if defined(NILE_GRFX_OPENGL)
  // Set the pixel format for the device context:
  PIXELFORMATDESCRIPTOR pfd = {};
  pfd.nSize                 = sizeof(pfd);
  pfd.nSize                 = sizeof(
      PIXELFORMATDESCRIPTOR
  ); // Set the size of the PFD to the size of the class
  pfd.dwFlags
      = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL
      | PFD_DRAW_TO_WINDOW; // Enable double buffering, opengl support and drawing to a window
  pfd.iPixelType
      = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
  pfd.cColorBits
      = 32; // Give us 32 bits of color information (the higher, the more colors)
  pfd.cDepthBits
      = 32; // Give us 32 bits of depth information (the higher, the more depth levels)
  pfd.iLayerType = PFD_MAIN_PLANE; // Set the layer of the PFD
  int format     = ChoosePixelFormat(hdc, &pfd);
  if(format == 0 || SetPixelFormat(hdc, format, &pfd) == FALSE)
  {
    ReleaseDC(hWnd, hdc);
    DestroyWindow(hWnd);
    MessageBox(
        NULL, _T("Failed to set a compatible pixel format!"),
        window_title, MB_ICONERROR
    );
    return -1;
  }
  // Create and enable a temporary (helper) opengl context:
  HGLRC temp_context = NULL;
  if(NULL == (temp_context = wglCreateContext(hdc)))
  {
    ReleaseDC(hWnd, hdc);
    DestroyWindow(hWnd);
    MessageBox(
        NULL, _T("Failed to create the initial rendering context!"),
        window_title, MB_ICONERROR
    );
    return -1;
  }
  wglMakeCurrent(hdc, temp_context);

  // Load WGL Extensions:
  gladLoaderLoadWGL(hdc);

  // Set the desired OpenGL version:
  int attributes [] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB,
      3, // Set the MAJOR version of OpenGL to 3
      WGL_CONTEXT_MINOR_VERSION_ARB,
      2, // Set the MINOR version of OpenGL to 2
      WGL_CONTEXT_FLAGS_ARB,
      WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
      0
  };

  // Create the final opengl context and get rid of the temporary one:
  HGLRC opengl_context = NULL;
  if(NULL
     == (opengl_context
         = wglCreateContextAttribsARB(hdc, NULL, attributes)))
  {
    wglDeleteContext(temp_context);
    ReleaseDC(hWnd, hdc);
    DestroyWindow(hWnd);
    MessageBox(
        NULL, _T("Failed to create the final rendering context!"),
        window_title, MB_ICONERROR
    );
    return -1;
  }
  wglMakeCurrent(
      NULL, NULL
  ); // Remove the temporary context from being active
  wglDeleteContext(temp_context); // Delete the temporary OpenGL context
  wglMakeCurrent(
      hdc, opengl_context
  ); // Make our OpenGL 3.2 context current

  // Glad Loader!
  if(!gladLoaderLoadGL())
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(opengl_context);
    ReleaseDC(hWnd, hdc);
    DestroyWindow(hWnd);
    MessageBox(
        NULL, _T("Glad Loader failed!"), window_title, MB_ICONERROR
    );
    return -1;
  }

  // Show & Update the main window:
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
# endif // NILE_GRFX_OPENGL
  //
  //
  // NOTE(AABIB):
  //   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage
  //
  int XOffset = 0;
  int YOffset = 0;
  MSG Message;
  while(Win32_G_DefaultWindowRunning)
  {
    //
    // ??????
    //
    while(true) // WARN(AABI): infinite loop can happen
    {
      // NOTE(AABI): Funny enough peekmessage used to return -1 on err xD
      // If a message is available, the return value is nonzero.
      // If no messages are available, the return value is zero.
      BOOL peekmessage_resault
          = PeekMessageA(&Message, 0, 0, 0, PM_REMOVE);

      if(peekmessage_resault == 0)
      {
        // NOTE(AABI): exit this while loop if theres no msg
        break;
      }

      // NOTE(AABI): make sure quit is handled
      if(Message.message == WM_QUIT)
      {
        Win32_G_DefaultWindowRunning = false;
      }

      // TODO(AABI): handle error
      TranslateMessage(&Message);
      DispatchMessageA(&Message);
    }

    // @todo: add xinput controller handling loop here

    //
    // Render Weird Gradient
    //
    // NOTES(AABI):
    //   PITCH: memory size of each row in bytes
    int Width  = BitmapWidth;
    int Height = BitmapHeight;
    int Pitch  = Width * BytePerPixel;
    u8 *Row    = (u8 *)BitmapMemory;
    for(int Y = 0; Y < BitmapHeight; ++Y)
    {
      u32 *Pixel = (u32 *)Row;
      for(int X = 0; X < BitmapWidth; ++X)
      {
        *Pixel = ((u32)(u8)(Y + YOffset) << (8 * 0))
               + ((u32)(u8)(X + XOffset) << (8 * 1))
               + ((u32)0 << (8 * 2)) + ((u32)0 << (8 * 3));
        ++Pixel;
      }
      Row += Pitch;
    }

    //
    // ????
    //
    RECT ClientRect;
    GetClientRect(createwindowhandle_resault, &ClientRect);

    int WindowWidth  = ClientRect.right - ClientRect.left;
    int WindowHeight = ClientRect.bottom - ClientRect.top;

    StretchDIBits(
        DeviceContext, 0, 0, WindowWidth, WindowHeight, 0, 0,
        BitmapWidth, BitmapHeight, BitmapMemory, &BitmapInfo,
        DIB_RGB_COLORS, SRCCOPY
    );

    ReleaseDC(createwindowhandle_resault, DeviceContext);

    //
    // Offsets for Rendering Weird Gradient
    //
    ++XOffset;
    ++YOffset;

# if defined(NILE_GRFX_OPENGL)
// glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
// glClear(GL_COLOR_BUFFER_BIT);
// SwapBuffers(hdc);
# endif
  }

  // Clean-up:
# if defined(NILE_GRFX_OPENGL)
  if(opengl_context)
    wglDeleteContext(opengl_context);
# endif

  ReleaseDC(createwindowhandle_resault, DeviceContext);
  // if(hdc)
  // ReleaseDC(hWnd, hdc);
  // if(hWnd)
  // DestroyWindow(hWnd);

  return (0);
}
#endif // NILE_PLATFORM_WINDOWS

//
// Windows main
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Android main
//
#if defined(NILE_PLATFORM_ANDROID)
NILE_fn_internal int
NILE_createWindow_Android()
{

  return 0;
}
#endif // NILE_PLATFORM_ANDROID
//
// Android main
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Cross Window
//

// @todo: find a way to not pass void pointers
typedef struct NILE_Window {
  void *window_x11;
  void *window_win32;
  void *window_android;
  void *window_wasm;
  void *window_macos;
  void *window_ios;
} NILE_Window;

NILE_fn_internal NILE_Window *
NILE_createWindow(
    const char *name, int x, int y, int w, int h, int flags
)
{
  NILE_Window *window = (NILE_Window *)malloc(sizeof(NILE_Window));

#if defined(NILE_WINDOW_X11)
  window->window_x11 = (NILE_WindowX11 *)malloc(sizeof(NILE_WindowX11));

  NILE_WindowX11 *windowX11
      = NILE_createWindow_X11_Modern(window->window_x11);
  if(windowX11 != NULL)
  {
    window->window_x11 = windowX11;
  }
#endif

  return window;
}

NILE_fn_internal int
NILE_closeWindow(NILE_Window *window)
{

#if defined(NILE_WINDOW_X11)
  if(window->window_x11 != NULL)
  {
    free(window->window_x11);
  }
#endif

  free(window);
  return 0;
}

NILE_fn_internal int
NILE_windowSwapBuffers(NILE_Window *window)
{

#if defined(NILE_WINDOW_X11)
  if(window->window_x11 != NULL)
  {
    int result = NILE_windowSwapBuffers_X11_Modern(window->window_x11);
  }
#endif

  return 0;
}

//
// Cross Window
// ----------------------------------------------------------------------------
