//
//  GL_Draw.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/16/22.
//
//
#define GLFW_INCLUDE_GLCOREARB
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include "GL_Draw.h"

void DrawMesh(MeshDetails& mesh){
    glBindVertexArray(mesh.vao);
    //TODO: error check this, glGetError()
    glDrawElements((mesh.drawType == TRIANGLES) ? GL_TRIANGLES : GL_LINES, mesh.numElements, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void DrawMesh(MeshDetails const& mesh){
    glBindVertexArray(mesh.vao);
    //TODO: error check this, glGetError()
    glDrawElements((mesh.drawType == TRIANGLES) ? GL_TRIANGLES : GL_LINES, mesh.numElements, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
