#include <stdlib.h>

#include "model.h"

Model* create_model()
{
    Model* model = malloc(sizeof(Model));
    glGenVertexArrays(1, &model->vao);
    model->section_count = 0;

    return model;
}

void add_float_buffer(Model* model, unsigned long attrib_location, unsigned int element_size, unsigned long buffer_size, float data[])
{
    glBindVertexArray(model->vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attrib_location, element_size, GL_FLOAT, GL_FALSE, element_size * sizeof(float), (void*)0);
    glEnableVertexAttribArray(attrib_location);
    glBindVertexArray(0);
}

void add_index_buffer(Model* model, unsigned long buffer_size, unsigned int data[])
{
    glBindVertexArray(model->vao);
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, data, GL_STATIC_DRAW);
    model->sections[model->section_count].ibo = ibo;
    model->sections[model->section_count].index_count = buffer_size / sizeof(unsigned int);
    model->section_count++;
    glBindVertexArray(0);
}

void free_model(Model* model)
{
    free(model);
}
