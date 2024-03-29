#include <stdio.h>

#include "src/Application.hpp"
#include <hkui/inputHelpers/InputHelper.hpp>
#include <hkui/vendor/GL/Glefw.hpp>

int main()
{
    const int32_t windowWidth = 1280;
    const int32_t windowHeight = 720;

    const int32_t minWidth = 800;
    const int32_t minHeight = 600;
    const int32_t maxWidth = 99999;
    const int32_t maxHeight = 99999;

    /* Init glfw */
    if (GLFW_FALSE == glfwInit())
    {
        perror("Something happened while trying to initialize GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create mock window just to succeed initializing glew*/
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "UnSnapshot C++", NULL, NULL);
    if (window == NULL)
    {
        perror("Failed to create glew initializing window\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    // glfwSwapInterval(0); // zero to disable Vsync

    /* Init glew after glfw (we need to have a valid context bound first) */
    if (glewInit() != GLEW_OK)
    {
        perror("GLEW failed to initialize\n");
        return 1;
    }

    /* Quick gpu info */
    printf("GPU Vendor: %s\nGPU Renderer: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));

    glfwSetWindowSizeLimits(window, minWidth, minHeight, maxWidth, maxHeight);

    todo::Application app(window);
    app.setup();

    inputHelpers::InputHelper& inHelper = inputHelpers::InputHelper::get();
    inHelper.observe(window);
    // clang-format off
    inHelper.registerOnKeyAction(std::bind(&todo::Application::onKeyPress, &app,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3,
        std::placeholders::_4));

    inHelper.registerOnWindowResizeAction(std::bind(&todo::Application::onWindowResize, &app,
        std::placeholders::_1,
        std::placeholders::_2));

    inHelper.registerOnMouseButtonAction(std::bind(&todo::Application::onButtonAction, &app,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3));

    inHelper.registerOnMouseMoveAction(std::bind(&todo::Application::onMouseMoveAction, &app,
        std::placeholders::_1,
        std::placeholders::_2));

    // inHelper.registerOnMouseDropAction(std::bind(&Application::onMouseDrop, &app,
    //     std::placeholders::_1,
    //     std::placeholders::_2));
    // clang-format on

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window) && !app.gTerminated)
    {
        // if (app.gTerminated) { return 1; }
        app.loop();
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    /* Free no longer needed init window. User must make sure now there's a context bound
       by him before using any glew/glfw API calls
    */
    glfwDestroyWindow(window);
    glfwTerminate();
}