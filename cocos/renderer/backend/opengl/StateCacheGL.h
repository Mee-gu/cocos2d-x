#pragma once

#include "platform/CCGL.h"
#include "renderer/backend/Macros.h"
#include "renderer/backend/Types.h"

CC_BACKEND_BEGIN

class GL
{
public:
    static void enable(GLenum cap);
    static void disable(GLenum cap);

private:
    static RenderStatus _lastRenderStatus;
};

CC_BACKEND_END