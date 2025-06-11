/**************************************************************************************************
file:       Gwin
author:     Robbert de Groot
company:    Zekaric
copyright:  2025, Zekaric

description:
Libarary functions.
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
static Gb   _isStarted = gbFALSE;
static Gwin _app;

/**************************************************************************************************
prototype:
**************************************************************************************************/
static Gb    _ClocContent( Gwin * const app, Gs const * const appName);
static void  _DlocContent( Gwin * const app);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gwinAddWindow
**************************************************************************************************/
GWIN_API Gindex gwinAddWindow(GwinWindow * const win)
{
   Gb     result;
   Gindex index;

   genter;

   greturnIf(
         !_isStarted ||
         !win,
      GindexERROR);

   // Find a free spot if any
   index = gwinWindowArrayFind(_app.windowArray, NULL);
   if (index != GindexERROR)
   {
      result = gwinWindowArrayUpdateAt(_app.windowArray, index, win);
      greturnIf(!result, GindexERROR);

      greturn index;
   }

   // Add to the list.
   result = gwinWindowArrayAddEnd(_app.windowArray, win);
   greturnIf(!result, GindexERROR);

   index = gwinWindowArrayGetCount(_app.windowArray) - 1;

   greturn index;
}

/**************************************************************************************************
func: gwinGetWindowAt
**************************************************************************************************/
GWIN_API GwinWindow *gwinGetWindowAt(Gindex const index)
{
   GwinWindow *win;

   genter;

   greturnNullIf(
      !_isStarted ||
      !gindexIsGood(index, gwinWindowArrayGetCount(_app.windowArray)));

   win = gwinWindowArrayGetAt(_app.windowArray, index);

   greturn win;
}

/**************************************************************************************************
func: gwinGetWindowCount
**************************************************************************************************/
GWIN_API Gcount gwinGetWindowCount(void)
{
   Gcount count;

   genter;

   greturn0If(!_isStarted);

   count = gwinWindowArrayGetCount(_app.windowArray);

   greturn count;
}

/**************************************************************************************************
func: gwinGetWindowParent
**************************************************************************************************/
GWIN_API GwinWindow *gwinGetWindowParent(void)
{
   genter;

   greturnNullIf(!_isStarted);

   greturn _app.windowParent;
}

/**************************************************************************************************
func: gwinIsStarted
**************************************************************************************************/
GWIN_API Gb gwinIsStarted(void)
{
   return _isStarted;
}

/**************************************************************************************************
func: gwinLoop
**************************************************************************************************/
GWIN_API Gi4 gwinLoop(void)
{
   SDL_Event event;
   Gi4       result;
   Gb        isTerminating;

   genter;

   result = GappSUCCESS;

   isTerminating = gbFALSE;
   while (!isTerminating)
   {
      // Handle Events.
      while (SDL_PollEvent(&event) != 0)
      {
         debugPrintFormatA("%x\n", event.type);

         switch (event.type)
         {
         //case SDL_EVENT_WINDOW_CLOSE_REQUESTED,   /**< The window manager requests that the window be closed */
         //case SDL_EVENT_WINDOW_DESTROYED,         /**< The window with the associated ID is being or has been destroyed. If this message is being handled
         case SDL_EVENT_QUIT:
            isTerminating = gbTRUE;
            break;

         case SDL_EVENT_WINDOW_EXPOSED:
            // redraw window.
            _app.windowParent->notifyRender(_app.windowParent);
            break;

         case SDL_EVENT_WINDOW_RESIZED:
         case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
         case SDL_EVENT_WINDOW_METAL_VIEW_RESIZED:
         case SDL_EVENT_WINDOW_MAXIMIZED:
         case SDL_EVENT_WINDOW_RESTORED:
            // reconfigure window.

            // redraw window.
            _app.windowParent->notifyRender(_app.windowParent);
            break;

         case SDL_EVENT_WINDOW_MINIMIZED:
         case SDL_EVENT_WINDOW_MOVED:
            // Probably do not have to do anything.
            break;

         default:
            result = 1;
            break;

         //case SDL_EVENT_WINDOW_MOUSE_ENTER,       /**< Window has gained mouse focus */
         //case SDL_EVENT_WINDOW_MOUSE_LEAVE,       /**< Window has lost mouse focus */
         //case SDL_EVENT_WINDOW_FOCUS_GAINED,      /**< Window has gained keyboard focus */
         //case SDL_EVENT_WINDOW_FOCUS_LOST,        /**< Window has lost keyboard focus */
         //case SDL_EVENT_WINDOW_HIT_TEST,          /**< Window had a hit test that wasn't SDL_HITTEST_NORMAL */
         //case SDL_EVENT_WINDOW_ICCPROF_CHANGED,   /**< The ICC profile of the window's display has changed */
         //case SDL_EVENT_WINDOW_DISPLAY_CHANGED,   /**< Window has been moved to display data1 */
         //case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED, /**< Window display scale has been changed */
         //case SDL_EVENT_WINDOW_SAFE_AREA_CHANGED, /**< The window safe area has been changed */
         //case SDL_EVENT_WINDOW_OCCLUDED,          /**< The window has been occluded */
         //case SDL_EVENT_WINDOW_ENTER_FULLSCREEN,  /**< The window has entered fullscreen mode */
         //case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN,  /**< The window has left fullscreen mode */

         //SDL_EVENT_KEY_DOWN        = 0x300, /**< Key pressed */
         //SDL_EVENT_KEY_UP,                  /**< Key released */
         //SDL_EVENT_TEXT_EDITING,            /**< Keyboard text editing (composition) */
         //SDL_EVENT_TEXT_INPUT,              /**< Keyboard text input */
         //SDL_EVENT_KEYMAP_CHANGED,          /**< Keymap changed due to a system event such as an
         //                                    input language or keyboard layout change. */
         //SDL_EVENT_KEYBOARD_ADDED,          /**< A new keyboard has been inserted into the system */
         //SDL_EVENT_KEYBOARD_REMOVED,        /**< A keyboard has been removed */
         //SDL_EVENT_TEXT_EDITING_CANDIDATES, /**< Keyboard text editing candidates */
         //
         ///* Mouse events */
         //SDL_EVENT_MOUSE_MOTION    = 0x400, /**< Mouse moved */
         //SDL_EVENT_MOUSE_BUTTON_DOWN,       /**< Mouse button pressed */
         //SDL_EVENT_MOUSE_BUTTON_UP,         /**< Mouse button released */
         //SDL_EVENT_MOUSE_WHEEL,             /**< Mouse wheel motion */
         //SDL_EVENT_MOUSE_ADDED,             /**< A new mouse has been inserted into the system */
         //SDL_EVENT_MOUSE_REMOVED,           /**< A mouse has been removed */
         //
         ///* Joystick events */
         //SDL_EVENT_JOYSTICK_AXIS_MOTION  = 0x600, /**< Joystick axis motion */
         //SDL_EVENT_JOYSTICK_BALL_MOTION,          /**< Joystick trackball motion */
         //SDL_EVENT_JOYSTICK_HAT_MOTION,           /**< Joystick hat position change */
         //SDL_EVENT_JOYSTICK_BUTTON_DOWN,          /**< Joystick button pressed */
         //SDL_EVENT_JOYSTICK_BUTTON_UP,            /**< Joystick button released */
         //SDL_EVENT_JOYSTICK_ADDED,                /**< A new joystick has been inserted into the system */
         //SDL_EVENT_JOYSTICK_REMOVED,              /**< An opened joystick has been removed */
         //SDL_EVENT_JOYSTICK_BATTERY_UPDATED,      /**< Joystick battery level change */
         //SDL_EVENT_JOYSTICK_UPDATE_COMPLETE,      /**< Joystick update is complete */
         //
         ///* Gamepad events */
         //SDL_EVENT_GAMEPAD_AXIS_MOTION  = 0x650, /**< Gamepad axis motion */
         //SDL_EVENT_GAMEPAD_BUTTON_DOWN,          /**< Gamepad button pressed */
         //SDL_EVENT_GAMEPAD_BUTTON_UP,            /**< Gamepad button released */
         //SDL_EVENT_GAMEPAD_ADDED,                /**< A new gamepad has been inserted into the system */
         //SDL_EVENT_GAMEPAD_REMOVED,              /**< A gamepad has been removed */
         //SDL_EVENT_GAMEPAD_REMAPPED,             /**< The gamepad mapping was updated */
         //SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN,        /**< Gamepad touchpad was touched */
         //SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION,      /**< Gamepad touchpad finger was moved */
         //SDL_EVENT_GAMEPAD_TOUCHPAD_UP,          /**< Gamepad touchpad finger was lifted */
         //SDL_EVENT_GAMEPAD_SENSOR_UPDATE,        /**< Gamepad sensor was updated */
         //SDL_EVENT_GAMEPAD_UPDATE_COMPLETE,      /**< Gamepad update is complete */
         //SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED,  /**< Gamepad Steam handle has changed */
         //
         ///* Touch events */
         //SDL_EVENT_FINGER_DOWN      = 0x700,
         //SDL_EVENT_FINGER_UP,
         //SDL_EVENT_FINGER_MOTION,
         //SDL_EVENT_FINGER_CANCELED,

         //SDL_EVENT_DROP_FILE        = 0x1000, /**< The system requests a file open */
         //SDL_EVENT_DROP_TEXT,                 /**< text/plain drag-and-drop event */

         //SDL_EVENT_PEN_PROXIMITY_IN = 0x1300,  /**< Pressure-sensitive pen has become available */
         //SDL_EVENT_PEN_PROXIMITY_OUT,          /**< Pressure-sensitive pen has become unavailable */
         //SDL_EVENT_PEN_DOWN,                   /**< Pressure-sensitive pen touched drawing surface */
         //SDL_EVENT_PEN_UP,                     /**< Pressure-sensitive pen stopped touching drawing surface */
         //SDL_EVENT_PEN_BUTTON_DOWN,            /**< Pressure-sensitive pen button pressed */
         //SDL_EVENT_PEN_BUTTON_UP,              /**< Pressure-sensitive pen button released */
         //SDL_EVENT_PEN_MOTION,                 /**< Pressure-sensitive pen is moving on the tablet */
         //SDL_EVENT_PEN_AXIS,                   /**< Pressure-sensitive pen angle/pressure/etc changed */
         }

         // Should do something with input.
      }

      // Render the windows that have changed.
   }

   greturn result;
}

/**************************************************************************************************
func: gwinRemoveWindowAt
**************************************************************************************************/
GWIN_API Gb gwinRemoveWindowAt(Gindex const index)
{
   Gb result;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !gindexIsGood(index, gwinWindowArrayGetCount(_app.windowArray)));

   result = gwinWindowArrayUpdateAt(_app.windowArray, index, NULL);

   greturn result;
}

/**************************************************************************************************
func: gwinStart
**************************************************************************************************/
GWIN_API Gb gwinStart(wchar_t const * const name)
{
   Gs *sname;

   returnFalseIf(
      !grlStart() &&
      !_isStarted);

   _isStarted = gbTRUE;

   sname = gsClocFromU2(name);
   _isStarted = _ClocContent(&_app, sname);
   gsDloc(sname);

   return _isStarted;
}

/**************************************************************************************************
func: gwinStop
**************************************************************************************************/
GWIN_API void gwinStop(void)
{
   returnVoidIf(!_isStarted);

   _DlocContent(&_app);

   _isStarted = gbFALSE;

   grlStop();

   return;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _ClocContent
**************************************************************************************************/
static Gb _ClocContent(Gwin * const app, Gs const * const appName)
{
   Gid      *idArray;
   Gindex    index;
   SDL_Rect  rtemp;

   genter;

   gmemClearType(app, Gwin);

   GTYPE_SET(app, "GWin");

   app->name   = gsClocFrom(appName);
   app->nameU1 = gsClocU1(  appName);

   greturnFalseIf(!SDL_Init(SDL_INIT_VIDEO));

   greturnFalseIf(!SDL_SetAppMetadata((char const *) app->nameU1, "1.0", "www.zekaric.com"));

   // Get the monitors attached to the computer.
   idArray = SDL_GetDisplays(&app->monitorCount);
   greturnFalseIf(
      !app->monitorCount ||
      !idArray);

   app->monitorArray = gmemClocTypeArray(GwinMonitor, app->monitorCount);
   greturnFalseIf(!app->monitorArray);

   app->monitorMainId = SDL_GetPrimaryDisplay();
   forCount(index, app->monitorCount)
   {
      SDL_GetDisplayUsableBounds(idArray[index], &rtemp);

      gwinMonitorClocContent(
         &app->monitorArray[index],
         idArray[index],
         rtemp.x,
         rtemp.y,
         rtemp.w,
         rtemp.h);

      if (app->monitorMainId == idArray[index])
      {
         app->monitorMainIndex = index;
      }
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

   // Create the window array.
   app->windowArray = gwinWindowArrayCloc();

   // Create the main window for the program.
   app->windowParent = gwinWindowCloc();
   greturnFalseIf(!app->windowParent);

   greturnFalseIf(!gwinWindowSetTitle(       app->windowParent, app->name));
   greturnFalseIf(!gwinWindowSetIsResizable( app->windowParent, gbTRUE));
   greturnFalseIf(!gwinWindowSetPosition(
      app->windowParent,
      gwinMonitorGetX(&app->monitorArray[app->monitorMainIndex]),
      gwinMonitorGetY(&app->monitorArray[app->monitorMainIndex])));
   greturnFalseIf(!gwinWindowSetSize(
      app->windowParent,
      gwinMonitorGetW(&app->monitorArray[app->monitorMainIndex]),
      gwinMonitorGetH(&app->monitorArray[app->monitorMainIndex])));
   greturnFalseIf(!gwinWindowSetIsVisible(     app->windowParent, gbTRUE));

   // See what we actually got for the window.
   SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER,  &app->isDoubleBuffered);
   SDL_GL_GetAttribute(SDL_GL_RED_SIZE,      &app->bitsR);
   SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE,    &app->bitsG);
   SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE,     &app->bitsB);
   SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE,    &app->bitsDepth);
   SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE,  &app->bitsStencil);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _DlocContent
**************************************************************************************************/
static void _DlocContent(Gwin * const app)
{
   genter;

   // Clean up memory.
   gwinWindowSetIsVisible(app->windowParent, gbFALSE);
   gwinWindowDloc(app->windowParent);

   gsDloc(app->name);
   gmemDloc(app->nameU1);
   gmemDloc(app->monitorArray);

   gmemClearType(app, Gwin);

   greturn;
}