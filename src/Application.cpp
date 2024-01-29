#include "Application.hpp"

namespace todo
{

Application::Application(GLFWwindow* windowHandle)
    : gWindowHandle{ windowHandle }
    , gShInstance{ shaderHelpers::ShaderHelper::get() }
    , gRenderInstance{ renderHelpers::RenderHelper::get() }
{}

void Application::setup()
{

}

void Application::loop()
{
    /* Render stuff, order independent (depends only on Z) */
    gRenderInstance.clearScreen();
}
}