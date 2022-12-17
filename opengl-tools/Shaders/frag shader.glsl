#version 410 core
uniform vec2 uRes;
uniform vec2 uMouse;
uniform sampler2D uTexture;
uniform int uSpritePixW;
uniform int uSpritePixH;
uniform vec2 uSpriteSheetCoords;

out vec4 outColor;
in vec2 iUV;
float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}
void main(){
    vec2 normTexCoords = vec2(0.0);
    normTexCoords.x = ((uSpriteSheetCoords.x * 64) + (iUV.x * uSpritePixW)) / 1024.0;
    normTexCoords.y = 1 - ((uSpriteSheetCoords.y * 64) + (iUV.y * uSpritePixH)) / 1024.0;
    ivec2 pixelPos = ivec2(normTexCoords * 1024);
    vec4 pixelColor = texelFetch(uTexture, pixelPos, 0);
    if (pixelColor.a != 1.0f){
            discard;
        }
    vec4 c = texture(uTexture, normTexCoords);
    outColor = c;
}
