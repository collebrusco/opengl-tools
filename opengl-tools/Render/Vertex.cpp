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

ROM_Mesh::ROM_Mesh(const std::vector<Vertex>& vs, const std::vector<uint32_t>& ems, DrawType_t t) : verticies(vs), elements(ems) {
    type = t;
}

RAM_Mesh::RAM_Mesh(DrawType_t t) {
    
    type = t;
}

MeshDetails::MeshDetails(){
    vao = numElements = 0;
    drawType = TRIANGLES;
}

MeshDetails::MeshDetails(uint32_t v, uint32_t e){
    vao = v; numElements = e; drawType = TRIANGLES;
}

MeshDetails::MeshDetails(uint32_t v, uint32_t e, DrawType_t dt){
    vao = v; numElements = e; drawType = dt;
}
