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

#include "AnimationLoader.h"
#include <libxml/xmlreader.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Utils.h"

using namespace std;

static void processAnimamtionNode(xmlTextReaderPtr reader, AnimationLoader* loader);

AnimationLoader::AnimationLoader(Animation* anim,
                       const char* metafilename,
                       const char* datafilename)
    :
      animation(anim)
{
    file.open(datafilename, ios::binary);
    file.seekg(0);

    xmlTextReaderPtr reader = xmlReaderForFile(metafilename, NULL, 0);
    assert(reader != NULL);

    int ret = xmlTextReaderRead(reader);
    while (ret == 1)
    {
        processAnimamtionNode(reader, this);
        ret = xmlTextReaderRead(reader);
    }
    xmlFreeTextReader(reader);
    assert(ret == 0);
}

static void processAnimamtionNode(xmlTextReaderPtr reader, AnimationLoader* loader)
{
    const char *name = (const char*)xmlTextReaderConstName(reader);
    assert (name != NULL);

    int nodeType = xmlTextReaderNodeType(reader);
    if(nodeType != 1)
    {
        return;
    }

    if(strcmp("Sampler", name) == 0)
    {
        float duration = 0;
        int channelCount = 0;
        xmlChar* durVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "duration");
        if(durVal)
            duration = atof ((const char*) durVal);
        xmlChar* numChVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "channels");
        if(numChVal)
            channelCount = atoi ((const char*) numChVal);
        loader->sampler(duration, channelCount);
        xmlFree(durVal);
        xmlFree(numChVal);

    }
    else if(strcmp("Channel", name) == 0)
    {
        xmlChar* nameVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "name");
        xmlChar* keyFramesVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "keyframes");
        xmlChar* fromVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "from");
        xmlChar* toVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "to");
        xmlChar* attributesVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "attributes");

        const char* chName = "";
        int keyframes = 0;
        float from = 0.0f;
        float to = 1.0f;
        int countAttributes = 0;
        if(nameVal)
            chName = (const char*) nameVal;
        if(keyFramesVal)
            keyframes = atoi((const char*) keyFramesVal);
        if(fromVal)
            from = atof((const char*) fromVal);
        if(toVal)
            to = atof((const char*) toVal);
        if(attributesVal)
            countAttributes = atoi((const char*) attributesVal);

        loader->channel(chName, keyframes, from, to, countAttributes);
        xmlFree(nameVal);
        xmlFree(keyFramesVal);
        xmlFree(fromVal);
        xmlFree(toVal);
        xmlFree(attributesVal);
    }
    else if(strcmp("Attribute", name) == 0)
    {
        xmlChar* nameVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "name");
        xmlChar* sizeVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "size");
        xmlChar* typeVal = xmlTextReaderGetAttribute(reader, (xmlChar*) "type");

        const char* attributeName = "";
        int attributeSize = 0;
        const char* attributeType = "FLOAT";
        if(nameVal)
            attributeName = (const char*) nameVal;
        if(sizeVal)
            attributeSize = atof((const char*) sizeVal);
        if(typeVal)
            attributeType = (const char*) typeVal;

        loader->attribute(attributeName, attributeSize);
        xmlFree(nameVal);
        xmlFree(sizeVal);
        xmlFree(typeVal);
    }

}

void AnimationLoader::sampler(float duration, int countChannels)
{
    animation->duration = duration;
    animation->countChannels = countChannels;
    animation->channels.clear();
}

void AnimationLoader::channel(const char *name, int keyframes, float from, float to, int countAttributes)
{
    AnimationChannel* channel = new AnimationChannel();
    channel->name = name;
    channel->keyframes = keyframes;
    channel->duration = animation->duration;
    channel->countAttributes = countAttributes;
    channel->positions = new float[keyframes*3];
    channel->orientations = new float[keyframes*4];
    channel->fromTime = from;
    channel->toTime = to;
    animation->channels.push_back(channel);
}

void AnimationLoader::attribute(const char* name, int size)
{
    AnimationChannel* ch = animation->channels.back();

    if(string(name).compare("POSITION") == 0)
    {
        for(int j = 0; j < ch->keyframes; ++j)
        {
            for(int i = 0; i < size; ++i)
            {
                float value = 0.0f;
                file.read((char *)(&value), sizeof(value));
                ch->positions[j*3+i] = value;
            }
        }
    }
    else if(string(name).compare("ORIENTATION") == 0)
    {
        for(int j = 0; j < ch->keyframes; ++j)
        {
            for(int i = 0; i < size; ++i)
            {
                float value = 0.0f;
                file.read((char *)(&value), sizeof(value));
                ch->orientations[j*4+i] = value;
            }
            if(size == 3)
            {
                float w = Utils::calculateQuaternionW(ch->orientations[j*4+0],
                                                      ch->orientations[j*4+1],
                                                      ch->orientations[j*4+2]);
                ch->orientations[j*4+3] = w;
            }
        }
    }
}
