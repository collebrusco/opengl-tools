//
//  Window.h
//  openGL_tools
//
//  Created by Frank Collebrusco on 12/15/22.
//  Window Obj and global instance
//  Adapted from jdh MC clone https://github.com/jdah/minecraft-weekend/blob/master/src/gfx/window.c

#ifndef Window_h
#define Window_h

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
#include <iostream>
#include <vector>

struct Button {
    bool down, last, lastTick, pressed, pressedTick, released;
};

struct Mouse {
    Button buttons[GLFW_MOUSE_BUTTON_LAST];
    glm::vec2 position, delta, scrollDelta, scrollDeltaLast;
};

struct Keyboard {
    Button keys[GLFW_KEY_LAST];
};

class Window {
private:
    void buttonArrayUpdate(size_t n, Button *butts);
public:
    GLFWwindow *handle;
    glm::ivec2 frame;
    float aspect;
    Mouse mouse;
    Keyboard keyboard;
    
    Window(const char*);
    Window(Window const&)            = delete;
    void operator = (Window const&)  = delete;
    
    void update();
    void setMouseGrabbed(bool);
    bool getMouseGrabbed();
    void setMousePos(glm::vec2);
};

extern Window window;


#endif /* Window_h */
