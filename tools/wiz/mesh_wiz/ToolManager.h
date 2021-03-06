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

#ifndef _TOOLMANAGER_H_
#define _TOOLMANAGER_H_

#include "ConvertTool.h"
#include "TransformTool.h"
#include "OptimizeTool.h"
#include "FrontFaceTool.h"
#include "BakeTool.h"
#include "MeshTool.h"


namespace assembly3d
{
    class Mesh;
    namespace wiz
    {
        /**
         * @brief Class for managing the different tool classes.
         *
        */
        class ToolManager
        {
        public:
            /**
             * @brief Constructor.
             *
             * @param mesh The mesh to work on.
             * @param verbose True for verbose output.
             */
            ToolManager(Mesh* mesh, bool verbose);
            ~ToolManager();

            /**
             * @brief Converts index type.
             *
             * @param type The new index type (UNSIGNED_BYTE, UNSIGNED_SHORT and UNSIGNED_INT)
             */
            bool convertIndexType(const char* type);
            /**
             * @brief Translates mesh.
             *
             * @param tx
             * @param ty
             * @param tz
             */
            void translate(float tx, float ty, float tz, bool transformTexCoords=false);
            /**
             * @brief Rotates mesh.
             *
             * @param rangle
             * @param rx
             * @param ry
             * @param rz
             */
            void rotate(float rangle, float rx, float ry, float rz, bool transformTexCoords=false);
			
			void remapAxes(const char* newX, const char* newY, const char* newZ);
            
			/**
             * @brief Scales mesh.
             *
             * @param sx
             * @param sy
             * @param sz
             */
            void scale(float sx, float sy, float sz, bool transformTexCoords=false);
            /**
             * @brief Resizes mesh.
             *
             * @param rsx
             * @param rsy
             * @param rsz
             */
            void resize(float rsx, float rsy, float rsz, bool transformTexCoords=false);
            /**
             * @brief Resizes mesh.
             *
             * @param axis
             * @param val
             */
            void resize(const char* axis, float val, bool transformTexCoords=false);
            /**
             * @brief Centers mesh.
             *
             * @param axisX
             * @param axisY
             * @param axisZ
             */
            void center(int axisX, int axisY, int axisZ, bool transformTexCoords=false);
            /**
             * @brief Stiches mesh.
             *
             */
            void stitch();
            /**
             * @brief Stiches mesh.
             *
             * @param attributeName
             * @param epsilon
             */
            void stitchEps(const char* attributeName, float epsilon);
            /**
             * @brief Flips front-face.
             *
             */
            void flip();
			
			void flipWinding();
            /**
             * @brief Tests normal consitency.
             *
             */
            bool makeNormalsConsistent();
            bool checkFrontFaceConsistenty(int& numOutwards, int& numInwards);

            int checkBakeable();
            int checkUVOverlapping();

            void mergeMeshes(Mesh* second);

        protected:
        private:
            Mesh* m_mesh;
            bool m_verboseOutput;

            ConvertTool* m_convertTool;
            TransformTool* m_transformTool;
            OptimizeTool* m_optimizeTool;
            FrontFaceTool* m_frontFaceTool;
            BakeTool* m_textureTool;
            MeshTool* m_meshTool;
        };
    }
}

#endif  // _TOOLMANAGER_H_
