#include <stdio.h>
#include <stdlib.h>

#include "shader.h"

static char* read_source(const char* filepath)
{
    char* buffer = NULL;
    unsigned int size;

    FILE* f = fopen(filepath, "r");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        rewind(f);

        buffer = (char*)malloc((size + 1) * sizeof(char));

        fread(buffer, sizeof(char), size, f);
        buffer[size] = '\0';
        fclose(f);
    }
    else
    {
        fprintf(stderr, "SHADER ERROR: Failed to open '%s'\n", filepath);
    }

    return buffer;
}

static int check_shader_error(GLuint id, GLenum type, const char* message)
{
    int success;
    glGetShaderiv(id, type, &success);
    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(id, 512, NULL, log);
        fprintf(stderr,"%s : \n%s\n", message, log);
    }
    
    return success;
}

static int check_program_error(GLuint id, GLenum type, const char* message)
{
    int success;
    glGetProgramiv(id, type, &success);
    if (!success)
    {
        char log[512];
        glGetProgramInfoLog(id, 512, NULL, log);
        fprintf(stderr,"%s : \n%s\n", message, log);
    }
    
    return success;
}

static GLuint compile_shader(GLenum type, const char* src)
{
    GLuint id = glCreateShader(type);

    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    check_shader_error(id, GL_COMPILE_STATUS, "SHADER ERROR: Failed to compile shader");
    return id;
}

Shader* create_shader(GLenum type, const char* filepath)
{
    Shader* shader = NULL;
    char* src = read_source(filepath);
    if (src != NULL)
    {
        GLuint id = compile_shader(type, src);
        free(src);

        shader = malloc(sizeof(Shader));
        shader->id = id;
        shader->type = type;
    }
    else
    {
        fprintf(stderr, "SHADER ERROR: Failed to create shader, empty src string\n");
    }
    return shader;
}

ShaderProgram* create_program(Shader* vs, Shader* fs)
{
    ShaderProgram* program = malloc(sizeof(ShaderProgram));

    program->id = glCreateProgram();
    
    glAttachShader(program->id, vs->id);
    glAttachShader(program->id, fs->id);

    glLinkProgram(program->id);
    check_program_error(program->id, GL_LINK_STATUS, "SHADER ERROR: Failed to link program");

    return program;
}

void free_shader(Shader* shader)
{
    glDeleteShader(shader->id);
    free(shader);
}

void free_program(ShaderProgram* program)
{
    glDeleteProgram(program->id);
    free(program);
}

