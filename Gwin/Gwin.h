/**************************************************************************************************
file:       Gwin
author:     Robbert de Groot
company:    Zekaric
copyright:  2025, Zekaric

description:
The header file for the Gwin library.
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

#if !defined(GWIN_H)
#define      GWIN_H

// GWin is a static library normally.  Just in case someone wants it to be a dll.
#if defined(GWIN_IS_A_DYNAMIC_LIBRARY)
#if defined(GWIN_EXPORTS)
#define GWIN_API __declspec(dllexport)
#else defined(GWIN_IMPORTS)
#define GWIN_API __declspec(dllimport)
#endif
#else
#if defined(CPP)
#define GWIN_API extern "C"
#else
#define GWIN_API
#endif
#endif

/**************************************************************************************************
include:
**************************************************************************************************/
#include "Gwin_Type.h"

#include "GwinMonitor.h"

#include "GwinWindow.h"

#include "GwinItem.h"

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

/**************************************************************************************************
global:
function:
**************************************************************************************************/
GWIN_API Gb           gwinAddWindow(      GwinWindow      * const win);

GWIN_API GwinWindow  *gwinGetWindowAt(    Gindex const index);
GWIN_API Gcount       gwinGetWindowCount( void);
GWIN_API GwinWindow  *gwinGetWindowParent(void);

GWIN_API Gb           gwinIsStarted(      void);

GWIN_API Gi4          gwinLoop(           void);

GWIN_API Gb           gwinRemoveWindowAt( Gindex const index);

GWIN_API Gb           gwinStart(          wchar_t const * const name);
GWIN_API void         gwinStop(           void);

#endif
