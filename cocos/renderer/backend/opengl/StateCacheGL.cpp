#include "StateCacheGL.h"
#include "base/ccTypes.h"
CC_BACKEND_BEGIN

RenderStatus GL::_lastRenderStatus = RenderStatus::RS_NONE;

void GL::enable(GLenum cap)
{
    switch(cap)
    {
        case GL_DEPTH_TEST:
            if(!(_lastRenderStatus & RenderStatus::RS_DEPTH_TEST))
            {
                glEnable(GL_DEPTH_TEST);
                _lastRenderStatus |= RenderStatus ::RS_DEPTH_TEST;
            }
            break;
        default:
            break;
    }
}

void GL::disable(GLenum cap)
{
    switch(cap)
    {
        case GL_DEPTH_TEST:
            if((_lastRenderStatus & RenderStatus::RS_DEPTH_TEST))
            {
                glDisable(GL_DEPTH_TEST);
                _lastRenderStatus &= ~RenderStatus ::RS_DEPTH_TEST;
            }
            break;
        default:
            break;
    }
}


CC_BACKEND_END