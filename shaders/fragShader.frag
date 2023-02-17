#version 330 core

in vec3 color;
in vec3 aPosOut;

out vec4 FragColor;


void main()
{    
    vec3 newColor = color;
    if(aPosOut.x < 0.2){
     newColor = vec3(color.x,color.y,0.4);
    }
    if(aPosOut.y < 0.1){
     newColor = vec3(color.x,0.02,color.z);
    }


    FragColor = vec4(newColor,1.0);
}