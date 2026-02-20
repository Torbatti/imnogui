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

#define NILE_PLATFORM_WINDOWS
#define NILE_WINDOW_WIN32
#define NILE_GLUE_WGL
#define NILE_GLUE_WGL_MODERN
#define NILE_GRFX_OPENGL
#define NILE_GRFX_OPENGL_V33

// https://semver.org/
#define NILE_VERSION_MAJOR 0
#define NILE_VERSION_MINOR 1
#define NILE_VERSION_PATCH 0

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// #include <unistd.h>

#define NILE_persist_global static
#define NILE_persist_local  static
#define NILE_fn_internal    static
#define NILE_fn_external    extern

#define NILE_RESULT_SUCCESS 0
#define NILE_RESULT_FAIL    1

#define NILE_assert assert

// ----------------------------------------------------------------------------
// Nile Platforms
//
#if defined(__linux__) || defined(__gnu_linux__)
# define NILE_PLATFORM_LINUX
#endif
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
# define NILE_PLATFORM_WINDOWS
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
#  if defined(NILE_GLUE_GLX)
#   define GLAD_GLX_IMPLEMENTATION
#  endif
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
#  if defined(NILE_GLUE_WGL)
#   define GLAD_WGL_IMPLEMENTATION
#  endif
#  if defined(NILE_GLUE_WGL_BASE)
#   include <glad/wgl10.h>
#  endif
#  if defined(NILE_GLUE_WGL_MODERN)
#   include <glad/wgl10modern.h>
#  endif

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
// - @section(x11-sm6sguct-kfnzz886): get window attributes + set glviewport if gl/glx is enabled
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
#  if defined(NILE_GRFX_OPENGL) && defined(NILE_GLUE_GLX)
NILE_fn_internal int
NILE_createWindow_X11_GLX(NILE_WindowX11 *winx11)
{
  NILE_assert(winx11 != NULL);

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
    return NILE_RESULT_FAIL;
  }
  NILE_assert(main_display != NULL);

  int    default_screen = XDefaultScreen(main_display);
  Window root_window    = XDefaultRootWindow(main_display);
  // @section(x11-sm6sguct-ms896bep): end

  // @section(x11-sm6sguct-dbzvdgqa): start
  // @brief: glx modern context initialization
  // @todo: rework and rename this!
  int glx_version = gladLoaderLoadGLX(main_display, default_screen);
  if(!glx_version)
  {
    printf("Unable to load GLX.\n");
    return NILE_RESULT_FAIL;
  }
  printf(
      "Loaded GLX %d.%d\n", GLAD_VERSION_MAJOR(glx_version),
      GLAD_VERSION_MINOR(glx_version)
  );

  // @todo: new section start
#   if defined(NILE_GLUE_GLX_BASE)
  GLint visual_attributes [] = {GLX_RGBA, GLX_DOUBLEBUFFER, None};
  XVisualInfo *visual_info   = glXChooseVisual(
      main_display, default_screen, visual_attributes
  );
  if(visual_info == NULL)
  {
    printf("cannot connect to X server\n");
    return NILE_RESULT_FAIL;
  }
  NILE_assert(visual_info != NULL);

  Colormap colormap = XCreateColormap(
      main_display, root_window, visual_info->visual, AllocNone
  );
#   endif
#   if defined(NILE_GLUE_GLX_MODERN)
  Visual *default_visual = DefaultVisual(main_display, default_screen);
  if(default_visual == NULL)
  {
    printf("cannot connect to X server\n");
    return NILE_RESULT_FAIL;
  }
  Colormap colormap = XCreateColormap(
      main_display, root_window, default_visual, AllocNone
  );
#   endif
  // @todo: new section end

  // @todo: new section start
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
  // @todo: new section end

  // @todo: new section start
#   if defined(NILE_GLUE_GLX_BASE)
  Window window = XCreateWindow(
      main_display, root_window, window_x, window_y, window_width,
      window_height, window_border_width,
      DefaultDepth(main_display, default_screen), InputOutput,
      visual_info->visual, CWColormap | CWEventMask, &attributes
  );
#   endif
#   if defined(NILE_GLUE_GLX_MODERN)
  Window window = XCreateWindow(
      main_display, root_window, window_x, window_y, window_width,
      window_height, window_border_width,
      DefaultDepth(main_display, default_screen), InputOutput,
      default_visual, CWColormap | CWEventMask, &attributes
  );
#   endif
  // @todo: new section end

  XMapWindow(main_display, window);
  XStoreName(
      main_display, window,
      "[glad] Modern/Base GLX with X11 - this is intentional"
  );

  if(!window)
  {
    printf("Unable to create window.\n");
    return NILE_RESULT_FAIL;
  }

  // @todo: new section start
#   if defined(NILE_GLUE_GLX_BASE)
  GLXContext context
      = glXCreateContext(main_display, visual_info, NULL, GL_TRUE);
#   endif
#   if defined(NILE_GLUE_GLX_MODERN)
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
    return NILE_RESULT_FAIL;
  }
#   endif
  // @todo: new section end

  glXMakeCurrent(main_display, window, context);
  // @section(x11-sm6sguct-dbzvdgqa): end

  // @section(x11-sm6sguct-rkrwvtxe): start
  // @brief: load gl from gladloader
  int gl_version = gladLoaderLoadGL();
  if(!gl_version)
  {
    printf("Unable to load GL.\n");
    return NILE_RESULT_FAIL;
  }
  printf(
      "Loaded GL %d.%d\n", GLAD_VERSION_MAJOR(gl_version),
      GLAD_VERSION_MINOR(gl_version)
  );
  // @section(x11-sm6sguct-rkrwvtxe): end

  // @section(x11-sm6sguct-kfnzz886): start
  XWindowAttributes gwa;
  XGetWindowAttributes(main_display, window, &gwa);
  glViewport(0, 0, gwa.width, gwa.height);
  // @section(x11-sm6sguct-kfnzz886): end

  NILE_assert(main_display != NULL);
  winx11->window   = window;
  winx11->context  = context;
  winx11->display  = main_display;
  winx11->colormap = colormap;

  return 0;
}
// @section(x11-sm6sguct): end

// @section(x11-x49awnqj): start
NILE_fn_internal int
NILE_closeWindow_X11_GLX(NILE_WindowX11 *win)
{
  NILE_assert(winx11 != NULL);
  NILE_assert(win->display != NULL);

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
NILE_windowSwapBuffers_X11_GLX(NILE_WindowX11 *win)
{
  NILE_assert(winx11 != NULL);
  glXSwapBuffers(win->display, win->window);
  return 0;
}
// @section(x11-yzed2mnd): end

#  endif
// @endif: defined(NILE_GRFX_OPENGL) && defined(NILE_GLUE_GLX)

# endif
// @endif: defined(NILE_WINDOW_X11)

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
typedef struct NILE_Window_Win32 {
  HWND  hwindow;
  HDC   hcontext;
  HGLRC hgl_context;
} NILE_Window_Win32;

LRESULT CALLBACK
NILE_win32_defaultWindowCallback(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
)
{
  LRESULT Resault = 0;

  switch(uMsg)
  {
    case WM_QUIT :
    case WM_CLOSE   : DestroyWindow(hWnd); break;
    case WM_DESTROY : PostQuitMessage(0); break;
    default         : return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  return (Resault);
}

NILE_fn_internal int
NILE_createWindow_WIN32_WGL(NILE_Window_Win32 *win32)
{
  NILE_assert(win32 != NULL);

  // @section(): start
  HMODULE Instance = GetModuleHandleA(NULL);
  assert(Instance != NULL);
  // @section(): end

  // @section(): start
  WNDCLASSEXA window_class_exa = {0};
  window_class_exa.cbSize      = sizeof(WNDCLASSEXA);
  window_class_exa.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
  window_class_exa.lpfnWndProc   = NILE_win32_defaultWindowCallback;
  window_class_exa.cbClsExtra    = 0;
  window_class_exa.cbWndExtra    = 0;
  window_class_exa.hInstance     = Instance;
  window_class_exa.hIcon         = 0;
  window_class_exa.hCursor       = 0; // LoadCursor(NULL, IDC_ARROW)
  window_class_exa.hbrBackground = 0; // (HBRUSH) (COLOR_WINDOW + 1);
  window_class_exa.lpszMenuName  = 0;
  window_class_exa.lpszClassName = "MainWindowClass";
  window_class_exa.hIconSm       = 0;

  ATOM registerclass = RegisterClassExA(&window_class_exa);
  if(registerclass == 0)
  {
    // @todo: handle this
    DWORD registerclass_err = GetLastError();
    printf("registerclass failed, err: %lu ", registerclass_err);
    return 1;
  }
  // @section(): end

  // @section(): start
  //
  LPCSTR Win32_MainWindowName = "Main Window";
  int    window_x             = CW_USEDEFAULT;
  int    window_y             = CW_USEDEFAULT;
  int    window_width         = CW_USEDEFAULT; // CW_USEDEFAULT
  int    window_height        = CW_USEDEFAULT; // CW_USEDEFAULT
  HWND HWindow = CreateWindowExA(
      0, window_class_exa.lpszClassName, Win32_MainWindowName,
      WS_OVERLAPPEDWINDOW | WS_VISIBLE, window_x, window_y,
      window_width, window_height, 0, 0, Instance, 0
  );
  if(HWindow == NULL)
  {
    // @todo: handle this
    DWORD createwindow_err = GetLastError();
    printf("createwindow failed, err: %lu ", createwindow_err);
    return 1;
  }
  NILE_assert(HWindow != NULL);
  // @section(): end

  // @section(): start
  HDC HDeviceContext = GetDC(HWindow);
  if(HDeviceContext == 0)
  {
    // @todo: handle this
    puts("HDeviceContext failed");
    return 1;
  }
  NILE_assert(HDeviceContext != NULL);

  PIXELFORMATDESCRIPTOR pfd = {};
  pfd.nSize                 = sizeof(pfd);
  pfd.nSize                 = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.dwFlags
      = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  pfd.iLayerType = PFD_MAIN_PLANE;
  int format     = ChoosePixelFormat(HDeviceContext, &pfd);
  if(format == 0
     || SetPixelFormat(HDeviceContext, format, &pfd) == FALSE)
  {
    puts("SetPixelFormat failed");
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);
    MessageBox(
        NULL, _T("Failed to set a compatible pixel format!"),
        Win32_MainWindowName, MB_ICONERROR
    );
    return -1;
  }
// @section(): end

// @section(): start
# if defined(NILE_GLUE_WGL_MODERN)
  HGLRC temp_context = NULL;
  if(NULL == (temp_context = wglCreateContext(HDeviceContext)))
  {
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);
    MessageBox(
        NULL, _T("Failed to create the initial rendering context!"),
        Win32_MainWindowName, MB_ICONERROR
    );
    return -1;
  }
  wglMakeCurrent(HDeviceContext, temp_context);

  // Load WGL Extensions:
  gladLoaderLoadWGL(HDeviceContext);

  // Set the desired OpenGL version:
  int attributes []
      = {WGL_CONTEXT_MAJOR_VERSION_ARB,
         3,
         WGL_CONTEXT_MINOR_VERSION_ARB,
         2,
         WGL_CONTEXT_FLAGS_ARB,
         WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
         0};

  // Create the final opengl context and get rid of the temporary one:
  HGLRC opengl_context = NULL;
  if(NULL
     == (opengl_context = wglCreateContextAttribsARB(
             HDeviceContext, NULL, attributes
         )))
  {
    wglDeleteContext(temp_context);
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);
    MessageBox(
        NULL, _T("Failed to create the final rendering context!"),
        Win32_MainWindowName, MB_ICONERROR
    );
    return -1;
  }
  wglMakeCurrent(
      NULL, NULL
  ); // Remove the temporary context from being active
  wglDeleteContext(temp_context); // Delete the temporary OpenGL context
  wglMakeCurrent(
      HDeviceContext, opengl_context
  ); // Make our OpenGL 3.2 context current
# endif
  // @section(): end

  // @section(): start
  //  Glad Loader!
  if(!gladLoaderLoadGL())
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(opengl_context);
    ReleaseDC(HWindow, HDeviceContext);
    DestroyWindow(HWindow);
    MessageBox(
        NULL, _T("Glad Loader failed!"), Win32_MainWindowName,
        MB_ICONERROR
    );
    return -1;
  }
  // Show & Update the main window:
  // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow

  ShowWindow(HWindow, SW_SHOWDEFAULT);
  UpdateWindow(HWindow);
  // @section(): end

  // @section(): start
  //
  NILE_assert(HDeviceContext != NULL);
  NILE_assert(HWindow != NULL);
  NILE_assert(opengl_context != NULL);
  win32->hcontext    = HDeviceContext;
  win32->hwindow     = HWindow;
  win32->hgl_context = opengl_context;
  // @section(): end

  // @section(): start
  // @section(): end

  return 0;
}

NILE_fn_internal int
NILE_closeWindow_WIN32_WGL(NILE_Window_Win32 *win32)
{
  NILE_assert(win32 != NULL);
  NILE_assert(win32->hgl_context != NULL);
  NILE_assert(win32->hcontext != NULL);
  NILE_assert(win32->hwindow != NULL);

  // Clean-up:
  if(win32->hgl_context)
    wglDeleteContext(win32->hgl_context);
  if(win32->hcontext)
    ReleaseDC(win32->hwindow, win32->hcontext);
  if(win32->hwindow)
    DestroyWindow(win32->hwindow);

  return 0;
}

NILE_fn_internal int
NILE_windowSwapBuffers_WIN32_WGL(NILE_Window_Win32 *win32)
{
  NILE_assert(win32 != NULL);
  NILE_assert(win32->hgl_context != NULL);
  NILE_assert(win32->hcontext != NULL);
  NILE_assert(win32->hwindow != NULL);

  SwapBuffers(win32->hcontext);
  return 0;
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
  NILE_assert(window->window_x11 != NULL);

  int createWindow_result
      = NILE_createWindow_X11_GLX((NILE_WindowX11 *)window->window_x11);
#endif
#if defined(NILE_WINDOW_WIN32)
  window->window_win32
      = (NILE_Window_Win32 *)malloc(sizeof(NILE_Window_Win32));
  NILE_assert(window->window_win32 != NULL);

  int createWindow_result = NILE_createWindow_WIN32_WGL(
      (NILE_Window_Win32 *)window->window_win32
  );

  free((NILE_Window_Win32 *)window->window_win32);
#endif
  assert(createWindow_result == 0);

  return window;
}

NILE_fn_internal int
NILE_closeWindow(NILE_Window *window)
{

#if defined(NILE_WINDOW_X11)
  NILE_assert(window->window_x11 != NULL);
  int closeWindow_result
      = NILE_closeWindow_X11_GLX((NILE_WindowX11 *)window->window_x11);

  free((NILE_WindowX11 *)window->window_x11);
#endif
#if defined(NILE_WINDOW_WIN32)
  NILE_assert(window->window_win32 != NULL);
  int closeWindow_result
      = NILE_closeWindow_WIN32_WGL(window->window_win32);

  free((NILE_Window_Win32 *)window->window_win32);
#endif

  free(window);
  return 0;
}

NILE_fn_internal int
NILE_windowSwapBuffers(NILE_Window *window)
{

#if defined(NILE_WINDOW_X11)
  NILE_assert(window->window_x11 != NULL);
  int result = NILE_windowSwapBuffers_X11_GLX(window->window_x11);
#endif
#if defined(NILE_WINDOW_WIN32)
  NILE_assert(window->window_win32 != NULL);
  int result = NILE_windowSwapBuffers_WIN32_WGL(window->window_win32);
#endif

  return 0;
}

//
// Cross Window
// ----------------------------------------------------------------------------
