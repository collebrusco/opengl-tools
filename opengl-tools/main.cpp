//
//  main.cpp
//  openGL_tools
//
//  Created by Frank Collebrusco on 12/14/22.
//

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
#include "Render/Meshes.h"
#include "Render/GL_Loader.h"
#include "Render/GL_Draw.h"
#include "Shader.h"
#include "util/f_time.h"
using namespace std;

#include <iostream>



int main(int argc, const char * argv[]) {
    Shader noiseShader("basic_vert_shader", "noise_frag_shader");
    Shader colorShader("basic_vert_shader", "single_color_frag_shader");
    glClearColor(0 / 255.0, 0 / 255.0, 0 / 255.0, 0.f);
    
    //TODO: vsync causes mysterious left mouse bug...
    glfwSwapInterval(1);
    
    MeshDetails tileMeshDetails = UploadMesh(TileMesh);
    MeshDetails tileOutlineMeshDetails = UploadMesh(TileOutlineMesh);
    // Main Loop
//    ftime::stopwatch_start();
    while (!glfwWindowShouldClose(window.handle)){
        glfwWaitEventsTimeout(1.0 / 120.0);
        glClear(GL_COLOR_BUFFER_BIT);
        colorShader.bind();
        colorShader.uVec3("uColor", glm::vec3(1.f,0.2f,0.2f));
        DrawMesh(tileMeshDetails);
        colorShader.bind();
        colorShader.uVec3("uColor", glm::vec3(1.f));
        DrawMesh(tileOutlineMeshDetails);
        window.update();
//        cout << 1 / stopwatch_stop(ftime::SECONDS) << " FPS\n";
//        ftime::stopwatch_start();
    }
    cout << "window closed!\n";
    glfwTerminate();
    return 0;
}

