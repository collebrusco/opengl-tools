//
//  f_transform.cpp
//  opengl-tools
//
//  Created by Frank Collebrusco on 12/24/22.
//
//

#include "f_transform.h"

glm::mat4 genModelMat(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale){//, glm::mat4 *m){
    glm::mat4 m;
    glm::vec3 anchor(0.f);
    m = glm::mat4(1.0);
    m = glm::translate(m, pos);
    m = glm::rotate(m, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    m = glm::rotate(m, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    m = glm::rotate(m, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    m = glm::scale(m, scale);
    m = glm::translate(m, anchor);
    return m;
}
