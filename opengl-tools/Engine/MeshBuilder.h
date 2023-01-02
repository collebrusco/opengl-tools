//
//  MeshBuilder.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 1/1/23.
//
//

#ifndef MeshBuilder_h
#define MeshBuilder_h

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <vector>
#include "../Render/Vertex.h"

#include <iostream>
static void outv3(glm::vec3 a){
    std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ")\n";
}
class Quad {
    // pin is coord of corner, a and b are two vecs making up the quad
    glm::vec3 a, b, pin;
public:
    Quad(glm::vec3 A, glm::vec3 B, glm::vec3 C){
        pin = A;
        a = B;// - A;
        b = C;// - A;
//        std::cout << "A: "; outv3(this->A());
//        std::cout << "B: "; outv3(this->B());
//        std::cout << "C: "; outv3(this->C());
//        std::cout << "D: "; outv3(D());
    }
    glm::vec3 A(){
        return pin;
    }
    glm::vec3 B(){
        return pin + a;
    }
    glm::vec3 C(){
        return pin + b;
    }
    glm::vec3 D(){
        return pin + a + b;
    }
};
class MeshBuilder {
    RAM_Mesh& mesh;
    bool hasV(Vertex const& vTar, uint32_t& idx){
        for (int i = 0; i < (mesh.verticies.size()); i++){
            auto const& v = mesh.verticies.at(i);
            if ((v.pos == vTar.pos) && (v.UV == vTar.UV)){
                idx = i;
                return true;
            }
        }
        idx = (uint32_t)mesh.verticies.size();
        return false;
    }
    uint32_t addV(Vertex const& vTar){
        uint32_t i;
        if (hasV(vTar, i)){return i;}
        i = (uint32_t)mesh.verticies.size();
        mesh.verticies.push_back(vTar);
        return i;
    }
    glm::vec2 toUV(glm::vec3 const& a){
        return glm::vec2(a.x + 0.5, a.z + 0.5);
    }
    uint32_t addV(glm::vec3 p){
        return addV(Vertex(p, toUV(p)));
    }
    void addE(uint32_t e){
        mesh.elements.push_back(e);
    }
public:
    MeshBuilder(RAM_Mesh& m) : mesh(m) {}
    void addFace(Quad q){
        auto ai = addV(q.A());
        auto bi = addV(q.B());
        auto ci = addV(q.C());
        auto di = addV(q.D());
        addE(ai); addE(di); addE(bi);
        addE(ai); addE(di); addE(ci);
    }
    void addFace(glm::vec3 A, glm::vec3 B, glm::vec3 C){
        this->addFace(Quad(A, B, C));
    }
    void clear(){
        mesh.verticies.clear();
        mesh.elements.clear();
    }
    RAM_Mesh const& getMesh(){
        return mesh;
    }
};
#endif /* MeshBuilder_h */
