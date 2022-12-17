//
//  Meshes.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/16/22.
//

#ifndef Meshes_h
#define Meshes_h
#include <vector>
#include "Vertex.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

static const std::vector<Vertex> tile_vertices = {
    Vertex(glm::vec3(-0.5f, 0.5f, 0.f), glm::vec2(0.0f, 1.0f)),
    Vertex(glm::vec3(0.5f, 0.5f, 0.f), glm::vec2(1.0f, 1.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f, 0.f), glm::vec2(0.0f, 0.0f)),
    Vertex(glm::vec3(0.5f, -0.5f, 0.f), glm::vec2(1.0f, 0.0f)),

};

static const std::vector<uint32_t> tile_elements = {
            0, 3, 2,
            0, 1, 3
        };
const Mesh TileMesh(tile_vertices, tile_elements, TRIANGLES);

static const std::vector<uint32_t> tile_outline_elements = {
    0, 1,
    1, 3,
    3, 2,
    2, 0
};
const Mesh TileOutlineMesh(tile_vertices, tile_outline_elements, LINES);

#endif /* Meshes_h */
