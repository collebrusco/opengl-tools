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

class Camera {
    
};

class orthoCamera {
    
};

class Environment {
private:
    orthoCamera cam;
public:
    
};

#endif /* Environment_h */
