#include <GL/glew.h>
#include <math.h>
#include <llama/util.h>
#include <llama/vec.h>
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
        0.5f,
        0.0f,
        -0.5f,
        -0.5f,
        0.0f,
        0.5f,
        -0.5f,
        0.0f,
        0.5f,
        -0.5f,
        0.0f,
        -0.5f,
        0.5f,
        0.0f,
        0.5f,
        0.5f,
        0.0f,
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (6 * 3) * sizeof(float), pos, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(0.4f, 0.6f, 0.35f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*llmat proj = ll_persp(45.0f, 1.0, 1.0f, 100.0f);*/
    llmat proj = ll_ortho(-10, 10, -10, 10, -10, 10);
    glUseProgram(basic->id);
    GLuint proj_loc = glGetUniformLocation(basic->id, "proj");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, ll_matToFloats(proj));

    llvec u_color = ll_vec(0.0f, 0.0f, 1.0f, 1.0f);
    glUseProgram(basic->id);
    GLint color_loc = glGetUniformLocation(basic->id, "u_color");
    glUniform4fv(color_loc, 1, ll_vecToFloats(u_color));

    float r = 0;
    float s = 0;
    while (!window_should_close(window))
    {
        r += 1.0f * window->time.dt;
        s = 1 + fabs(sinf(fmod(r, 2 * PI)));
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(basic->id);

    llmat model = ll_identityMat(4);
    llmat model_scale = ll_scaleMat(2.0f, 2.0f, 2.0f);
    llmat model_rotation = ll_transposeMat(ll_rotationMat(r, 0.0f, 0.0f)); /* NOTE: rotationMatrix needs to be fixed in llama, It is in column major, llama should use row major :') <-- tears of happiness because this shit took me way too long to figure out... */
    llmat model_trans = ll_translationMat(0.0f,0.0f, -1.0f -r);
    model = ll_dotMat(model, model_trans);
    model = ll_dotMat(model, model_rotation);
    model = ll_dotMat(model, model_scale);
    


    glUseProgram(basic->id);
    GLint model_loc = glGetUniformLocation(basic->id, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, ll_matToFloats(model));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /*printf("dt: %lf\n", window->time.dt);*/

        update_window(window);
    }

    free_window(window);
    free_program(basic);

    return 0;
}
