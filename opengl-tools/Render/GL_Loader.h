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

uint32_t UploadTexture(std::string name, bool pixelated);

//MeshDetails UploadMesh(const std::vector<Vertex>& verts, const std::vector<uint32_t> elem, DrawType_t type);
MeshDetails UploadMesh(const ROM_Mesh& mesh);
MeshDetails UploadMesh(RAM_Mesh const& mesh);


void UnloadMesh(MeshDetails&);


#endif /* GL_Loader_h */
