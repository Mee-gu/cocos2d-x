/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#include "DepthStencilStateGL.h"
#include "platform/CCGL.h"

#include "base/ccMacros.h"
#include "renderer/backend/opengl/UtilsGL.h"
#include "GLStateCached.h"

CC_BACKEND_BEGIN

void DepthStencilStateGL::reset()
{
    GL::disable(GL_DEPTH_TEST);
    GL::disable(GL_STENCIL_TEST);
}

DepthStencilStateGL::DepthStencilStateGL(const DepthStencilDescriptor& descriptor)
: DepthStencilState(descriptor)
{}

void DepthStencilStateGL::apply(unsigned int stencilReferenceValueFront, unsigned int stencilReferenceValueBack) const
{
    // depth test
    
    if (_depthStencilInfo.depthTestEnabled)
    {
        GL::enable(GL_DEPTH_TEST);
    }
    else
    {
        GL::disable(GL_DEPTH_TEST);
    }
    
    if (_depthStencilInfo.depthWriteEnabled)
        GL::depthMask(GL_TRUE);
    else
        GL::depthMask(GL_FALSE);
    
    GL::depthFunc(UtilsGL::toGLComareFunction(_depthStencilInfo.depthCompareFunction));
    
    if (_depthStencilInfo.stencilTestEnabled)
        GL::enable(GL_STENCIL_TEST);
    else
        GL::disable(GL_STENCIL_TEST);

    // stencil test
    if (_depthStencilInfo.stencilTestEnabled)
    {
        if (_isBackFrontStencilEqual)
        {
            GL::stencilFunc(UtilsGL::toGLComareFunction(_depthStencilInfo.frontFaceStencil.stencilCompareFunction),
                          stencilReferenceValueFront,
                          _depthStencilInfo.frontFaceStencil.readMask);
            GL::stencilOp(UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.stencilFailureOperation),
                        UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthFailureOperation),
                        UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthStencilPassOperation));
            GL::stencilMask(_depthStencilInfo.frontFaceStencil.writeMask);
        }
        else
        {
            GL::stencilFuncSeparate(GL_BACK,
                                  UtilsGL::toGLComareFunction(_depthStencilInfo.backFaceStencil.stencilCompareFunction),
                                  stencilReferenceValueBack,
                                  _depthStencilInfo.backFaceStencil.readMask);
            GL::stencilFuncSeparate(GL_FRONT,
                                  UtilsGL::toGLComareFunction(_depthStencilInfo.frontFaceStencil.stencilCompareFunction),
                                  stencilReferenceValueFront,
                                  _depthStencilInfo.frontFaceStencil.readMask);
            
            GL::stencilOpSeparate(GL_BACK,
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.backFaceStencil.stencilFailureOperation),
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.backFaceStencil.depthFailureOperation),
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.backFaceStencil.depthStencilPassOperation));
            GL::stencilOpSeparate(GL_FRONT,
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.stencilFailureOperation),
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthFailureOperation),
                                UtilsGL::toGLStencilOperation(_depthStencilInfo.frontFaceStencil.depthStencilPassOperation));
            
            GL::stencilMaskSeparate(GL_BACK, _depthStencilInfo.backFaceStencil.writeMask);
            GL::stencilMaskSeparate(GL_FRONT, _depthStencilInfo.frontFaceStencil.writeMask);
        }
    }
    
    CHECK_GL_ERROR_DEBUG();
}

CC_BACKEND_END
