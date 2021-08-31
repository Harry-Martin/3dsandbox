#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

typedef struct
{
    GLuint id;
} ShaderProgram;

typedef struct
{
    GLuint id;
    GLenum type;
} Shader;

Shader* create_shader(GLenum type, const char* src);
ShaderProgram* create_program(Shader* vs, Shader* fs);
void free_shader(Shader* shader);
void free_program(ShaderProgram* program);

#endif /* SHADER_H */
