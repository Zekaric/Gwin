/**************************************************************************************************
file:       Gwin
author:     Robbert de Groot
company:    Zekaric
copyright:  2025, Zekaric

description:
Routines for monitor information.
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

#if !defined(GWIN_MONITOR_H)
#define      GWIN_MONITOR_H

/**************************************************************************************************
global:
prototype:
**************************************************************************************************/
GWIN_API Gb     gwinMonitorClocContent(GwinMonitor       * const gwinMonitor, Gid const id, Gi4 const x, Gi4 const y, Gi4 const w, Gi4 const h);

GWIN_API void   gwinMonitorDlocContent(GwinMonitor       * const gwinMonitor);

GWIN_API Gi4    gwinMonitorGetH(       GwinMonitor const * const gwinMonitor);
GWIN_API Gid    gwinMonitorGetId(      GwinMonitor const * const gwinMonitor);
GWIN_API Gi4    gwinMonitorGetW(       GwinMonitor const * const gwinMonitor);
GWIN_API Gi4    gwinMonitorGetX(       GwinMonitor const * const gwinMonitor);
GWIN_API Gi4    gwinMonitorGetY(       GwinMonitor const * const gwinMonitor);

GWIN_API Gb     gwinMonitorSetH(       GwinMonitor       * const gwinMonitor, Gi4 const value);
GWIN_API Gb     gwinMonitorSetId(      GwinMonitor       * const gwinMonitor, Gid const value);
GWIN_API Gb     gwinMonitorSetW(       GwinMonitor       * const gwinMonitor, Gi4 const value);
GWIN_API Gb     gwinMonitorSetX(       GwinMonitor       * const gwinMonitor, Gi4 const value);
GWIN_API Gb     gwinMonitorSetY(       GwinMonitor       * const gwinMonitor, Gi4 const value);

#endif
