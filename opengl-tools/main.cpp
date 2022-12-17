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
    Shader testShader("basic_vert_shader", "basic_frag_shader");
    glClearColor(200.0 / 255.0, 140.0 / 255.0, 80.0 / 255.0, 0.f);
    
    //TODO: vsync causes mysterious left mouse bug...
    glfwSwapInterval(1);
    
    MeshDetails tileMeshDetails = UploadMesh(TileMesh);
    testShader.bind();
    // Main Loop
    stopwatch_start();
    while(!glfwWindowShouldClose(window.handle)){
        glfwWaitEventsTimeout(1.0 / 120.0);
        glClear(GL_COLOR_BUFFER_BIT);
        DrawMesh(tileMeshDetails);
        window.update();
        cout << 1 / stopwatch_stop(ftime::SECONDS) << " FPS\n";
        stopwatch_start();
    }
    cout << "window closed!\n";
    glfwTerminate();
    return 0;
}

