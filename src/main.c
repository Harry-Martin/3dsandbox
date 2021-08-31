#include <GL/glew.h>
#include <stdio.h>

#include "shader.h"
#include "window.h"

int main()
{
    Window* window = create_window(1920, 1080, "Test");

    glEnable(GL_DEBUG_OUTPUT);
    Shader* vs = create_shader(GL_VERTEX_SHADER, "src/basic.vert");
    Shader* fs = create_shader(GL_FRAGMENT_SHADER, "src/basic.frag");
    ShaderProgram* basic = create_program(vs, fs);

    float pos[] = {
        -0.5f,
        -0.5f,
        0.0f,
        0.5f,
        -0.5f,
        0.0f,
        0.0f,
        0.5f,
        0.0f,
    };
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), pos, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.4f, 0.6f, 0.35f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!window_should_close(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(basic->id);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /*printf("dt: %lf\n", window->time.dt);*/

        update_window(window);
    }

    free_window(window);
    free_program(basic);

    return 0;
}
