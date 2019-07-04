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
 
#pragma once

#include "../Macros.h"
#include "../Types.h"
#include "../RenderPipelineDescriptor.h"
#include "base/CCRef.h"
#include "base/CCEventListenerCustom.h"
#include "platform/CCGL.h"
#include "../Program.h"

#include <string>
#include <vector>
#include <unordered_map>

CC_BACKEND_BEGIN

class ShaderModuleGL;

struct AttributeInfo
{
    unsigned int location = 0;
    unsigned int size = 0;
    GLenum type = GL_BYTE;
    GLsizei stride = 0;
    unsigned int offset = 0;
    GLboolean needToBeNormallized = GL_FALSE;
    std::string name;
};

class ProgramGL : public Program
{
public:
    typedef std::vector<AttributeInfo> VertexAttributeArray;
    
    ProgramGL(const std::string& vertexShader, const std::string& fragmentShader);
    ~ProgramGL();
    
    inline const std::vector<VertexAttributeArray>& getAttributeInfos() const { return _attributeInfos; }
    inline GLuint getHandler() const { return _program; }
    void computeAttributeInfos(const RenderPipelineDescriptor& descriptor);

    virtual const std::unordered_map<std::string, UniformInfo>& getVertexUniformInfos() const override;
    virtual const std::unordered_map<std::string, UniformInfo>& getFragmentUniformInfos() const override;

    virtual UniformLocation getUniformLocation(const std::string& uniform) const override;

    virtual int getMaxVertexLocation() const override;
    virtual int getMaxFragmentLocation() const override;

    virtual const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const override;

private:
    void compileProgram();
    bool getAttributeLocation(const std::string& attributeName, unsigned int& location) const;
    void computeUniformInfos();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    virtual void reloadProgram();
    virtual int getMappedLocation(int location) const override;
    virtual const std::unordered_map<std::string, UniformLocation> getAllUniformsLocation() const override { return _originalUniformLocations; }
#endif
    
    GLuint _program = 0;
    ShaderModuleGL* _vertexShaderModule = nullptr;
    ShaderModuleGL* _fragmentShaderModule = nullptr;
    
    std::vector<VertexAttributeArray> _attributeInfos;
    std::unordered_map<std::string, UniformInfo> _uniformInfos;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    std::unordered_map<std::string, UniformLocation> _originalUniformLocations;
    std::unordered_map<int, int> _uniformLocationMap;
    EventListenerCustom* _backToForegroundListener = nullptr;
#endif
    
    int _maxLocation = -1;
};

CC_BACKEND_END
