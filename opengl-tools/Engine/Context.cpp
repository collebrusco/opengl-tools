//
//  Context.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/17/22.
//
//

#include "Context.h"
#define GLFW_INCLUDE_GLCOREARB
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <vector>

#include "Window.h"
#include "../Render/Meshes.h"
#include "../Render/GL_Loader.h"
#include "../Render/GL_Draw.h"
#include "../Shader.h"
#include "../util/f_time.h"

static vector<Shader> Shaders;
static vector<MeshDetails> Meshes;
static const float WAIT_TIME = (1.f / 120.f);
double dt;

void context_init(){
    Shaders.emplace_back("basic_vert_shader", "noise_frag_shader");
    Shaders.emplace_back("basic_vert_shader", "single_color_frag_shader");
    glClearColor(0.f, 0.f, 0.f, 0.f);

    Meshes.push_back(UploadMesh(TileMesh));
    Meshes.push_back(UploadMesh(TileOutlineMesh));
}

void context_loop(){
    ftime::stopwatch_start();
    while (!glfwWindowShouldClose(window.handle)){
        glfwWaitEventsTimeout(WAIT_TIME);
        glClear(GL_COLOR_BUFFER_BIT);       // wait events and clear buffer
        
        Shaders.at(0).bind();
        Shaders.at(0).uVec3("uColor", glm::vec3(1.f,0.2f,0.2f));
        DrawMesh(Meshes.at(0));
        Shaders.at(0).bind();
        Shaders.at(0).uVec3("uColor", glm::vec3(1.f, 0.2f, 0.2f));
        DrawMesh(Meshes.at(1));
        window.update();
        
        dt = ftime::stopwatch_stop(ftime::SECONDS);
        ftime::stopwatch_start();
    }
}

void context_close(){
    cout << "window closed!\n";
    glfwTerminate();
}
