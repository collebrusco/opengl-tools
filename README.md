# opengl-tools
General OpenGL graphics & input abstractions I've created & use in OpenGL projects. I'll end up with some engine code in here as well. The idea is for this to be a general set of tools for graphics, engine, & input that I'll clone for various projects.

So far, this template includes:
## Window.cpp
* Global, single instance window object that handles all input
* Contains Mouse and Keyboard objects with information about input
* Call window.update() every frame, this updates press & release data
* Current input information is acquired with callbacks
* This is adapted from jdh, link to that in the h & cpp files. That dude is brilliant
## Shader.cpp
* Object representing Shader program on GPU
* Construct with vertex and fragment shader filenames or call .compileAndLink(vertFileName, fragFileName)
* Filenames are handled as so: "Shaders/" + filename + ".glsl"; Change this if you want a different scheme
* bind with bind(), upload uniforms with one of the many uniform upload methods
