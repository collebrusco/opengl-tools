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
#include "../util/f_transform.h"
#include "Environment.h"

static vector<Shader> Shaders;
static vector<MeshDetails> Meshes;
static const float WAIT_TIME = (1.f / 120.f);
static const bool OUT_FPS = false;
double dt;

Environment scene;

void context_init(){
    glClearColor(0.f, 0.f, 0.f, 0.f);
    
    
    Shaders.emplace_back("basic_vert_shader", "noise_frag_shader");
    Shaders.emplace_back("basic_vert_shader", "single_color_frag_shader");

    Meshes.push_back(UploadMesh(TileMesh));
    Meshes.push_back(UploadMesh(TileOutlineMesh));
    
    scene.init();
}

static void SyncCamera(Environment env){
    CameraData cd = env.cameraData();
    for (auto s : Shaders){
        s.uMat4("uView", cd.view);
        s.uMat4("uProj", cd.proj);
    }
}

static void RenderEnvironment(Environment env){
    for (auto ep : env.entities){
        Entity& e = *(ep.second);
        if (e.comp(TransformType) && e.comp(RenderType)){
            const TransformComponent& tcomp = *((TransformComponent*)(e.comp(TransformType)));
            glm::mat4 model = genModelMat(tcomp.pos, tcomp.rotation, tcomp.scale);
            
            Shaders.at(((RenderComponent*)(e.comp(RenderType)))->shaderID).bind();
            Shaders.at(((RenderComponent*)(e.comp(RenderType)))->shaderID).uMat4("uModel", model);
            DrawMesh(Meshes.at(((RenderComponent*)(e.comp(RenderType)))->meshID));
        }
    }
}

static void test_bounce(Environment env, double dt){
    static glm::vec2 v(2.f,2.f);
    for (auto ep : env.entities){
        Entity& e = *(ep.second);
        float h = ((10/window.aspect)/2) - 0.5f;
        TransformComponent& tcomp = *((TransformComponent*)(e.comp(TransformType)));
        if (((tcomp.pos.x + (v.x * dt)) > 4.5) || ((tcomp.pos.x + (v.x * dt)) < -4.5)){
            v.x *= -1;
        }
        if (((tcomp.pos.y + (v.y * dt)) > h) || ((tcomp.pos.y + (v.y * dt)) < -h)){
            v.y *= -1;
        }
        tcomp.pos.x += (v.x * dt);
        tcomp.pos.y += (v.y * dt);
    }
}

void context_loop(){
    ftime::stopwatch_start();
    while (!glfwWindowShouldClose(window.handle)){
        glfwWaitEventsTimeout(WAIT_TIME);
        glClear(GL_COLOR_BUFFER_BIT);       // wait events and clear buffer
        
        // ****************************TESTING********************************
//        Shaders.at(0).bind();
//        Shaders.at(0).uVec3("uColor", glm::vec3(1.f,0.2f,0.2f));
//        DrawMesh(Meshes.at(0));
//        Shaders.at(1).bind();
//        Shaders.at(1).uVec3("uColor", glm::vec3(1.f, 0.2f, 0.2f));
//        DrawMesh(Meshes.at(1));
        scene.update(dt);
        test_bounce(scene, dt);
        SyncCamera(scene);
        RenderEnvironment(scene);
        // **************************END_TESTING******************************

        window.update();
        dt = ftime::stopwatch_stopstart(ftime::SECONDS);
        if (OUT_FPS){
            cout << 1/dt << "\n";
        }
    }
}

void context_close(){
    cout << "window closed!\n";
    glfwTerminate();
}
