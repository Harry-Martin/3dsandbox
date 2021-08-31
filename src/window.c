#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "window.h"

void window_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW ERROR: %s\n", description);
}

void window_key_callback(GLFWwindow* id, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(id, GLFW_TRUE);
    }
}

void window_framebuffer_size_callback(GLFWwindow* id, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window* create_window(int width, int height)
{
    glfwInit();

    glfwSetErrorCallback(window_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* id = glfwCreateWindow(width, height, "Test", NULL, NULL);

    glfwSetKeyCallback(id, window_key_callback);

    glfwMakeContextCurrent(id);
    glewInit();

    glfwSwapInterval(1); /* NOTE: acts on current context (context must be valid first) */

    Window* window = malloc(sizeof(Window));
    window->id = id;
    window->width = width;
    window->height = height;
    window->time = (Time) {
        .startTime = 0,
        .lastTime = 0,
        .dt = 0,
    };

    return window;
}

bool window_should_close(Window* window)
{
    return glfwWindowShouldClose(window->id);
}

void update_window(Window* window)
{
    glfwSwapBuffers(window->id);
    glfwPollEvents();

    window->time.lastTime = window->time.startTime;
    window->time.startTime = glfwGetTime();
    window->time.dt = window->time.startTime - window->time.lastTime;
}

void free_window(Window* window)
{
    glfwDestroyWindow(window->id);
    glfwTerminate();
    free(window);
}
