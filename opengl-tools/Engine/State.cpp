//
//  State.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 1/2/23.
//
//

#include "State.h"
#include "../Render/Meshes.h"
#include "../Render/GL_Loader.h"

State state;

State::State() : meshes(0x00002000) {};

bool State::initShaders(){
    bool flag = true;
    if (!shaders[NOISE_SHADER].compileAndLink("basic_vert_shader", "noise_frag_shader")){
        flag = false;
    };
    if (!shaders[DEFAULT_SHADER].compileAndLink("basic_vert_shader", "single_color_frag_shader")){
        flag = false;
    }
    if (!shaders[TEXTURE_SHADER].compileAndLink("vert_shader", "frag_shader")){
        flag = false;
    }
    return flag;
}

void State::initMeshes(){\
    meshes.force(UploadMesh(TileMesh), TILE_MESH);
    meshes.force(UploadMesh(TileOutlineMesh), TILE_OUTLINE_MESH);
    meshes.force(UploadMesh(CubeMesh), CUBE_MESH);
}

void State::init(){
    this->initShaders();
    this->initMeshes();
}

Shader const& State::shader(ShaderType type){
    return shaders[type];
}

MeshDetails const& State::mesh(uint32_t i){
    assert(i < meshes.size());
    return meshes[i];
}

uint32_t State::pushMesh(RAM_Mesh m){
    return meshes.push(UploadMesh(m));
}
