#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW ERROR: %s\n", description);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();

    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Test", NULL, NULL);

    glfwSetKeyCallback(window, glfw_key_callback);

    glfwMakeContextCurrent(window);
    glewInit();

    glfwSwapInterval(1); /* NOTE: acts on current context (context must be valid first) */

    double lastTime = 0;
    double startTime = 0;
    double dt = 0;
    while (!glfwWindowShouldClose(window))
    {

        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = startTime;
        startTime = glfwGetTime();
        dt = startTime - lastTime;
        
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
