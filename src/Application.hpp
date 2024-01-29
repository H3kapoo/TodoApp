#pragma once

#include <hkui/renderHelpers/RenderHelper.hpp>
#include <hkui/shaderHelpers/ShaderHelper.hpp>

namespace todo
{
class Application
{
public:
    Application(GLFWwindow* windowHandle);

    void setup();
    void loop();

private:
    GLFWwindow* gWindowHandle{ nullptr };
    shaderHelpers::ShaderHelper& gShInstance;
    renderHelpers::RenderHelper& gRenderInstance;
};
}