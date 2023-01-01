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
#include "Camera.h"
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
        type = TransformType;
        pos = glm::vec3(0.f);
        rotation = glm::vec3(0.f);
        scale = glm::vec3(1.f);
    }
    TransformComponent(glm::vec3 p){
        type = TransformType;
        pos = p;
        rotation = glm::vec3(0.f);
        scale = glm::vec3(1.f);
    }
    TransformComponent(glm::vec3 p, glm::vec3 r){
        type = TransformType;
        pos = p;
        rotation = r;
        scale = glm::vec3(1.f);
    }
    TransformComponent(glm::vec3 p, glm::vec3 r, glm::vec3 s){
        type = TransformType;
        pos = p;
        rotation = r;
        scale = s;
    }
};

struct RenderComponent : public Component {
public:
    uint32_t meshID;
    uint32_t shaderID;
    RenderComponent(){
        type = RenderType; meshID = shaderID = 0;
    }
    RenderComponent(uint32_t m, uint32_t s){
        meshID = m;
        shaderID = s;
        type = RenderType;
    }
};

class Entity {
private:
    std::map<ComponentType, Component*> components;
public: //protected:
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
    bool hasComp(ComponentType type){
        return components.contains(type);
    }
    template <typename T>
    T& comp(){
        ComponentType type;
        T dummy;            // I dont love this solution, calling constructor to get ctype map key TODO: improve
        type = dummy.type;
        assert(this->hasComp(type));
        return *((T*)components[type]);
    }
public:
    uint32_t ID; //todo private?
    Entity(uint32_t iD){
        ID = iD;
    }
    ~Entity(){
        for (auto c : components){
            if (c.second) delete c.second;
        }
    }
};

class Environment {
private:
    void destroy(){
        delete cam;
        for (auto e : entities){
            delete e.second;
        }
    }
protected:
    uint32_t findEmptyID(){
        uint32_t i = 0;
        while (entities.contains(i)){
            i++;
        }
        return i;
    }
public:
    Camera* cam;
    std::map<uint32_t, Entity*> entities;
    ~Environment(){
        this->destroy();
    }
    Environment(){
        cam = new PerspectiveCamera;
        cam->setMouseControl(true);
    }
    void init(){
//        entities[0] = new Entity(0);
//        entities[0]->pushComponent(new RenderComponent(2, 0));
//        entities[0]->pushComponent(new TransformComponent(glm::vec3(0.0, 0.0, -0.5), glm::vec3(0.0, 0.0, 0.f)));
    }
    Entity& addEntity(){
        uint32_t ID = this->findEmptyID();
        Entity* newEntity = new Entity(ID);
        entities.insert({ID, newEntity});
        return *newEntity;
    }
    Entity& addEntity(Entity* ent){
        ent->ID = this->findEmptyID();
        entities.insert({ent->ID, ent});
        return *ent;
    }
    bool removeEntity(uint32_t ID){
        if (entities.contains(ID)){
            delete entities[ID];
            entities.erase(ID);
            return true;
        } else {
            return false;
        }
    }
    void update(float dt){
        cam->update();
    }
    CameraData cameraData() const { // could make this return data of one of num of cameras if needed
        return cam->Data();
    }
};

#endif /* Environment_h */
