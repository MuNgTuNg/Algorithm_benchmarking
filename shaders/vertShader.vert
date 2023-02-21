#version 330 core

layout ( location = 0 ) in vec3 aPos;
layout ( location = 1 ) in vec3 aColor;

uniform mat4 location;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 scale;

uniform float iTime;


out vec3 color;
out vec3 aPosOut;
out float time;

void main(){
    
   
    aPosOut = aPos;
    time = iTime;
    
    gl_Position = model * projection * location * scale * vec4(aPos.x,aPos.y,aPos.z,1.0);
    color = aColor;
}