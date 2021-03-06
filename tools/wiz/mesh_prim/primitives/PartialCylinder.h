/*
 * Copyright (c) 2011 Peter Vasil, Michael Nischt
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

#ifndef PARTIALCYLINDER_H
#define PARTIALCYLINDER_H

#include "../Primitive.h"

namespace assembly3d
{
    namespace prim
    {
        /**
         * @brief Partial cylinder primitive class.
         *
         */
        class PartialCylinder : public Primitive
        {
        public:
            /**
             * @brief Constructor.
             *
             * @param base
             * @param top
             * @param height
             * @param slices
             * @param stacks
             * @param start
             * @param sweep
             */
            PartialCylinder(float base, float top, float height, int slices,
                            int stacks, float start, float sweep);
            virtual ~PartialCylinder();

            /**
             * @brief
             *
             * @param mesh The mesh object to write in.
             * @param positions True if positions should be generated.
             * @param normals True if normals should be generated.
             * @param texCoords True if texCoords should be generated.
             * @param tangents True if tangents should be generated.
             * @param bitangents True if bitangents should be generated.
             */
            void create(Mesh* mesh, bool positions, bool normals,
                        bool texCoords, bool tangents, bool bitangents);

        private:
            float m_base;
            float m_top;
            float m_height;
            float m_start;
            float m_sweep;
        };
    }
}

#endif // PARTIALCYLINDER_H
