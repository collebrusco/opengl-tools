//
//  State.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 1/2/23.
//
//  This global state tracks global objects associated with OpenGL Such as shaders and meshes.
//  When a shader/mesh is uploaded, it exists globally throughout the program as it lives on the GPU
//  So here it's modelled with a global state so the CPU can work with it as what it is, global state

#ifndef State_h
#define State_h
#include <vector>
#include "../Render/Shader.h"
#include "../Render/Vertex.h"
#include "../util/ObjectPool.h"

#define SHADER_LAST TEXTURE_SHADER
#define ITERATE_SHADERS int i = 0; i <= SHADER_LAST; i++
// Shaders are never added dynamically,
// so all should be registered here
// and compiled & linked in initShaders()
// in order so the enum is the index
enum ShaderType {
    DEFAULT_SHADER = 0,
    NOISE_SHADER,
    TEXTURE_SHADER,
};

// Meshes can be uploaded/unloaded on the fly
// So these enums are only for hardcoded meshes
// These are defined in Render/Meshes.h and
// added to pool in initMeshes() in proper order
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
    ~State();
    void init();
    MeshDetails const& mesh(uint32_t);
    uint32_t pushMesh(RAM_Mesh);
    void popMesh(uint32_t);
};

extern State state;

#endif /* State_h */
