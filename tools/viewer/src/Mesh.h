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

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include "config.h"

//#define A3D_GL_USE_VAO

#ifdef __APPLE__
#define glGenVertexArrays     glGenVertexArraysAPPLE
#define glDeleteVertexArrays  glDeleteVertexArraysAPPLE
#define glBindVertexArray     glBindVertexArrayAPPLE
#endif

class ProgramSimple;

class Mesh
{
    friend class MeshLoader;
public:
		//TODO: Mesh(GLint position, GLint normal, GLint texcoord); or struct Attributes { .. }
    Mesh(ProgramSimple* p);
    ~Mesh();

    GLvoid bind();
    GLvoid unbind();    

    GLvoid draw();
    GLvoid draw(GLuint index);

    const char* getGroupName(int idx) { return groupNames[idx].c_str(); }
    int getNGroups() { return nGroups; }

private:
    void bindBuffers();
    void disableBuffers();

    ProgramSimple* prog;
#if A3D_USE_GL_VAO == 1
    GLuint vertexArray;
#endif
    GLuint* buffers;
    GLsizei* attrSizes;
    GLsizei* attrTypeSizes;
    GLenum* attrTypes;
    GLsizei nVertices, nAttributes, nGroups, nTotalTriangles;
    GLsizei* nTriangles;
    GLsizei indexSize;
    GLenum indexType;
    std::vector<std::string> groupNames;
    std::vector<std::string> attrNames;
    //int positionIndex, normalIndex, texcoordIndex;

};

#endif // MESH_H
