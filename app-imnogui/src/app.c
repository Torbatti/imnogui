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

// @todo(aabib): this needs fixing!!! cant use it this way it feels too cumbersome!
// @todo(aabib): windows windowing api needs a better name than `win32`
#include "../include/defd.h"
#if defined(DEFD_PLATFORM_LINUX)
# define NILE_PLATFORM_LINUX
# define NILE_WINDOW_X11
# define NILE_GLUE_GLX
# define NILE_GLUE_GLX_BASE
// # define NILE_GLUE_GLX_MODERN
# define NILE_GRFX_OPENGL
# define NILE_GRFX_OPENGL_V33
#endif
#if defined(DEFD_PLATFORM_WINDOWS)
# define NILE_PLATFORM_WINDOWS
# define NILE_WINDOW_WIN32
# define NILE_GLUE_WGL
# define NILE_GLUE_WGL_MODERN
# define NILE_GRFX_OPENGL
# define NILE_GRFX_OPENGL_V33
#endif

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#if defined(DEFD_PLATFORM_LINUX)
# include <unistd.h>
#endif

#include "../include/nile.h"
#include "../include/base-core.h"

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
    .name   = "ImNoGui",
};

int
main()
{

  NILE_Window *window = NILE_createWindow(
      app_window.name, app_window.x, app_window.y, app_window.width,
      app_window.height, (u64)0
  );
  assert(window != NULL);

  int quit = false;
  while(!quit)
  {

#if defined(NILE_WINDOW_X11)
    while(XPending(((NILE_WindowX11 *)window->window_x11)->display))
    {
      XEvent xev;
      XNextEvent(((NILE_WindowX11 *)window->window_x11)->display, &xev);

      if(xev.type == KeyPress)
      {
        quit = true;
      }
    }
#endif

    glClearColor(0.8, 0.6, 0.7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    NILE_windowSwapBuffers(window);

#if defined(NILE_PLATFORM_LINUX)
    usleep(1000 * 10);
#endif
#if defined(NILE_PLATFORM_WINDOWS)
    Sleep(1000 * 10);
#endif
  }

  int close_window_resault = NILE_closeWindow(window);

  return 0;
}
//
// App main
// ----------------------------------------------------------------------------
