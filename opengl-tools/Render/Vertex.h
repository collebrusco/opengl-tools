//
//  Vertex.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/16/22.
//

#ifndef Vertex_h
#define Vertex_h

#include <vector>
#define GLM_FORCE_SWIZZLE
#include <glm/vec2.hpp>
#include <glm/vec3.hpp> // glm::vec3

enum DrawType_t {
    TRIANGLES, LINES
};

struct Vertex {
    Vertex();
    Vertex(glm::vec3);
    Vertex(glm::vec3, glm::vec2);
    glm::vec3 pos;
    glm::vec2 UV;
};

// Use this to create meshes
struct ROM_Mesh {
    const std::vector<Vertex>& verticies;
    const std::vector<uint32_t>& elements;
    DrawType_t type;
    ROM_Mesh(const std::vector<Vertex>& vs, const std::vector<uint32_t>& ems, DrawType_t t);
};

struct RAM_Mesh {
    std::vector<Vertex> verticies;
    std::vector<uint32_t> elements;
    DrawType_t type;
    RAM_Mesh(DrawType_t t);
};

struct MeshDetails {
    MeshDetails();
    MeshDetails(uint32_t v, uint32_t e);
    MeshDetails(uint32_t v, uint32_t e, DrawType_t dt);
    uint32_t vao;
    uint32_t numElements;
    DrawType_t drawType;
};

#endif /* Vertex_h */
