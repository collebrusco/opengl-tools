//
//  State.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 1/2/23.
//
//

#ifndef State_h
#define State_h
#include <vector>
#include "../Render/Shader.h"
#include "../Render/Vertex.h"
#include "../util/ObjectPool.h"

#define SHADER_LAST TEXTURE_SHADER
#define ITERATE_SHADERS int i = 0; i < SHADER_LAST; i++
enum ShaderType {
    DEFAULT_SHADER = 0,
    NOISE_SHADER,
    TEXTURE_SHADER,
};

enum MeshType {
    TILE_MESH = 0,
    TILE_OUTLINE_MESH,
    CUBE_MESH
};

class State {
private:
//    vector<MeshDetails> meshes;
    ObjectPool<MeshDetails> meshes;
    void initShaders();
    void initMeshes();
public:
    std::vector<Shader> shaders;
    State();
    void init();
    MeshDetails const& mesh(uint32_t);
    uint32_t pushMesh(RAM_Mesh);
    void popMesh(uint32_t);
};

extern State state;

#endif /* State_h */
