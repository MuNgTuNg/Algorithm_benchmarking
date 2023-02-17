#include <sDebugging.hpp>

namespace shb{

void log(const char* msg){
  if(DEBUG){
    std::cout<< msg;
  }
}
void log(const std::string& msg){
  if(DEBUG){
    std::cout<< msg;
  }
}
void log(double& msg){
  if(DEBUG){
    std::cout<< msg;
  }
}


GLenum checkError(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

void checkError(GLuint handle, int type){
    int  success;
    

    if(type == SHADER){
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
    }
    if(type == SHADER_PROGRAM){
      glGetProgramiv(handle, GL_LINK_STATUS, &success);
    }

    if(!success)
    {
      if(type == SHADER){
        char infoLog[512];
        glGetShaderInfoLog(handle, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
      }

      if(type == SHADER_PROGRAM){
        char infoLog[512];
        glGetProgramInfoLog(handle, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
      }

        
      
    }

}


}//namespace shb