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
    SyncCamera(env);
    for (auto ep : env.entities){
        Entity& e = *(ep.second);
        if (e.hasComp(TransformType) && e.hasComp(RenderType)){
            auto const& tcomp = e.comp<TransformComponent>();
            auto const& rcomp = e.comp<RenderComponent>();
            glm::mat4 model = genModelMat(tcomp.pos, tcomp.rotation, tcomp.scale);
            
            Shaders.at(rcomp.shaderID).bind();
            Shaders.at(rcomp.shaderID).uMat4("uModel", model);
            static const glm::vec3 color(1.f,0.f,0.f);
            Shaders.at(rcomp.shaderID).uVec3("uColor", color); // test
            DrawMesh(Meshes.at(rcomp.meshID));
        }
    }
}

static void test_bounce(Environment env, double dt){
    static glm::vec2 v(2.f,2.f);
    static int mod = 1;
    for (auto ep : env.entities){
        Entity& e = *(ep.second);
        float h = ((10/window.aspect)/2) - 0.5f;
        auto& tcomp = e.comp<TransformComponent>();
        auto& rcomp = e.comp<RenderComponent>();
        if (((tcomp.pos.x + (v.x * dt)) > 4.5) || ((tcomp.pos.x + (v.x * dt)) < -4.5)){
            v.x *= -1;
        }
        if (((tcomp.pos.y + (v.y * dt)) > h) || ((tcomp.pos.y + (v.y * dt)) < -h)){
            v.y *= -1;
        }
        tcomp.pos.x += (v.x * dt);
        tcomp.pos.y += (v.y * dt);
        tcomp.rotation.z += (45.f * dt);
        if (!(mod++ % 30)) rcomp.shaderID ^= 0x01;
    }
}

void context_loop(){
    ftime::stopwatch_start();
    while (!glfwWindowShouldClose(window.handle)){
        glfwWaitEventsTimeout(WAIT_TIME);
        glClear(GL_COLOR_BUFFER_BIT);       // wait events and clear buffer
        
        // ****************************TESTING********************************
        scene.update(dt);
        test_bounce(scene, dt);
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
    scene.destroy();
    cout << "window closed!\n";
    glfwTerminate();
}
