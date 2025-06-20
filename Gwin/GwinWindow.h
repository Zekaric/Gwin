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

#if !defined(GWIN_WINDOW_H)
#define      GWIN_WINDOW_H

/**************************************************************************************************
include:
**************************************************************************************************/

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
GWIN_API GwinWindow  *gwinWindowCloc(           void);
GWIN_API Gb           gwinWindowClocContent(    GwinWindow       * const win);

GWIN_API void         gwinWindowDloc(           GwinWindow       * const win);
GWIN_API void         gwinWindowDlocContent(    GwinWindow       * const win);

GWIN_API Gp          *gwinWindowGetData(        GwinWindow const * const gwinWindow);
GWIN_API Gi4          gwinWindowGetH(           GwinWindow const * const gwinWindow);

GWIN_API GwinWindow  *gwinWindowGetParentWindow(GwinWindow const * const gwinWindow);
GWIN_API Gs          *gwinWindowGetTitle(       GwinWindow const * const gwinWindow);
GWIN_API Gi4          gwinWindowGetW(           GwinWindow const * const gwinWindow);
GWIN_API Gi4          gwinWindowGetX(           GwinWindow const * const gwinWindow);
GWIN_API Gi4          gwinWindowGetY(           GwinWindow const * const gwinWindow);

GWIN_API Gb           gwinWindowIsActive(       GwinWindow const * const gwinWindow);
GWIN_API Gb           gwinWindowIsDirty(        GwinWindow const * const gwinWindow);
GWIN_API Gb           gwinWindowIsMaximized(    GwinWindow const * const gwinWindow);
GWIN_API Gb           gwinWindowIsMinimized(    GwinWindow const * const gwinWindow);
GWIN_API Gb           gwinWindowIsResizable(    GwinWindow const * const gwinWindow);
GWIN_API Gb           gwinWindowIsVisible(      GwinWindow const * const gwinWindow);

GWIN_API Gindex       gwinWindowItemAdd(        GwinWindow       * const win, GwinItem * const item);
GWIN_API GwinItem    *gwinWindowItemGetAt(      GwinWindow const * const win, Gindex const index);
GWIN_API Gcount       gwinWindowItemGetCount(   GwinWindow const * const win);
GWIN_API Gb           gwinWindowItemRemove(     GwinWindow       * const win, GwinItem * const item);
GWIN_API Gb           gwinWindowItemRemoveAt(   GwinWindow       * const win, Gindex const index);

GWIN_API Gb           gwinWindowSetCurrent(     GwinWindow       * const win);
GWIN_API Gb           gwinWindowSetIsResizable( GwinWindow       * const win, Gb const value);
GWIN_API Gb           gwinWindowSetIsVisible(   GwinWindow       * const win, Gb const value);
GWIN_API Gb           gwinWindowSetPosition(    GwinWindow       * const win, Gi4 const x, Gi4 const y);
GWIN_API Gb           gwinWindowSetSize(        GwinWindow       * const win, Gi4 const w, Gi4 const h);
GWIN_API Gb           gwinWindowSetTitle(       GwinWindow       * const win, Gs const * const value);

#endif
