/*
 * Copyright (c) 2011 Peter Vasil, Micheal Nischt
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "ProgramSimple.h"
#include "ShaderUtils.h"

#include <algorithm>

//TODO: lighting uniform matrix for shader

static const GLchar* szSimpleShaderVert = "uniform mat4 projection;"
                                        "uniform mat4 modelView;"
                                        "attribute vec4 vertex;"
                                        "attribute vec3 normal;"
                                        "attribute vec2 texCoord;"
                                        "varying vec3 fragmentNormal;"
                                        "varying vec2 fragmentTexCoord;"
                                        "void main(void)"
                                        "{"
                                        "fragmentTexCoord = texCoord;"
                                        "vec4 n = modelView*vec4(normal, 0.0);"
                                        "fragmentNormal = normalize(n.xyz);"
                                        "gl_Position = projection*modelView*vertex;"
                                        "}";

static const GLchar* szSimpleShaderFrag = "uniform sampler2D firstTexture;"
                                        "varying vec3 fragmentNormal;"
                                        "varying vec2 fragmentTexCoord;"
                                        "void main(void)"
                                        "{"
                                        "float intensity = max(dot(fragmentNormal, vec3(0.0, 0.0, 1.0)), 0.0);"
                                        "gl_FragColor = texture2D(firstTexture, fragmentTexCoord)*intensity;"
                                        "}";


//#include "glm/glm.hpp"
//#include "glm/gtc/type_ptr.hpp"
//#include "glm/gtc/matrix_transform.hpp"

ProgramSimple::ProgramSimple()
{
//    GLuint vs = ShaderUtils::createVertexShader("glsl/Simple.vert");
//    GLuint fs = ShaderUtils::createFragmentShader("glsl/Simple.frag");

//    program = ShaderUtils::createProgram(vs, fs);
    program = ShaderUtils::createProgramFromSrcPair(szSimpleShaderVert, szSimpleShaderFrag);

    projectionLoc = glGetUniformLocation(program, "projection");
    modelViewLoc = glGetUniformLocation(program, "modelView");
    textureLoc = glGetUniformLocation(program, "firstTexture");
//    lightingLoc = glGetUniformLocation(program, "lighting");

    vertexLoc = glGetAttribLocation(program, "vertex");
    normalLoc = glGetAttribLocation(program, "normal");
    texCoordLoc = glGetAttribLocation(program, "texCoord");

}

ProgramSimple::~ProgramSimple()
{
    if(glIsProgram(program))
    {
        glDeleteProgram(program);
        program = 0;
    }
}

GLuint ProgramSimple::programName()
{
    return program;
}
GLint ProgramSimple::position()
{
	return vertexLoc;
}
GLint ProgramSimple::normal()
{
	return normalLoc;
}
GLint ProgramSimple::texCoord()
{
	return texCoordLoc;
}

void ProgramSimple::projection(float *matrix)
{
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, matrix);
}

void ProgramSimple::modelView(float *matrix)
{
    glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, matrix);
//    glm::mat4 m = glm::mat4(1.0f);
//    std::copy(matrix, matrix+16, glm::value_ptr(m));
//    glm::mat4 invT = glm::transpose(glm::inverse(m));
//    glUniformMatrix4fv(lightingLoc, 1, GL_FALSE, glm::value_ptr(invT));

}



