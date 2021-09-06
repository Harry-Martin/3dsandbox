#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct
{
    double lastTime;
    double startTime;
    double dt;
} Time;

typedef struct
{
    GLFWwindow* id;
    int width;
    int height;
    Time time;
} Window;

Window* create_window();
bool window_should_close(Window* window);
void update_window(Window* window);
void free_window(Window* window);

#endif /* WINDOW_H */
