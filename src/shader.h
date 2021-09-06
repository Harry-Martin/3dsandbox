#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <llama/mat.h>
#include <llama/vec.h>

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

void set_uniform_mat4(ShaderProgram* shader, const char* name, llmat m);
void set_uniform_vec4(ShaderProgram* shader, const char* name, llvec m);
void set_uniform_float(ShaderProgram* shader, const char* name, float* f);

#endif /* SHADER_H */
