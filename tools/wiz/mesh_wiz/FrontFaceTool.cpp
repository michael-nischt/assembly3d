/*
 * Copyright (c) 2011 Peter Vasil
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

#include "MeshWizIncludes.h"
#include "FrontFaceTool.h"
#include <cmath>
#include <sstream>
#include "TransformTool.h"

#define PIf		3.1415926535897932384626433832795f

using namespace assembly3d;
using namespace assembly3d::wiz;

FrontFaceTool::FrontFaceTool()
{
}

FrontFaceTool::~FrontFaceTool()
{
}

void FrontFaceTool::flip(Mesh* mesh)
{
    int numTriangles = mesh->getNumberOfTriangles();
    for(int i = 0; i < numTriangles; ++i)
    {
        unsigned int* pTriangle = mesh->getTriangle(i);
        unsigned int idx1 = pTriangle[1];
        unsigned int idx2 = pTriangle[2];

        pTriangle[1] = idx2;
        pTriangle[2] = idx1;
    }

    int numVertices = mesh->getNumberOfVertices();
    for(int i = 0; i < numVertices; ++i)
    {
        float* pNormal = mesh->getNormal(i);
        pNormal[0] = -pNormal[0];
        pNormal[1] = -pNormal[1];
        pNormal[2] = -pNormal[2];
    }
}

bool FrontFaceTool::makeConsistent(Mesh *mesh, std::string& resultMsg)
{
    bool modelChanged = false;

    std::vector<int> verticesOutwards;
    std::vector<int> verticesInwards;

    std::stringstream strStr;

    bool normalsConsistent = isConsistent(mesh, verticesOutwards, verticesInwards);
    if(normalsConsistent == false)
    {
        strStr << verticesOutwards.size() << " outward vertices.\n";
        strStr << verticesInwards.size() << " inward vertices.\n";
        if(verticesOutwards.size() > verticesInwards.size())
        {
            strStr << "Flipping inward vertices...\n";
            for(size_t i = 0; i < verticesInwards.size(); ++i)
            {

                float* pNormal = mesh->getNormal(verticesInwards[i]);
                pNormal[0] = -pNormal[0];
                pNormal[1] = -pNormal[1];
                pNormal[2] = -pNormal[2];
            }
            modelChanged = true;
        }
        else if(verticesOutwards.size() < verticesInwards.size())
        {
            strStr << "Flipping outward vertices...\n";
            for(size_t i = 0; i < verticesOutwards.size(); ++i)
            {
                float* pNormal = mesh->getNormal(verticesOutwards[i]);
                pNormal[0] = -pNormal[0];
                pNormal[1] = -pNormal[1];
                pNormal[2] = -pNormal[2];
            }
            modelChanged = true;
        }
    }
    else
    {
        strStr << "Front-faces are consistent.";
    }

    resultMsg = strStr.str();
    return modelChanged;
}

bool FrontFaceTool::isConsistent(Mesh *mesh, std::vector<int>& verticesOutwards,
                                 std::vector<int>& verticesInwards)
{
    bool consistent = false;

    float* faceNormals = mesh->getFaceNormals();
    
    for(int i = 0; i < mesh->getNumberOfVertices(); ++i)
    {

        float* pNormal1 = mesh->getNormal(i);
        float* pNormal2 = &faceNormals[i*4];
		
        float normal[3] = {pNormal1[0],
                           pNormal1[1],
                           pNormal1[2]};

        TransformTool::normalize(normal, 3);

        float dotVec1Vec2 =  normal[0]*pNormal2[0] +
                             normal[1]*pNormal2[1] +
                             normal[2]*pNormal2[2];

        float angle = (float)acos(std::min(dotVec1Vec2, 1.0f));

        if(angle <= (PIf / 2))
        {
            verticesOutwards.push_back(i);
        }
        else
        {
            verticesInwards.push_back(i);
        }
    }

    if(verticesOutwards.empty() || verticesInwards.empty())
    {
        consistent = true;
    }

    return consistent;
}

void FrontFaceTool::changeWinding(Mesh* mesh)
{
	int numTriangles = mesh->getNumberOfTriangles();
    for(int i = 0; i < numTriangles; ++i)
    {
        unsigned int* pTriangle = mesh->getTriangle(i);
        unsigned int idx1 = pTriangle[1];
        unsigned int idx2 = pTriangle[2];
		
        pTriangle[1] = idx2;
        pTriangle[2] = idx1;
    }
}
