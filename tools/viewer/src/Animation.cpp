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

#include "Animation.h"
#include <math.h>
#include "Location3D.h"
#include <iostream>

AnimationChannel::AnimationChannel()
{
}
AnimationChannel::~AnimationChannel()
{
    if(positions)
        delete[] positions; positions = 0;
    if(orientations)
        delete[] orientations; orientations = 0;
}

void AnimationChannel::update(float elapsedTime, Location3D& loc)
{
    float remainder = fmodf(elapsedTime, duration);
    float dur2 = toTime - fromTime;
    float pos = 0.0f;
    if(remainder > fromTime)
        pos = remainder-fromTime;
    int idx = (pos * keyframes) / dur2;
    if(pos > dur2)
        idx = keyframes;

    loc.x = positions[idx*3+0];
    loc.y = positions[idx*3+1];
    loc.z = positions[idx*3+2];
    loc.quatX = orientations[idx*4+0];
    loc.quatY = orientations[idx*4+1];
    loc.quatZ = orientations[idx*4+2];
    loc.quatW = orientations[idx*4+3];
}
