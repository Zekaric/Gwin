/**************************************************************************************************
file:       GwinWindow
author:     Robbert de Groot
company:    Zekaric
copyright:  2025, Zekaric

description:
Gwin Window routines.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2025, Robbert de Groot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/
static void _DefaultNotifyRender(GwinWindow * const win);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gwinWindowAddItem
**************************************************************************************************/
GWIN_API Gi4 gwinWindowAddItem(GwinWindow * const win, GwinItem * const item)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win             ||
      !item);

   // If there are holes in the item array then reuse the hole.
   if (gv4ArrayGetCount(win->itemHoleIndexArray))
   {
      // Get an index from the hole indes array.  Last one is fast.
      index = gv4ArrayGetEnd(win->itemHoleIndexArray)->i;

      // Remove the index from the hole index array.
      gv4ArrayEraseEnd(win->itemHoleIndexArray);

      gwinItemArrayUpdateAt(win->itemArray, index, item);

      greturn index;
   }

   // Append to the item array.
   gwinItemArrayAddEnd(win->itemArray, item);

   index = gwinItemArrayGetCount(win->itemArray) - 1;

   greturn index;
}

/**************************************************************************************************
func: gwinWindowCloc
**************************************************************************************************/
GWIN_API GwinWindow *gwinWindowCloc(void)
{
   genter;

   GwinWindow *win;

   greturnNullIf(!gwinIsStarted());

   win = gmemClocType(GwinWindow);
   greturnNullIf(!win);

   if (!gwinWindowClocContent(win))
   {
      gmemDloc(win);
      greturn NULL;
   }

   greturn win;
}

/**************************************************************************************************
func: gwinWinClocContent
**************************************************************************************************/
GWIN_API Gb gwinWindowClocContent(GwinWindow * const win)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win);

   gmemClearType(win, GwinWindow);

   GTYPE_SET(win, "GwinWindow");

   win->itemArray          = gwinItemArrayCloc();
   win->itemHoleIndexArray = gv4ArrayCloc(NULL, gbTRUE);
   win->notifyRender       = _DefaultNotifyRender;
   win->windowIndex        = gwinAddWindow(win);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinWindowDloc
**************************************************************************************************/
GWIN_API void gwinWindowDloc(GwinWindow * const win)
{
   genter;

   greturnVoidIf(
      !gwinIsStarted() ||
      !win);

   gwinRemoveWindowAt(win->windowIndex);

   gwinWindowDlocContent(win);

   gmemDloc(win);

   greturn;
}

/**************************************************************************************************
func: gwinWindowDlocContent
**************************************************************************************************/
GWIN_API void gwinWindowDlocContent(GwinWindow * const win)
{
   Gindex    index;
   GwinItem *item;

   genter;

   greturnVoidIf(
      !gwinIsStarted() ||
      !win);

   if (win->isVisible)
   {
      gwinWindowSetIsVisible(win, gbFALSE);
   }

   gsDloc(win->title);

   // Clean up the item array.
   // For all items...
   forCountDown(index, gwinItemArrayGetCount(win->itemArray))
   {
      // Get the item
      item = gwinItemArrayGetAt(win->itemArray, index);

      // Dloc itself.
      item->notifyDlocItem(item);
   }
   gwinItemArrayDloc(win->itemArray);

   // Clean up the item hole index array.
   gv4ArrayDloc(win->itemHoleIndexArray);

   gmemClearType(win, GwinWindow);

   greturn;
}

/**************************************************************************************************
func: gwinWindowGetData
**************************************************************************************************/
GWIN_API Gp * gwinWindowGetData(GwinWindow const * const gwinWindow)
{
   genter;

   greturnNullIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->data;
}

/**************************************************************************************************
func: gwinWindowGetH
**************************************************************************************************/
GWIN_API Gi4 gwinWindowGetH(GwinWindow const * const gwinWindow)
{
   genter;

   greturn0If(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->h;
}

/**************************************************************************************************
func: gwinWindowGetItemAt

Return value can be NULL if the item at a particular index was 'removed' with function
gwinWindowRemoveItemAt().
**************************************************************************************************/
GWIN_API GwinItem *gwinWindowGetItemAt(GwinWindow const * const win, Gindex const index)
{
   GwinItem *item;

   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win             ||
      !gindexIsGood(index, gwinItemArrayGetCount(win->itemArray)));

   item = gwinItemArrayGetAt(win->itemArray, index);

   greturn item;
}

/**************************************************************************************************
func: gwinWindowGetItemCount
**************************************************************************************************/
GWIN_API Gcount gwinWindowGetItemCount(GwinWindow const * const win)
{
   Gcount count;

   genter;

   greturn0If(
      !gwinIsStarted() ||
      !win);

   count = gwinItemArrayGetCount(win->itemArray);

   return count;
}

/**************************************************************************************************
func: gwinWindowGetParentWindow
**************************************************************************************************/
GWIN_API GwinWindow * gwinWindowGetParentWindow(GwinWindow const * const gwinWindow)
{
   genter;

   greturnNullIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->parentWindow;
}

/**************************************************************************************************
func: gwinWindowGetTitle
**************************************************************************************************/
GWIN_API Gs * gwinWindowGetTitle(GwinWindow const * const gwinWindow)
{
   genter;

   greturnNullIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->title;
}

/**************************************************************************************************
func: gwinWindowGetW
**************************************************************************************************/
GWIN_API Gi4 gwinWindowGetW(GwinWindow const * const gwinWindow)
{
   genter;

   greturn0If(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->w;
}

/**************************************************************************************************
func: gwinWindowGetX
**************************************************************************************************/
GWIN_API Gi4 gwinWindowGetX(GwinWindow const * const gwinWindow)
{
   genter;

   greturn0If(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->x;
}

/**************************************************************************************************
func: gwinWindowGetY
**************************************************************************************************/
GWIN_API Gi4 gwinWindowGetY(GwinWindow const * const gwinWindow)
{
   genter;

   greturn0If(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->y;
}

/**************************************************************************************************
func: gwinWindowIsActive
**************************************************************************************************/
GWIN_API Gb gwinWindowIsActive(GwinWindow const * const gwinWindow)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->isActive;
}

/**************************************************************************************************
func: gwinWindowIsDirty
**************************************************************************************************/
GWIN_API Gb gwinWindowIsDirty(GwinWindow const * const gwinWindow)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->isDirty;
}

/**************************************************************************************************
func: gwinWindowIsMaximized
**************************************************************************************************/
GWIN_API Gb gwinWindowIsMaximized(GwinWindow const * const gwinWindow)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->isMaximized;
}

/**************************************************************************************************
func: gwinWindowIsMinimized
**************************************************************************************************/
GWIN_API Gb gwinWindowIsMinimized(GwinWindow const * const gwinWindow)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->isMinimized;
}

/**************************************************************************************************
func: gwinWindowIsResizable
**************************************************************************************************/
GWIN_API Gb gwinWindowIsResizable(GwinWindow const * const gwinWindow)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->isResizable;
}

/**************************************************************************************************
func: gwinWindowIsVisible
**************************************************************************************************/
GWIN_API Gb gwinWindowIsVisible(GwinWindow const * const gwinWindow)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinWindow);

   greturn gwinWindow->isVisible;
}

/**************************************************************************************************
func: gwinWindowRemoveItemAt
**************************************************************************************************/
GWIN_API Gb gwinWindowRemoveItemAt(GwinWindow * const win, Gindex const index)
{
   Gv4 vindex;

   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win             ||
      !gindexIsGood(index, gwinItemArrayGetCount(win->itemArray)));

   // NULL out the item at the index.  This does not destroy the item.
   gwinItemArrayUpdateAt(win->itemArray, index, NULL);

   // Record in the hole index array that this is a hole that can be reused.
   vindex.i = index;
   gv4ArrayAddEnd(win->itemHoleIndexArray, &vindex);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinWindowSetCurrent
**************************************************************************************************/
GWIN_API Gb gwinWindowSetCurrent(GwinWindow * const win)
{
   GLenum error;

   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win);

   SDL_GL_MakeCurrent((SDL_Window *) win->windowSdl, (SDL_GLContext) win->contextSdl);

   // According to a post in Stack Overflow, This may need to be called after every context switch.
   // Some GLEWs may not need it but to be safe, call if after every SDL_GL_MakeCurrent();
   glewExperimental = GL_TRUE;
   error            = glewInit();
   greturnFalseIf(error != GLEW_OK);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinWindowSetIsResizable
**************************************************************************************************/
GWIN_API Gb gwinWindowSetIsResizable(GwinWindow * const win, Gb const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win);

   win->isResizable = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinWindowSetIsVisible
**************************************************************************************************/
GWIN_API Gb gwinWindowSetIsVisible(GwinWindow * const win, Gb const value)
{
   genter;

   greturnTrueIf(win->isVisible == value);

   if (value)
   {

      Gc1 *titleU1;

      titleU1 = gsClocU1(win->title);

      win->windowSdl = (GwinWindowSdl *) SDL_CreateWindow(
         (char const *) titleU1,
         win->w/2,
         win->h/2,
         SDL_WINDOW_OPENGL                |
            //SDL_WINDOW_BORDERLESS         |
            SDL_WINDOW_HIGH_PIXEL_DENSITY |
            //SDL_WINDOW_HIDDEN             |
            (SDL_WINDOW_RESIZABLE * win->isResizable));

      gmemDloc(titleU1);

      greturnFalseIf(!win->windowSdl);

      greturnFalseIf(!SDL_SetWindowPosition((SDL_Window *) win->windowSdl, win->x + 64, win->y + 64));

      if (win->isMaximized)
      {
         greturnFalseIf(!SDL_MaximizeWindow((SDL_Window *) win->windowSdl));
      }

      // Set preferred OpenGL requirements.
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,  3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,  3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,   SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(SDL_GL_RED_SIZE,               8);
      SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,             8);
      SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,              8);
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,           1);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,             32);
      SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,           1);

      win->contextSdl = (GwinWindowContextSdl *) SDL_GL_CreateContext((SDL_Window *) win->windowSdl);

      greturnFalseIf(SDL_GL_SetSwapInterval(1) < 0);

      gwinWindowSetCurrent(win);

      // Create the shaders.
      gwinShaderStart();
   }
   else
   {
      SDL_GL_DestroyContext((SDL_GLContext) win->contextSdl);
      SDL_DestroyWindow(    (SDL_Window *)  win->windowSdl);

      win->contextSdl = NULL;
      win->windowSdl  = NULL;
   }

   win->isVisible = value;

   win->notifyRender(win);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinWindowSetPosition
**************************************************************************************************/
GWIN_API Gb gwinWindowSetPosition(GwinWindow * const win, Gi4 const x, Gi4 const y)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win);

   win->x = x;
   win->y = y;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinWindowSetSize
**************************************************************************************************/
GWIN_API Gb gwinWindowSetSize(GwinWindow * const win, Gi4 const w, Gi4 const h)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win);

   win->w = w;
   win->h = h;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinWindowSetTitle
**************************************************************************************************/
GWIN_API Gb gwinWindowSetTitle(GwinWindow * const win, Gs const * const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !win);

   win->title = gsClocFrom(value);

   greturn gbTRUE;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _DefaultNotifyRender
**************************************************************************************************/
static void _DefaultNotifyRender(GwinWindow * const win)
{
   int       index;
   GwinItem *item;
   GLfloat   quad[] = {
      -0.5f, -0.5f, 0.0f,  // bl
       0.5f, -0.5f, 0.0f,  // br
       0.5f,  0.5f, 0.0f,  // tr
      -0.5f,  0.5f, 0.0f   // tl
   };
   GLuint    vbo;
   GLuint    vao;

   genter;

   greturnVoidIf(
      !win ||
      !win->isVisible);

   // Reset Matricies.
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Clearing the window to a solid light gray color.
   glClearColor(0.95f, 0.95f, 0.95f, 0.95f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   // Create the vertex buffer object for the quad.
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

   // Create the vertex attribute object for the quad.  Describing the buffer data.
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
   glEnableVertexArrayAttrib(vao, 0);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

   // Use the item shader program.
   glUseProgram((GLuint) gwinShaderGetItemProgram());
   glBindVertexArray(vao);

   glDrawArrays(GL_LINE_STRIP, 0, 4);

   // For all items in the window...
   //forCount(index, gwinItemArrayGetCount(win->itemArray))
   //{
   //   item = (GwinItem *) gwinItemArrayGetAt(win->itemArray, index);
   //
   //   item->notifyRender(win, item);
   //}

   // Swap the buffer
   SDL_GL_SwapWindow((SDL_Window *) win->windowSdl);

   greturn;
}