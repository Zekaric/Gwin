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
static void _DefaultNotifyRender(GwinWindow * const win, GwinItem * const item);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gwinItemCloc
**************************************************************************************************/
GWIN_API GwinItem *gwinItemCloc(GwinWindow * const parentWindow, Gi4 const x, Gi4 const y, Gi4 const w,
   Gi4 const h)
{
   GwinItem *gwinItem;

   genter;

   greturnNullIf(!gwinIsStarted());

   gwinItem = gmemClocType(GwinItem);
   greturnNullIf(!gwinItem);

   if (!gwinItemClocContent(gwinItem, parentWindow, x, y, w, h))
   {
      gmemDloc(gwinItem);
      greturn NULL;
   }

   greturn gwinItem;
}

/**************************************************************************************************
func: gwinItemClocContent
**************************************************************************************************/
GWIN_API Gb gwinItemClocContent(GwinItem * const gwinItem, GwinWindow * const parentWindow,
   Gi4 const x, Gi4 const y, Gi4 const w, Gi4 const h)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gmemClearType(gwinItem, GwinItem);

   GTYPE_SET(gwinItem, "GwinItem");

   gwinItem->parentWindow   = parentWindow;
   gwinItem->x              = x;
   gwinItem->y              = y;
   gwinItem->w              = w;
   gwinItem->h              = h;
   gwinItem->notifyRender   = _DefaultNotifyRender;
   gwinItem->notifyDlocItem = gwinItemDloc;

   greturnFalseIf(!gwinWindowItemAdd(parentWindow, gwinItem));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemDloc
**************************************************************************************************/
GWIN_API void gwinItemDloc(GwinItem * const gwinItem)
{
   genter;

   greturnVoidIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItemDlocContent(gwinItem);

   gmemDloc(gwinItem);

   greturn;
}

/**************************************************************************************************
func: gwinItemDlocContent
**************************************************************************************************/
GWIN_API void gwinItemDlocContent(GwinItem * const gwinItem)
{
   genter;

   greturnVoidIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinWindowItemRemoveAt(gwinItem->parentWindow, gwinItem->itemIndex);

   gmemClearType(gwinItem, GwinItem);

   greturn;
}

/**************************************************************************************************
func: gwinItemGetH
**************************************************************************************************/
GWIN_API Gi4 gwinItemGetH(GwinItem const * const gwinItem)
{
   genter;

   greturn0If(
      !gwinIsStarted() ||
      !gwinItem);

   greturn gwinItem->h;
}

/**************************************************************************************************
func: gwinItemGetParentWindow
**************************************************************************************************/
GWIN_API GwinWindow * gwinItemGetParentWindow(GwinItem const * const gwinItem)
{
   genter;

   greturnNullIf(
      !gwinIsStarted() ||
      !gwinItem);

   greturn gwinItem->parentWindow;
}

/**************************************************************************************************
func: gwinItemGetW
**************************************************************************************************/
GWIN_API Gi4 gwinItemGetW(GwinItem const * const gwinItem)
{
   genter;

   greturn0If(
      !gwinIsStarted() ||
      !gwinItem);

   greturn gwinItem->w;
}

/**************************************************************************************************
func: gwinItemGetX
**************************************************************************************************/
GWIN_API Gi4 gwinItemGetX(GwinItem const * const gwinItem)
{
   genter;

   greturn0If(
      !gwinIsStarted() ||
      !gwinItem);

   greturn gwinItem->x;
}

/**************************************************************************************************
func: gwinItemGetY
**************************************************************************************************/
GWIN_API Gi4 gwinItemGetY(GwinItem const * const gwinItem)
{
   genter;

   greturn0If(
      !gwinIsStarted() ||
      !gwinItem);

   greturn gwinItem->y;
}

/**************************************************************************************************
func: gwinItemGetData
**************************************************************************************************/
GWIN_API Gp * gwinItemGetData(GwinItem const * const gwinItem)
{
   genter;

   greturnNullIf(
      !gwinIsStarted() ||
      !gwinItem);

   greturn gwinItem->data;
}

/**************************************************************************************************
func: gwinItemIsActive
**************************************************************************************************/
GWIN_API Gb gwinItemIsActive(GwinItem const * const gwinItem)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   greturn gwinItem->isActive;
}

/**************************************************************************************************
func: gwinItemIsVisible
**************************************************************************************************/
GWIN_API Gb gwinItemIsVisible(GwinItem const * const gwinItem)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   greturn gwinItem->isVisible;
}

/**************************************************************************************************
func: gwinItemSetH
**************************************************************************************************/
GWIN_API Gb gwinItemSetH(GwinItem * const gwinItem, Gi4 const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->h = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemSetIsActive
**************************************************************************************************/
GWIN_API Gb gwinItemSetIsActive(GwinItem * const gwinItem, Gb const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->isActive = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemSetIsVisible
**************************************************************************************************/
GWIN_API Gb gwinItemSetIsVisible(GwinItem * const gwinItem, Gb const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->isVisible = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemSetNotifyRender
**************************************************************************************************/
GWIN_API Gb gwinItemSetNotifyRender(GwinItem * const gwinItem, GwinNotifyRenderItem value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->notifyRender = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemSetParentWindow
**************************************************************************************************/
GWIN_API Gb gwinItemSetParentWindow(GwinItem * const gwinItem, GwinWindow * const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->parentWindow = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemSetW
**************************************************************************************************/
GWIN_API Gb gwinItemSetW(GwinItem * const gwinItem, Gi4 const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->w = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemSetX
**************************************************************************************************/
GWIN_API Gb gwinItemSetX(GwinItem * const gwinItem, Gi4 const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->x = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemSetY
**************************************************************************************************/
GWIN_API Gb gwinItemSetY(GwinItem * const gwinItem, Gi4 const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->y = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinItemSetData
**************************************************************************************************/
GWIN_API Gb gwinItemSetData(GwinItem * const gwinItem, Gp * const value)
{
   genter;

   greturnFalseIf(
      !gwinIsStarted() ||
      !gwinItem);

   gwinItem->data = value;

   greturn gbTRUE;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _DefaultNotifyRender
**************************************************************************************************/
static void _DefaultNotifyRender(GwinWindow * const win, GwinItem * const item)
{
   genter;

   item;

   greturnVoidIf(
      !win ||
      !win->isVisible);

   // Render a simple white box with black border.
   glDrawArrays(GL_QUADS, 0, 4);

   greturn;
}