//
//  Camera.h
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/27/22.
//
//

#ifndef Camera_h
#define Camera_h
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "../Window.h"

struct CameraData {
    glm::mat4 view, proj;
    CameraData(glm::mat4 v, glm::mat4 p);
};

class Camera {
protected:
    glm::vec3 pos, look, up;
    glm::mat4 view;
    glm::mat4 proj;
public: //TODO: detect & update only when needed
    glm::mat4 updateView();
    virtual glm::mat4 updateProj() = 0;
    glm::mat4 View();
    glm::mat4 Proj();
    CameraData Data();
};

class OrthoCamera : public Camera {
    constexpr const static glm::mat2x4 lrbtMat = { glm::vec4(-0.5f, 0.5f, 0, 0),
                                                   glm::vec4(0, 0, -0.5f, 0.5f)};
    float near, far;
    float viewWidth; //in game coords
public:
    OrthoCamera();
    OrthoCamera(const OrthoCamera&) = default;
    OrthoCamera(glm::vec3 p, glm::vec3 l, glm::vec3 u, float n, float f, float w);
    void setViewWidth(float vw);
    glm::mat4 updateProj() override ;
};
#endif /* Camera_h */
