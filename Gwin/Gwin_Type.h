/**************************************************************************************************
file:       GwinType
author:     Robbert de Groot
company:    Zekaric
copyright:  2025, Zekaric

description:
The global types for the Gwin library.
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

#if !defined(GWIN_TYPE_H)
#define      GWIN_TYPE_H

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
typedef struct GwinItem          GwinItem;
typedef struct GwinItemArray     GwinItemArray;
typedef struct GwinMonitor       GwinMonitor;
typedef struct GwinWindow        GwinWindow;
typedef struct GwinWindowArray   GwinWindowArray;
typedef struct Gp                GwinWindowContextSdl; // SDL_GLContext *
typedef struct Gp                GwinWindowSdl;        // SDL_Window *

typedef void (*GwinNotifyDlocItem)(    GwinItem * const item);
typedef void (*GwinNotifyRenderItem)(  GwinWindow * const win, GwinItem * const item);
typedef void (*GwinNotifyRenderWindow)(GwinWindow * const win);

typedef struct
{
   GTYPE_VAR;

   Gs                      *name;
   Gc1                     *nameU1;
   Gcount                   monitorCount;
   GwinMonitor             *monitorArray;
   Gid                      monitorMainId;
   Gindex                   monitorMainIndex;
   GwinWindow              *windowParent;
   GwinWindowArray         *windowArray;

   Gi4                      isDoubleBuffered;
   Gcount                   bitsR,
                            bitsG,
                            bitsB,
                            bitsDepth,
                            bitsStencil;

   Gp                      *data;
} Gwin;

struct GwinMonitor
{
   GTYPE_VAR;

   Gid                      id;
   Gi4                      x,
                            y,
                            w,
                            h;
};

#define GWIN_ITEM_VAR                        \
   GTYPE_VAR;                                \
   Gb                       isActive,        \
                            isVisible;       \
   GwinWindow              *parentWindow;    \
   Gi4                      x,               \
                            y,               \
                            w,               \
                            h;               \
   GwinNotifyRenderItem     notifyRender;    \
   GwinNotifyDlocItem       notifyDlocItem;  \
   Gindex                   itemIndex;       \
   Gp                      *data

struct GwinItem
{
   GWIN_ITEM_VAR;
};

struct GwinWindow
{
   GTYPE_VAR;

   Gb                       isActive,
                            isDirty,
                            isMaximized,
                            isMinimized,
                            isResizable,
                            isVisible;
   Gs                      *title;
   Gi4                      x,
                            y,
                            w,
                            h;
   GwinWindow              *parentWindow;
   GwinItemArray           *itemArray;
   Gv4Array                *itemHoleIndexArray;

   Gindex                   windowIndex;
   GwinNotifyRenderWindow   notifyRender;

   // SDL specific
   GwinWindowSdl           *windowSdl;
   GwinWindowContextSdl    *contextSdl;

   Gp                      *data;
};

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
GwinWindow containers.
**************************************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////////////////////////
struct GwinWindowArray
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   GwinWindow             **p;
};

#define gwinWindowArrayAdd(        ARRAY,        VALUE)                                               g_ArrayAdd(        (G_Array *) ARRAY,        (Gp *) VALUE)
#define gwinWindowArrayAddAt(      ARRAY, INDEX, VALUE)                                               g_ArrayAddAt(      (G_Array *) ARRAY, INDEX, (Gp *) VALUE)
#define gwinWindowArrayAddBegin(   ARRAY,        VALUE)                                               g_ArrayAddBegin(   (G_Array *) ARRAY,        (Gp *) VALUE)
#define gwinWindowArrayAddEnd(     ARRAY,        VALUE)                                               g_ArrayAddEnd(     (G_Array *) ARRAY,        (Gp *) VALUE)
#define gwinWindowArrayClear(      ARRAY, COUNT, INDEX)                                               g_ArrayClear(      (G_Array *) ARRAY, COUNT, INDEX)
#define gwinWindowArrayCopy(       ARRAY, COUNT, INDEXSRC, INDEXDST)                                  g_ArrayCopy(       (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST)
#define gwinWindowArrayCopyFrom(   ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                     g_ArrayCopyFrom(   (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC)
#define gwinWindowArrayCloc(       )                                              (GwinWindowArray *) g_ArrayCloc(                          "GwinWindowArray", GwinWindow *, gbTRUE, NULL, gbTRUE, gbFALSE)
#define gwinWindowArrayClocContent(ARRAY)                                                             g_ArrayClocContent((G_Array *) ARRAY, "GwinWindowArray", GwinWindow *, gbTRUE, NULL, gbTRUE, gbFALSE)
#define gwinWindowArrayDloc(       ARRAY)                                                             g_ArrayDloc(       (G_Array *) ARRAY)
#define gwinWindowArrayDlocContent(ARRAY)                                                             g_ArrayDlocContent((G_Array *) ARRAY)
#define gwinWindowArrayErase(      ARRAY, VALUE)                                                      g_ArrayErase(      (G_Array *) ARRAY, (Gp *) VALUE)
#define gwinWindowArrayEraseAt(    ARRAY, COUNT, INDEX)                                               g_ArrayEraseAt(    (G_Array *) ARRAY, COUNT, INDEX)
#define gwinWindowArrayEraseBegin( ARRAY)                                                             g_ArrayEraseBegin( (G_Array *) ARRAY)
#define gwinWindowArrayEraseEnd(   ARRAY)                                                             g_ArrayEraseEnd(   (G_Array *) ARRAY)
#define gwinWindowArrayFind(       ARRAY, VALUE)                                                      g_ArrayFind(       (G_Array *) ARRAY, (Gp *) VALUE)
#define gwinWindowArrayFlush(      ARRAY)                                                             g_ArrayFlush(      (G_Array *) ARRAY)
#define gwinWindowArrayForEach(    ARRAY, FUNC)                                                       g_ArrayForEach(    (G_Array *) ARRAY, FUNC)
#define gwinWindowArrayGet(        ARRAY)                                        ((GwinWindow **)     g_ArrayGet(        (G_Array *) ARRAY))
#define gwinWindowArrayGetAt(      ARRAY, INDEX)                                 ((GwinWindow *)      g_ArrayGetAt(      (G_Array *) ARRAY, INDEX))
#define gwinWindowArrayGetBegin(   ARRAY)                                        ((GwinWindow *)      g_ArrayGetBegin(   (G_Array *) ARRAY))
#define gwinWindowArrayGetCount(   ARRAY)                                                             g_ArrayGetCount(   (G_Array *) ARRAY)
#define gwinWindowArrayGetEnd(     ARRAY)                                        ((GwinWindow *)      g_ArrayGetEnd(     (G_Array *) ARRAY))
#define gwinWindowArrayGetSize(    ARRAY)                                                             g_ArrayGetSize(    (G_Array *) ARRAY)
#define gwinWindowArraySetCount(   ARRAY, COUNT)                                                      g_ArraySetCount(   (G_Array *) ARRAY, COUNT)
#define gwinWindowArraySort(       ARRAY)                                                             g_ArraySort(       (G_Array *) ARRAY)
#define gwinWindowArraySwap(       ARRAY, INDEXA, INDEXB)                                             g_ArraySwap(       (G_Array *) ARRAY, INDEXA, INDEXB)
#define gwinWindowArrayUpdateAt(   ARRAY, INDEX, VALUE)                                               g_ArrayUpdateAt(   (G_Array *) ARRAY, INDEX, (Gp *) VALUE)

/**************************************************************************************************
GwinItem containers.
**************************************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////////////////////////
struct GwinItemArray
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   GwinItem               **p;
};

#define gwinItemArrayAdd(          ARRAY,        VALUE)                                               g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE)
#define gwinItemArrayAddAt(        ARRAY, INDEX, VALUE)                                               g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE)
#define gwinItemArrayAddBegin(     ARRAY,        VALUE)                                               g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE)
#define gwinItemArrayAddEnd(       ARRAY,        VALUE)                                               g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE)
#define gwinItemArrayClear(        ARRAY, COUNT, INDEX)                                               g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX)
#define gwinItemArrayCopy(         ARRAY, COUNT, INDEXSRC, INDEXDST)                                  g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST)
#define gwinItemArrayCopyFrom(     ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                     g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC)
#define gwinItemArrayCloc(         )                                              (GwinItemArray *)   g_ArrayCloc(                                  "GwinItemArray", GwinItem *, gbTRUE, NULL, gbTRUE, gbFALSE)
#define gwinItemArrayClocContent(  ARRAY)                                                             g_ArrayClocContent(        (G_Array *) ARRAY, "GwinItemArray", GwinItem *, gbTRUE, NULL, gbTRUE, gbFALSE)
#define gwinItemArrayDloc(         ARRAY)                                                             g_ArrayDloc(               (G_Array *) ARRAY)
#define gwinItemArrayDlocContent(  ARRAY)                                                             g_ArrayDlocContent(        (G_Array *) ARRAY)
#define gwinItemArrayErase(        ARRAY, VALUE)                                                      g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE)
#define gwinItemArrayEraseAt(      ARRAY, COUNT, INDEX)                                               g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX)
#define gwinItemArrayEraseBegin(   ARRAY)                                                             g_ArrayEraseBegin(         (G_Array *) ARRAY)
#define gwinItemArrayEraseEnd(     ARRAY)                                                             g_ArrayEraseEnd(           (G_Array *) ARRAY)
#define gwinItemArrayFind(         ARRAY, VALUE)                                                      g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE)
#define gwinItemArrayFlush(        ARRAY)                                                             g_ArrayFlush(              (G_Array *) ARRAY)
#define gwinItemArrayForEach(      ARRAY, FUNC)                                                       g_ArrayForEach(            (G_Array *) ARRAY, FUNC)
#define gwinItemArrayGet(          ARRAY)                                        ((GwinItem **)       g_ArrayGet(                (G_Array *) ARRAY))
#define gwinItemArrayGetAt(        ARRAY, INDEX)                                 ((GwinItem *)        g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gwinItemArrayGetBegin(     ARRAY)                                        ((GwinItem *)        g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gwinItemArrayGetCount(     ARRAY)                                                             g_ArrayGetCount(           (G_Array *) ARRAY)
#define gwinItemArrayGetEnd(       ARRAY)                                        ((GwinItem *)        g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gwinItemArrayGetSize(      ARRAY)                                                             g_ArrayGetSize(            (G_Array *) ARRAY)
#define gwinItemArraySetCount(     ARRAY, COUNT)                                                      g_ArraySetCount(           (G_Array *) ARRAY, COUNT)
#define gwinItemArraySort(         ARRAY)                                                             g_ArraySort(               (G_Array *) ARRAY)
#define gwinItemArraySwap(         ARRAY, INDEXA, INDEXB)                                             g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB)
#define gwinItemArrayUpdateAt(     ARRAY, INDEX, VALUE)                                               g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE)

#endif
