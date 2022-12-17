#version 410 core

out vec4 outColor;
in vec2 iUV;
float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}
void main(){
    outColor = vec4(255.0f, 0.f, 0.f, 1.f);
}
