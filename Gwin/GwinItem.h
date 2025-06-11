/**************************************************************************************************
file:       GwinItem
author:     Robbert de Groot
company:    Zekaric
copyright:  2025, Zekaric

description:
Base type for an item on a window.
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

#if !defined(GWIN_ITEM_H)
#define      GWIN_ITEM_H

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

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gwinItemCloc
**************************************************************************************************/
GWIN_API GwinItem    *gwinItemCloc(                                              GwinWindow * const parentWindow, Gi4 const x, Gi4 const y, Gi4 const w, Gi4 const h);
GWIN_API Gb           gwinItemClocContent(      GwinItem       * const gwinItem, GwinWindow * const parentWindow, Gi4 const x, Gi4 const y, Gi4 const w, Gi4 const h);

GWIN_API void         gwinItemDloc(             GwinItem       * const gwinItem);
GWIN_API void         gwinItemDlocContent(      GwinItem       * const gwinItem);

GWIN_API Gi4          gwinItemGetH(             GwinItem const * const gwinItem);
GWIN_API GwinWindow  *gwinItemGetParentWindow(  GwinItem const * const gwinItem);
GWIN_API Gi4          gwinItemGetW(             GwinItem const * const gwinItem);
GWIN_API Gi4          gwinItemGetX(             GwinItem const * const gwinItem);
GWIN_API Gi4          gwinItemGetY(             GwinItem const * const gwinItem);
GWIN_API Gp          *gwinItemGetData(          GwinItem const * const gwinItem);

GWIN_API Gb           gwinItemIsActive(         GwinItem const * const gwinItem);
GWIN_API Gb           gwinItemIsVisible(        GwinItem const * const gwinItem);

GWIN_API Gb           gwinItemSetH(             GwinItem       * const gwinItem, Gi4 const value);
GWIN_API Gb           gwinItemSetIsActive(      GwinItem       * const gwinItem, Gb const value);
GWIN_API Gb           gwinItemSetIsVisible(     GwinItem       * const gwinItem, Gb const value);
GWIN_API Gb           gwinItemSetNotifyRender(  GwinItem       * const gwinItem, GwinNotifyRenderItem value);
GWIN_API Gb           gwinItemSetParentWindow(  GwinItem       * const gwinItem, GwinWindow * const value);
GWIN_API Gb           gwinItemSetW(             GwinItem       * const gwinItem, Gi4 const value);
GWIN_API Gb           gwinItemSetX(             GwinItem       * const gwinItem, Gi4 const value);
GWIN_API Gb           gwinItemSetY(             GwinItem       * const gwinItem, Gi4 const value);
GWIN_API Gb           gwinItemSetData(          GwinItem       * const gwinItem, Gp * const value);

#endif