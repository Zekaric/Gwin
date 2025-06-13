/**************************************************************************************************
file:       GwinShader
author:     Robbert de Groot
company:    Zekaric
copyright:  2025, Zekaric

description:

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
static Gb          _isStarted = gbFALSE;

static char const *_shaderItemVertProg =
   "#version 150\n"
   "\n"
   "in vec3 vp;\n"
   "\n"
   "void main()\n"
   "{\n"
   "   gl_Position = vec4(vp, 1.0);\n"
   "}\n";

static char const *_shaderItemFragProg =
   "#version 150\n"
   "\n"
   "out vec4 frag_color;\n"
   "\n"
   "void main()\n"
   "{\n"
   "   frag_color = vec4(0.5, 0.0, 0.5, 1.0);\n"
   "}\n";

static GLuint      _shaderItemVert  = 0,
                   _shaderItemFrag  = 0,
                   _shaderItemProg  = 0;

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gwinShaderGetItemProgram
**************************************************************************************************/
GWIN_API Gn4 gwinShaderGetItemProgram(void)
{
   genter;

   greturn0If(!_isStarted);

   greturn _shaderItemProg;
}

/**************************************************************************************************
func: gwinShaderStart
**************************************************************************************************/
GWIN_API Gb gwinShaderStart(void)
{
   genter;

   greturnFalseIf(!gwinIsStarted());

   if (!_isStarted)
   {
      _shaderItemVert = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource( _shaderItemVert, 1, &_shaderItemVertProg, NULL);
      glCompileShader(_shaderItemVert);

      _shaderItemFrag = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource( _shaderItemFrag, 1, &_shaderItemFragProg, NULL);
      glCompileShader(_shaderItemFrag);

      _shaderItemProg = glCreateProgram();
      glAttachShader(_shaderItemProg, _shaderItemVert);
      glAttachShader(_shaderItemProg, _shaderItemFrag);
      glLinkProgram( _shaderItemProg);
   }

   _isStarted = gbTRUE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gwinShaderStop
**************************************************************************************************/
GWIN_API void gwinShaderStop(void)
{
   genter;

   greturnVoidIf(!gwinIsStarted());

   if (_isStarted)
   {
      glDeleteShader( _shaderItemVert);
      glDeleteShader( _shaderItemFrag);
      glDeleteProgram(_shaderItemProg);
   }

   greturn;
}
