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
using namespace std;

Shader testShader;
#include <iostream>

MeshDetails UploadTileMesh(){
    vector<Vertex> sqVertices(8);
                sqVertices.at(0).pos = glm::vec3(-0.5f, 0.5f, 0.f);
                sqVertices.at(0).UV = glm::vec2(0.0f, 1.0f);
                sqVertices.at(1).pos = glm::vec3(0.5f, 0.5f, 0.0f);
                sqVertices.at(1).UV = glm::vec2(1.0f, 1.0f);
                sqVertices.at(2).pos = glm::vec3(-0.5f, -0.5f, 0.0f);
                sqVertices.at(2).UV = glm::vec2(0.0f, 0.0f);
                sqVertices.at(3).pos = glm::vec3(0.5f, -0.5f, 0.0f);
                sqVertices.at(3).UV = glm::vec2(1.0f, 0.0f);

    vector<uint32_t> elems(6);
    elems = {
                0, 3, 2,
                0, 1, 3
            };
    return UploadMesh(Mesh(sqVertices,elems, TRIANGLES));
}

int main(int argc, const char * argv[]) {
    testShader.compileAndLink("basic_vert_shader", "basic_frag_shader");
    glClearColor(200.0 / 255.0, 140.0 / 255.0, 80.0 / 255.0, 0.f);
    
    //TODO: vsync causes mysterious left mouse bug...
    glfwSwapInterval(0);
    
    MeshDetails tileMeshDetails = UploadTileMesh();
//    MeshDetails tileMeshDetails = UploadMesh(TileMesh);
    testShader.bind();
    // Main Loop
    GLenum er = glGetError();
    if (er != GL_NO_ERROR){
        cout << er << "\n";
    }
    while(!glfwWindowShouldClose(window.handle)){
        glfwWaitEventsTimeout(1.0 / 120.0);
        glClear(GL_COLOR_BUFFER_BIT);
        DrawMesh(tileMeshDetails);
        window.update();
    }
    cout << "window closed!\n";
    glfwTerminate();
    return 0;
}

