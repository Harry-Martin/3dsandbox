#include <GL/glew.h>
#include <llama/util.h>
#include <llama/vec.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "shader.h"
#include "window.h"

int main()
{
    Window* window = create_window(1920, 1080, "Test");

    glEnable(GL_DEBUG_OUTPUT);

    Shader* vs = create_shader(GL_VERTEX_SHADER, "src/basic.vert");
    Shader* fs = create_shader(GL_FRAGMENT_SHADER, "src/basic.frag");
    ShaderProgram* basic = create_program(vs, fs);

    vs = create_shader(GL_VERTEX_SHADER, "src/white.vert");
    fs = create_shader(GL_FRAGMENT_SHADER, "src/white.frag");
    ShaderProgram* white = create_program(vs, fs);

    float pos[] = {
        /* front face */
        -0.5f, 0.5f, 0.5f, /* T L 0*/
        -0.5f, -0.5f, 0.5f, /* B L 1*/
        0.5f, -0.5f, 0.5f, /* B R 2*/

        0.5f, -0.5f, 0.5f, /* B R 2*/
        0.5f, 0.5f, 0.5f, /* T R 3*/
        -0.5f, 0.5f, 0.5f, /* T L 0*/

        /* back face */
        0.5f, -0.5f, -0.5f, /* B R 6*/
        -0.5f, -0.5f, -0.5f, /* B L 5*/
        -0.5f, 0.5f, -0.5f, /* T L 4*/

        -0.5f, 0.5f, -0.5f, /* T L 4*/
        0.5f, 0.5f, -0.5f, /* T R 7*/
        0.5f, -0.5f, -0.5f, /* B R 6*/

        /* left face */
        -0.5f, 0.5f, -0.5f, /* T L 4*/
        -0.5f, -0.5f, -0.5f, /* B L 5*/
        -0.5f, -0.5f, 0.5f, /* B L 1*/

        -0.5f, -0.5f, 0.5f, /* B L 1*/
        -0.5f, 0.5f, 0.5f, /* T L 0*/
        -0.5f, 0.5f, -0.5f, /* T L 4*/

        /* right face */
        0.5f, 0.5f, 0.5f, /* T R 3*/
        0.5f, -0.5f, 0.5f, /* B R 2*/
        0.5f, -0.5f, -0.5f, /* B R 6*/

        0.5f, -0.5f, -0.5f, /* B R 6*/
        0.5f, 0.5f, -0.5f, /* T R 7*/
        0.5f, 0.5f, 0.5f, /* T R 3*/

        /* top face */
        -0.5f, 0.5f, -0.5f, /* T L 4*/
        -0.5f, 0.5f, 0.5f, /* T L 0*/
        0.5f, 0.5f, 0.5f, /* T R 3*/

        0.5f, 0.5f, 0.5f, /* T R 3*/
        0.5f, 0.5f, -0.5f, /* T R 7*/
        -0.5f, 0.5f, -0.5f, /* T L 4*/

        /* bottom face */
        -0.5f, -0.5f, 0.5f, /* B L 1*/
        -0.5f, -0.5f, -0.5f, /* B L 5*/
        0.5f, -0.5f, -0.5f, /* B R 6*/

        0.5f, -0.5f, -0.5f, /* B R 6*/
        0.5f, -0.5f, 0.5f, /* B R 2*/
        -0.5f, -0.5f, 0.5f /* B L 1*/
    };

    int pos_count = sizeof(pos) / sizeof(float);
    unsigned int indices[pos_count];
    for (int i = 0; i < pos_count; i++)
    {
        indices[i] = i;
    }
    float normals[] = {
        /* front */
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        /* back */
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        /* left */
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        /* right */
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        /* top */
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,

        /* bottom */
        0.0f, -1.0f, 1.0f,
        0.0f, -1.0f, 1.0f,
        0.0f, -1.0f, 1.0f,

        0.0f, -1.0f, 1.0f,
        0.0f, -1.0f, 1.0f,
        0.0f, -1.0f, 1.0f
    };

    Model* cube = create_model();
    add_float_buffer(cube, 0, 3, sizeof(pos), pos);
    add_float_buffer(cube, 1, 3, sizeof(normals), normals);
    add_index_buffer(cube, sizeof(indices), indices);
    add_index_buffer(cube, 12 * sizeof(unsigned int), &indices[24]);

    glClearColor(0.4f, 0.6f, 0.35f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    llvec u_color = ll_vec(0.0f, 0.0f, 1.0f, 1.0f);
    set_uniform_vec4(basic, "u_color", u_color);

    float r = 0;
    float s = 0;
    while (!window_should_close(window))
    {
        r += 1.0f * window->time.dt;
        s = 1 + fabs(sinf(fmod(r, 2 * PI)));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        llmat proj = ll_persp(45.0f, (float)window->width / (float)window->height, 1.0f, 100.0f);
        /*llmat proj =ll_ortho(4.0f, (float)window->width / (float)window->height, -10, 10);*/
        set_uniform_mat4(basic, "proj", proj);

        glUseProgram(basic->id);

        float offset = -3.0f;

        llmat model = ll_identityMat(4);
        llmat model_scale = ll_scaleMat(1.0f, 1.0f, 1.0f);
        llmat model_rotation = ll_transposeMat(ll_rotationMat(r / 2.0f, 0.5f, -0.5f * r));
        llmat model_trans = ll_translationMat(0.0f, 0.0f, offset);
        model = ll_dotMat(model_scale, model);
        model = ll_dotMat(model_rotation, model);
        model = ll_dotMat(model_trans, model);
        set_uniform_mat4(basic, "model", model);

        float d = 1.50f;
        llvec light_pos = ll_vec(d * sinf(r), 0.5f + cosf(r * 2.0f)/2.5f, offset/1.5f);
        set_uniform_vec4(basic, "light_pos", light_pos);

        glBindVertexArray(cube->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube->sections[0].ibo);

        llvec u_color = ll_vec(0.0f, 0.0f, 1.0f, 1.0f);
        set_uniform_vec4(basic, "u_color", u_color);

        llvec light_color = ll_vec(1.0f, 1.0f, 1.0f, 1.0f);
        set_uniform_vec4(basic, "light_color", light_color);

        float ambient = 0.3f;
        set_uniform_float(basic, "u_ambient", &ambient);

        float specular = 0.5f;
        set_uniform_float(basic, "u_specular", &ambient);

        float light_radius = 1.2;
        set_uniform_float(basic, "u_light_radius", &light_radius);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, cube->sections[0].index_count, GL_UNSIGNED_INT, 0);

        glUseProgram(white->id);
        llmat lmodel = ll_identityMat(4);
        model_scale = ll_scaleMat(0.2f, 0.2f, 0.2f);
        model_rotation = ll_transposeMat(ll_rotationMat(0.0f, 0.0f, 0.0f));
        lmodel = ll_dotMat(model_scale, lmodel);
        lmodel = ll_dotMat(model_rotation, lmodel);
        lmodel = ll_dotMat(ll_vecTranslationMat(light_pos), lmodel);
        set_uniform_vec4(white, "light_color", light_color);
        set_uniform_mat4(white, "model", lmodel);
        set_uniform_mat4(white, "proj", proj);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, cube->sections[0].index_count, GL_UNSIGNED_INT, 0);

        /*printf("dt: %lf\n", window->time.dt);*/

        update_window(window);
    }

    free_window(window);
    free_program(basic);
    free(cube);

    return 0;
}
