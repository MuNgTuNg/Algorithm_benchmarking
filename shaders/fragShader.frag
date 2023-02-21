#version 330 core

in vec3 color;
in vec3 aPosOut;


out vec4 FragColor;

void main()
{    
  
    // Output to screen
    FragColor = vec4( color,1.0);
}
