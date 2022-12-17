#include "GL_Loader.h"
//
//  GL_Loader.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/16/22.
//
//
#define GLFW_INCLUDE_GLCOREARB
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/include/stb_image.h"
using namespace std;
using namespace glm;

static uint32_t textureSlotsInUse = 0;
uint32_t UploadTexture(string name, bool pixelated){
    int w, h, c;
    uint32_t textureId;
    string path = "assets/" + name + ".png";
    //GET PIXELS
    uint8_t* pixels = stbi_load(path.c_str(), &w, &h, &c, 0);
    //PARAMS
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
    //UPLOAD
    uint32_t mipLevel = 0;
    uint32_t internalFormat;
    uint32_t format;
    switch(c){
        case 1:
            internalFormat = GL_R32F;
            format = GL_RED;
            break;
        case 2:
            internalFormat = GL_RG32F;
            format = GL_RG;
            break;
        case 3:
            internalFormat = GL_RGB32F;
            format = GL_RGB;
            break;
        case 4:
            internalFormat = GL_RGBA32F;
            format = GL_RGBA;
            break;
        default:
            internalFormat = GL_RGBA32F;
            format = GL_RGBA;
            break;
    }
    
    glTexImage2D(GL_TEXTURE_2D, mipLevel, internalFormat,
                 w, h, 0, format, GL_UNSIGNED_BYTE, pixels);
    
    stbi_image_free(pixels);
    uint32_t texSlot = textureSlotsInUse++;
    glActiveTexture(GL_TEXTURE0 + texSlot);
    glBindTexture(GL_TEXTURE_2D, textureId);
    return texSlot;
}


 MeshDetails UploadMesh(const vector<Vertex>& verts, const vector<uint32_t> elem, DrawType_t type){
    if (verts.empty() || elem.empty()){
        throw("empty vectors!");
    }
    
    uint32_t VAO, VBO, EBO;
    
    glGenVertexArrays(1, &VAO);
    //cout << VAO << endl;
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex),
                          (const void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex),
                          (const void*)offsetof(Vertex, UV));
    glEnableVertexAttribArray(1);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size() * sizeof(uint32_t), elem.data(), GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    return MeshDetails(VAO, elem.size()&0xFFFFFFFF, type);
}


 void UnloadMesh(MeshDetails& d){
    glDeleteBuffers(1, &d.vao);
}
