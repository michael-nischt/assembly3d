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

#include "App.h"
#include "Location3D.h"
#include <cmath>
#include <algorithm>
#include "Utils.h"
#include "Animation.h"
#include "AnimationLoader.h"

using namespace std;

extern bool playAnimation;

App::App()
{
}

App::~App()
{
    for (size_t i = 0; i < locs.size(); ++i) {
        if(locs[i])
        {
            delete locs[i];
            locs[i] = 0;
        }
    }
    if(graphics)
        delete graphics; graphics = NULL;
}

void App::init(Resources* r)
{
    graphics = new Graphics();

    graphics->init();

    graphics->setSceneScale(r->sceneScale);

    for(int i = 0; i < r->numObj; ++i)
    {
        Location3D* loc = new Location3D();
        loc->x = r->positions[i][0];
        loc->y = r->positions[i][1];
        loc->z = r->positions[i][2];
        
        loc->quatX = r->orientations[i][0];
        loc->quatY = r->orientations[i][1];
        loc->quatZ = r->orientations[i][2];
        if(r->orientations[i].size() == 4)
            loc->quatW = r->orientations[i][3];
        else
            loc->quatW = Utils::calculateQuaternionW(loc->quatX, loc->quatY, loc->quatZ);
        
        Mesh* mesh;
        mesh = graphics->loadMesh(r->meshPaths[i].c_str(), r->dataPaths[i].c_str());

        std::vector<std::string> texPaths;
        for (int j = 0; j < mesh->getNGroups(); ++j) {
            string tPath = r->texPaths[i] + string(mesh->getGroupName(j));
            string tPathWithExt = Utils::getTextureImagePathWithExt(tPath.c_str());
            texPaths.push_back(tPathWithExt);
            //graphics->loadTexture(tPath.c_str());
        }
        string objName = r->names[i];
        graphics->addObject(objName, loc, mesh, r->scales[i], texPaths);
        locs.push_back(loc);
    }
    for(size_t j = 0; j < r->animMetas.size(); ++j)
    {
        if( ! r->animMetas[j].empty() && ! r->animDatas[j].empty())
        {
            Animation* anim = new Animation();
            AnimationLoader al(anim,r->animMetas[j].c_str(), r->animDatas[j].c_str());

            for(size_t i = 0; i < anim->channels.size(); ++i)
            {
                graphics->addAnim(anim->channels[i]->getName(), anim->channels[i]);
            }
            delete anim;
        }
    }
}

void App::render(int width, int height)
{
    graphics->render(width, height);
}


void App::updateView(float offsetX, float offsetY, float offsetZ, 
                     float angleX, float angleY)
{
//    graphics->updateView(offset * sin(angleY), 0.0f, offset * cos(angleY));
//    graphics->updateView(0.0f, 0.0f, offsetZ);
    graphics->updateView(offsetX, offsetY, offsetZ);
    graphics->updateView(angleX, angleY);
}

void App::update(float dT)
{
    if(playAnimation)
        graphics->updateAnimation(dT);
}

