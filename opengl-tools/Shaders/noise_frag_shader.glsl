#version 410 core

out vec4 outColor;
in vec2 iUV;
float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}
void main(){
//    outColor = vec4(iUV.xy, 0.f, 1.f); // classic red/yellow/green UV coord test
    int noise_scale = 8;
//    outColor = vec4(rand(vec2(float(int(iUV.x*1024)/noise_scale), float(int(iUV.y*1024)/noise_scale))),
//                    rand(vec2(float(int(iUV.y*1024)/noise_scale), float(int(iUV.x*1024)/noise_scale))),
//                    rand(vec2(rand(vec2(float(int(iUV.x*1024)/noise_scale), float(int(iUV.x*1024)/noise_scale))),
//                              rand(vec2(float(int(iUV.y*1024)/noise_scale), float(int(iUV.y*1024)/noise_scale))))), 1.f); // scaled noise
    outColor = vec4(rand(iUV.xy) - 0.2f, rand(iUV.yx) - 0.2f, rand(vec2(rand(iUV.yy), rand(iUV.xx))) - 0.2f, 1.f);                             // fine noise
}
