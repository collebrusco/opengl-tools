//
//  Environment.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/18/22.
//
//

#ifndef Environment_h
#define Environment_h

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
#include <map>
#include <cassert>
#include "../Window.h"
#include "../Shader.h"
enum ComponentType {
    TransformType,
    RenderType,
    
};
class Component {
public:
    uint32_t ownerID; //TODO: make children set this
    ComponentType type;
};

class TransformComponent : public Component {
public:
    glm::vec3 pos;
    glm::vec3 rotation;
    glm::vec3 scale;
    TransformComponent(){
        pos = glm::vec3(0.f);
        rotation = glm::vec3(0.f);
        scale = glm::vec3(1.f);
    }
    TransformComponent(glm::vec3 p){
        pos = p;
        rotation = glm::vec3(0.f);
        scale = glm::vec3(1.f);
    }
    TransformComponent(glm::vec3 p, glm::vec3 r){
        pos = p;
        rotation = r;
        scale = glm::vec3(1.f);
    }
    TransformComponent(glm::vec3 p, glm::vec3 r, glm::vec3 s){
        pos = p;
        rotation = r;
        scale = s;
    }
};

struct RenderComponent : Component {
public:
    uint32_t meshID;
    uint32_t shaderID;
    RenderComponent(uint32_t m, uint32_t s){
        meshID = m;
        shaderID = s;
        type = RenderType;
    }
};



class Entity {
private:
    std::map<ComponentType, Component*> components;
public:
    uint32_t ID; //todo private?
    Entity(uint32_t iD){
        ID = iD;
    }
    ~Entity(){
        for (auto c : components){
            delete c.second;
        }
    }
    void pushComponent(Component* comp){
        components.erase(comp->type);
        components[comp->type] = comp;
    }
    void addComponent(Component* comp){
        assert(!components.contains(comp->type));
        components[comp->type] = comp;
    }
    void popComponent(ComponentType type){
        if (components.contains(type)){
            delete components[type];
            components.erase(type);
        }
    }
    Component* comp(ComponentType type){
        if (components.contains(type)){
            return components[type];
        } else {
            return 0;
        }
    }
};

struct CameraData {
    glm::mat4 view, proj;
    CameraData(glm::mat4 v, glm::mat4 p){
        view = v; proj = p;
    }
};

class Camera {
protected:
    glm::vec3 pos, look, up;
    glm::mat4 view;
    glm::mat4 proj;
public: //TODO: detect & update only when needed
    glm::mat4 updateView(){
        glm::vec3 target = pos + look;
        view = lookAt(pos, target, up);
        return view;
    }
    virtual glm::mat4 updateProj() = 0;
    glm::mat4 View(){return view;}
    glm::mat4 Proj(){return proj;}
    CameraData Data(){return CameraData(view, proj);}
};

class OrthoCamera : public Camera {
    constexpr const static glm::mat2x4 lrbtMat = { glm::vec4(-0.5f, 0.5f, 0, 0),
                                                   glm::vec4(0, 0, -0.5f, 0.5f)};
    float near, far;
    float viewWidth; //in game coords
public:
    OrthoCamera(){
        pos = glm::vec3(0.f, 0.f, 1.f);
        look = glm::vec3(0.f, 0.f, -1.f);
        up = glm::vec3(0.f, 1.f, 0.f);
        near = 0.0001f;
        far = 10000.0f;
        viewWidth = 10;
    }
    OrthoCamera(const OrthoCamera&) = default;
    OrthoCamera(glm::vec3 p, glm::vec3 l, glm::vec3 u, float n, float f, float w){
        pos = p; look = l; up = u; near = n; far = f; viewWidth = w;
    }
    void setViewWidth(float vw){
        viewWidth = vw;
    }
    glm::mat4 updateProj() override {
        glm::vec2 orthoDims = glm::vec2(viewWidth, viewWidth / window.aspect);

        glm::vec4 lrbt = (lrbtMat * orthoDims);

        orthoDims.y = orthoDims.x / window.aspect;
        lrbt = (lrbtMat * orthoDims);
        proj = glm::ortho(lrbt.x, lrbt.y, lrbt.z, lrbt.w, near, far);
        return proj;
    }
};

class Environment {
private:
    OrthoCamera cam;
public:
    std::map<uint32_t, Entity*> entities;
    void init(){
        entities[0] = new Entity(0);
        entities[0]->pushComponent(new RenderComponent(0, 0));
        entities[0]->pushComponent(new TransformComponent(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.f)));
    }
    void update(float dt){
        cam.updateView();
        cam.updateProj();
    }
    CameraData cameraData(){
        return cam.Data();
    }
    
    void destroy(){
        for (auto e : entities){
            delete e.second;
        }
    }
    
};

#endif /* Environment_h */
