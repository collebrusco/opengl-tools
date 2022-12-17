//
//  GL_Loader.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/16/22.
//
//

#ifndef GL_Loader_h
#define GL_Loader_h

#include "Vertex.h"
#include <string>

uint32_t UploadTexture(std::string name);

MeshDetails UploadMesh(const std::vector<Vertex>& verts, const std::vector<uint32_t> elem, std::string type);

void UnloadMesh(MeshDetails&);


#endif /* GL_Loader_h */
