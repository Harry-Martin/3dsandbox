#include <stdio.h>
#include <GL/glew.h>

#include "window.h"


int main()
{

    Window* window = create_window(1920, 1080, "Test");

    glClearColor(0.4f, 0.6f, 0.35f, 1.0f);

    while (!window_should_close(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        printf("dt: %lf\n", window->time.dt);

        update_window(window);
    }

    destroy_window(window);

    return 0;
}
