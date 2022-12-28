//
//  Camera.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/27/22.
//
//

#include "Camera.h"
CameraData::CameraData(glm::mat4 v, glm::mat4 p){
    view = v; proj = p;
}

glm::mat4 Camera::updateView(){
    glm::vec3 target = pos + look;
    view = lookAt(pos, target, up);
    return view;
}
glm::mat4 Camera::View(){return view;}
glm::mat4 Camera::Proj(){return proj;}
CameraData Camera::Data(){return CameraData(view, proj);}

//********************************ORTHO********************************
OrthoCamera::OrthoCamera(){
    pos = glm::vec3(0.f, 0.f, 1.f);
    look = glm::vec3(0.f, 0.f, -1.f);
    up = glm::vec3(0.f, 1.f, 0.f);
    near = 0.0001f;
    far = 10000.0f;
    viewWidth = 10;
}
OrthoCamera::OrthoCamera(glm::vec3 p, glm::vec3 l, glm::vec3 u, float n, float f, float w){
        pos = p; look = l; up = u; near = n; far = f; viewWidth = w;
    }
void OrthoCamera::setViewWidth(float vw){
    viewWidth = vw;
}
glm::mat4 OrthoCamera::updateProj()  {
    glm::vec2 orthoDims = glm::vec2(viewWidth, viewWidth / window.aspect);

    glm::vec4 lrbt = (lrbtMat * orthoDims);

    orthoDims.y = orthoDims.x / window.aspect;
    lrbt = (lrbtMat * orthoDims);
    proj = glm::ortho(lrbt.x, lrbt.y, lrbt.z, lrbt.w, near, far);
    return proj;
}
