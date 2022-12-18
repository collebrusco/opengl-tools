#version 410 core

out vec4 outColor;
in vec2 iUV;
uniform vec3 uColor;
void main(){
    outColor = vec4(uColor,1.f);
}
