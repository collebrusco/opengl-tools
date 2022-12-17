#include "Vertex.h"
//
//  Vertex.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/16/22.
//
#include <glm/vec2.hpp>
#include <glm/vec3.hpp> // glm::vec3

Vertex::Vertex(){
    pos = glm::vec3(0);
    UV = glm::vec2(0);
}

Vertex::Vertex(glm::vec3 p){
    pos = p;
    UV = glm::vec2(0);
}

Vertex::Vertex(glm::vec3 p, glm::vec2 uv){
    pos = p;
    UV = uv;
}
