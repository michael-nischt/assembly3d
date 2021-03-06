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

#include "ShaderUtils.h"
#include <fstream>
#include <iostream>

using namespace std;

ShaderUtils::ShaderUtils()
{
}

GLuint ShaderUtils::createVertexShader(const char *vsSrc)
{
    ifstream vsFile(vsSrc, ifstream::in);
    string vertexShaderSource = string(istreambuf_iterator<char>(vsFile),
                                       istreambuf_iterator<char>());

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar *vsCstr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vsCstr, 0);

    // compile shader
    glCompileShader(vertexShader);

    GLint succeeded;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succeeded);

    if (!succeeded || !glIsShader(vertexShader) )
    {
        int logLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
        string infoLog(logLength, ' ');
        glGetShaderInfoLog(vertexShader, logLength, 0, &infoLog[0]);
        cout << "Vertex-shader compile error:\n\n" << infoLog.c_str() << endl;
    }
//    else
//    {
//        cout << "Vertex-shader loaded and compiled successfully." << endl;
//    }

    return vertexShader;
}

GLuint ShaderUtils::createFragmentShader(const char *fsSrc)
{
    GLuint fragmentShader = 0;

    ifstream fsFile(fsSrc, ifstream::in);
    string fragmentShaderSource = string(istreambuf_iterator<char>(fsFile),
                                         istreambuf_iterator<char>());

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar *fsCstr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fsCstr, 0);

    glCompileShader(fragmentShader);

    GLint succeeded;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succeeded);

    if (!succeeded || !glIsShader(fragmentShader) )
    {
        int logLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
        string info_log(logLength, ' ');
        glGetShaderInfoLog(fragmentShader, logLength, 0, &info_log[0]);
        cout << "Fragment-shader compile error:\n\n" << info_log.c_str() << endl;
    }
//	else
//	{
//		cout << "Fragment-shader loaded and compiled successfully." << endl;
//	}

    return fragmentShader;
}

GLuint ShaderUtils::createProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram , vertexShader);
    glAttachShader(shaderProgram , fragmentShader);

    // before linking, define output of fragment-shader
//    glBindFragDataLocation(shaderProgram , 0, "fragColor");

    glLinkProgram(shaderProgram );

    GLint succeeded;
    glGetProgramiv(shaderProgram , GL_LINK_STATUS, &succeeded);

    if (!succeeded || !glIsProgram(shaderProgram ))
    {
        int logLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        string info_log(logLength, ' ');
        glGetProgramInfoLog(shaderProgram, logLength, 0, &info_log[0]);
        cout << "Shader-program link error:\n\n" << info_log.c_str() << endl;
    }
//    else
//    {
//        cout << "Shader-program linked successfully.\n" << endl;
//    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint ShaderUtils::createProgramFromSrcPair(const GLchar* vertexShaderSrc,
                                             const GLchar* fragmentShaderSrc)
{
    GLuint shaderProgram = 0;
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;

    // -- vertex shader --

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSrc, 0);

    // compile shader
    glCompileShader(vertexShader);

    GLint succeeded;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succeeded);

    if (!succeeded || !glIsShader(vertexShader) )
    {
        int logLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
        string infoLog(logLength, ' ');
        glGetShaderInfoLog(vertexShader, logLength, 0, &infoLog[0]);
        cout << "Vertex-shader compile error:\n\n" << infoLog.c_str() << endl;
    }
//    else
//    {
//        cout << "Vertex-shader loaded and compiled successfully." << endl;
//    }

    // -- fragment shader --

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, 0);

    // compile shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succeeded);

    if (!succeeded || !glIsShader(fragmentShader) )
    {
        int logLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
        string info_log(logLength, ' ');
        glGetShaderInfoLog(fragmentShader, logLength, 0, &info_log[0]);
        cout << "Fragment-shader compile error:\n\n" << info_log.c_str() << endl;
    }
//    else
//    {
//        cout << "Fragment-shader loaded and compiled successfully." << endl;
//    }

    // -- link shader-program --
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram , vertexShader);
    glAttachShader(shaderProgram , fragmentShader);

    glLinkProgram(shaderProgram );

    glGetProgramiv(shaderProgram , GL_LINK_STATUS, &succeeded);

    if (!succeeded || !glIsProgram(shaderProgram ))
    {
        int logLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
        string info_log(logLength, ' ');
        glGetProgramInfoLog(shaderProgram, logLength, 0, &info_log[0]);
        cout << "Shader-program link error:\n\n" << info_log.c_str() << endl;
    }
//    else
//    {
//        cout << "Shader-program linked successfully.\n" << endl;
//    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;

}
