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
static const bool OUT_FPS = true;
double dt;

Environment scene;

static void init_test_field(Environment& env){
    const int width = 32;
    for (int i = 0; i < width*width; i++){
        auto& e = env.addEntity();
        glm::vec3 pos(0, -8.f, 0);
        pos.x = (-(width/2)) + (i % width);
        pos.z = (-(width/2)) + (i / width);
        e.pushComponent(new RenderComponent(2, 0));
        e.pushComponent(new TransformComponent(pos, glm::vec3(90, 0, 0)));
    }
}



#include "MeshBuilder.h"
#include <stdlib.h>
class Chunk : public Entity {
    glm::vec3 pos;
    RAM_Mesh mesh;
    RAM_Mesh& genMesh(){
        MeshBuilder mb(mesh);
        mb.addFace(glm::vec3(0.4, 0, 0.4), glm::vec3(0.1, 0, 0), glm::vec3(0, 0, 0.1));
        mb.addFace(glm::vec3(-0.5, 0, -0.5), glm::vec3(0.1, 0, 0), glm::vec3(0, 0, 0.1));
        mb.addFace(glm::vec3(0.4, 0, -0.5), glm::vec3(0.1, 0, 0), glm::vec3(0, 0, 0.1));
        mb.addFace(glm::vec3(-0.5, 0, 0.4), glm::vec3(0.1, 0, 0), glm::vec3(0, 0, 0.1));

        mb.addFace(glm::vec3(-0.5, 0, -0.4), glm::vec3(0, 0, 0.8), glm::vec3(0.1, 0, 0));    // left strip
        mb.addFace(glm::vec3(0.4, 0, -0.4), glm::vec3(0, 0, 0.8), glm::vec3(0.1, 0, 0));        // right strip
        mb.addFace(glm::vec3(-0.4, 0, 0.5), glm::vec3(0.8, 0, 0), glm::vec3(0, 0, -0.1));       // top strip
        mb.addFace(glm::vec3(-0.4, 0, -0.4), glm::vec3(0.8, 0, 0), glm::vec3(0, 0, -0.1));    // bot strip

        float h = ((float)(rand() & 0xFF)) / 75;
//        std::cout << h << "\n";
        mb.addFace(glm::vec3(-0.4, h, -0.4), glm::vec3(0.8, 0, 0), glm::vec3(0, 0, 0.8));   // top
        mb.addFace(glm::vec3(-0.4, 0, -0.4), glm::vec3(0, 0, 0.8), glm::vec3(0, h, 0));    // left side
        mb.addFace(glm::vec3(0.4, 0, -0.4), glm::vec3(0, 0, 0.8), glm::vec3(0, h, 0));    // right side
        mb.addFace(glm::vec3(-0.4, 0, -0.4), glm::vec3(0.8, 0, 0), glm::vec3(0, h, 0));    // back side
        mb.addFace(glm::vec3(-0.4, 0, 0.4), glm::vec3(0.8, 0, 0), glm::vec3(0, h, 0));    // front side

        return mesh;
    }
public:
    Chunk(uint32_t ID, glm::vec3 p) : Entity(ID), mesh(TRIANGLES) {
        pos = p;
        this->addComponent(new TransformComponent(pos));
        this->addComponent(new RenderComponent((uint32_t)Meshes.size(), 0));
        Meshes.emplace_back(UploadMesh(this->genMesh()));
    }
    ~Chunk(){
        UnloadMesh(Meshes.at(this->comp<RenderComponent>().meshID));
    }
};

static void init_test_example(Environment& env){
//    auto& example = env.addEntity();
//    example.pushComponent(new RenderComponent(2, 0));
//    example.pushComponent(new TransformComponent(glm::vec3(0.f, -0.5f, -2.f), glm::vec3(0, 0, 0)));
    env.addEntity(new Chunk(0, glm::vec3(0, -1, 0)));
}
static void init_test_chunkscape(Environment& env){
    ftime::stopwatch_start();
    cout << "Loading test chunkscape...\n";
    env.cam->pos.y = 5;
    srand(0x36F72AD2);
    static const int w = 64;
    for(int i = 0; i < w; i++){
        for(int j = 0; j < w; j++){
            env.addEntity(new Chunk(0, glm::vec3(i-(w/2), 0, j-(w/2))));
        }
    }
    cout << "loading took " << ftime::stopwatch_read(ftime::SECONDS) << "s\n";
}

void context_init(){
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glEnable(GL_DEPTH_TEST);
    
    Shaders.emplace_back("basic_vert_shader", "noise_frag_shader");
    Shaders.emplace_back("basic_vert_shader", "single_color_frag_shader");

    Meshes.push_back(UploadMesh(TileMesh));
    Meshes.push_back(UploadMesh(TileOutlineMesh));
    Meshes.push_back(UploadMesh(CubeMesh));
    RAM_Mesh cubeMesh(TRIANGLES);
//    MeshBuilder mb(cubeMesh);
//    mb.addFace(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f));
//    mb.addFace(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f));
//    //    mb.addFace(glm::vec3(-0.5, -0.5, 0), glm::vec3(0.5, -0.5, 0), glm::vec3(-0.5, 0.5, 0));
//
//    Meshes.push_back(UploadMesh(mb.getMesh()));
    
    scene.init();
    init_test_chunkscape(scene);
//    init_test_field(scene);
    
    window.setMouseGrabbed(true);
}

static void SyncCamera(const Environment& env){
    CameraData cd = env.cameraData();
    for (auto s : Shaders){
        s.uMat4("uView", cd.view);
        s.uMat4("uProj", cd.proj);
    }
}

static void RenderEnvironment(const Environment& env){
    double total_time = ftime::stopwatch_read(ftime::MICROSECONDS);
    double render_time = 0;
    double math_time = 0;
    double ecs_time = 0;
    double temp;
    SyncCamera(env);
    for (auto ep : env.entities){
        Entity& e = *(ep.second);
        temp = ftime::stopwatch_read(ftime::MICROSECONDS);
        if (e.hasComp(TransformType) && e.hasComp(RenderType)){
            auto & tcomp = e.comp<TransformComponent>();
            auto const& rcomp = e.comp<RenderComponent>();
            temp = ftime::stopwatch_read(ftime::MICROSECONDS) - temp;
            ecs_time += temp;
            temp = ftime::stopwatch_read(ftime::MICROSECONDS);
            auto const& model = tcomp.genModel();
            temp = ftime::stopwatch_read(ftime::MICROSECONDS) - temp;
            math_time += temp;
            temp = ftime::stopwatch_read(ftime::MICROSECONDS);
            Shaders.at(rcomp.shaderID).bind();
            Shaders.at(rcomp.shaderID).uMat4("uModel", model);
//            static const glm::vec3 color(1.f,0.f,0.f);
//            Shaders.at(rcomp.shaderID).uVec3("uColor", color); // test
            DrawMesh(Meshes.at(rcomp.meshID));
            temp = ftime::stopwatch_read(ftime::MICROSECONDS) - temp;
            render_time += temp;
        } else {
            temp = ftime::stopwatch_read(ftime::MICROSECONDS) - temp;
            ecs_time += temp;
        }
    }
    total_time = ftime::stopwatch_read(ftime::MICROSECONDS) - total_time;
    cout << "Render time:\n\ttotal: " << total_time << "us\n\tmath: " << math_time << "us\n\tecs: " << ecs_time << "us\n\trender: " << render_time << "us\n";
}

static void test_bounce(Environment& env, double dt){
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

static void test_controller(Environment& env, double dt){
    float speed = 2;
    if (window.keyboard.keys[GLFW_KEY_TAB].down){
        speed = 20;
    }
    if (window.keyboard.keys[GLFW_KEY_SPACE].down){
        env.cam->pos.y += speed * dt;
    }
    if (window.keyboard.keys[GLFW_KEY_LEFT_SHIFT].down){
        env.cam->pos.y -= speed * dt;
    }
    if (window.keyboard.keys[GLFW_KEY_W].down){
        env.cam->pos.x += (speed * -sin((double)(((PerspectiveCamera*)(env.cam))->theta))) * dt;
        env.cam->pos.z += (speed * -cos((double)(((PerspectiveCamera*)(env.cam))->theta))) * dt;
    }
    if (window.keyboard.keys[GLFW_KEY_A].down){
        env.cam->pos.x += (speed * -cos((double)(((PerspectiveCamera*)(env.cam))->theta))) * dt;
        env.cam->pos.z += (speed * sin((double)(((PerspectiveCamera*)(env.cam))->theta))) * dt;
    }
    if (window.keyboard.keys[GLFW_KEY_D].down){
        env.cam->pos.x += (speed * cos((double)(((PerspectiveCamera*)(env.cam))->theta))) * dt;
        env.cam->pos.z += (speed * -sin((double)(((PerspectiveCamera*)(env.cam))->theta))) * dt;
    }
    if (window.keyboard.keys[GLFW_KEY_S].down){
        env.cam->pos.x += (speed * sin((double)(((PerspectiveCamera*)(env.cam))->theta))) * dt;
        env.cam->pos.z += (speed * cos((double)(((PerspectiveCamera*)(env.cam))->theta))) * dt;
    }
    if (window.keyboard.keys[GLFW_KEY_T].pressed){
        window.setMouseGrabbed(!window.getMouseGrabbed());
    }
}

static void test_rotate(Environment& env, double dt){
    uint32_t i = 0;
    for (auto ep : env.entities){
        if (!i++){continue;}
        auto& e = *(ep.second);
        auto& tcomp = e.comp<TransformComponent>();
        tcomp.rotation.x += 15*dt;
        tcomp.rotation.y += 30*dt;
    }
}
#include <cmath>
static void test_chunkscape(Environment& env, double dt){
    cout << "entering cs test...\n";
    for (auto& en : env.entities){
        auto& e = *en.second;
        auto const& tcomp = e.comp<TransformComponent>();
        if (glm::distance(glm::vec2(tcomp.pos.x, tcomp.pos.z), glm::vec2(env.cam->pos.x, env.cam->pos.z)) > 64){
            env.removeEntity(e.ID);
        }
    }
//    glm::vec2 pos(env.cam->pos.x, env.cam->pos.z);
//    pos.x = round(pos.x);
//    pos.y = round(pos.y);
//    for (int x = pos.x - 64; x < pos.x - (64*0.707); x++){
//        for (int z = pos.y - 64; z < pos.y + 64; z++){
//
//        }
//    }
    cout << "returning from cs test..\n";
}

void context_loop(){
    ftime::stopwatch_start();
    while (!glfwWindowShouldClose(window.handle)){
//        glfwWaitEventsTimeout(WAIT_TIME);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // wait events and clear buffer
        
        // ****************************TESTING********************************
        scene.update(dt);
//        test_bounce(scene, dt);
//        test_rotate(scene, dt);
//        test_field(scene, dt);
        double timer = ftime::stopwatch_read(ftime::NANOSECONDS);
        test_controller(scene, dt);
        timer = ftime::stopwatch_read(ftime::NANOSECONDS) - timer;
        cout << "controller nanos: " << timer << "ns\n";
        timer = ftime::stopwatch_read(ftime::MILLISECONDS);
        test_chunkscape(scene, dt);
        timer = ftime::stopwatch_read(ftime::MILLISECONDS) - timer;
        cout << "chunkscape nanos: " << timer << "ms\n";
//        test_rotate(scene, dt);
        timer = ftime::stopwatch_read(ftime::MILLISECONDS);
        RenderEnvironment(scene);
        timer = ftime::stopwatch_read(ftime::MILLISECONDS) - timer;
        cout << "render nanos: " << timer << "ms\n------\n";
        // **************************END_TESTING******************************

        window.update();
        dt = ftime::stopwatch_stopstart(ftime::SECONDS);
        if (OUT_FPS){
//            cout << 1/dt << "\n";
        }
    }
}

void context_close(){
    cout << "window closed!\n";
    glfwTerminate();
}
