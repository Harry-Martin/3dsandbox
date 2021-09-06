#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

#define MAX_IBO_COUNT 4

typedef struct
{
    GLuint ibo;
    unsigned int index_count;
} ModelSection;

typedef struct
{
    GLuint vao;
    unsigned int section_count;
    ModelSection sections[MAX_IBO_COUNT];

} Model;

Model* create_model();
void add_float_buffer(Model* model, unsigned long attrib_location, unsigned int element_size, unsigned long buffer_size, float data[]);
void add_index_buffer(Model* model, unsigned long buffer_size, unsigned int data[]);
void free_model(Model* model);

#endif /* MODEL_H */
