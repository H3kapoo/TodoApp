#pragma once

#include <hkui/renderHelpers/RenderHelper.hpp>
#include <hkui/shaderHelpers/ShaderHelper.hpp>
#include <hkui/treeHelpers/ConcreteNode.hpp>
#include <hkui/stateHelpers/WindowState.hpp>

namespace todo
{
class Application
{
public:
    Application(GLFWwindow* windowHandle);

    void setup();
    void loop();

    void onWindowResize(int width, int height);

private:
    void setTitle(const std::string& title);

    std::string gBasicVert{ "src/assets/shaders/baseV.glsl" };
    std::string gBasicFrag{ "src/assets/shaders/baseF.glsl" };

    /* Basic mesh */
    treeHelpers::ConcreteNode gRootNode{ gBasicVert, gBasicFrag };

    stateHelpers::WindowState gWindowState;

    GLFWwindow* gWindowHandle{ nullptr };
    shaderHelpers::ShaderHelper& gShInstance;
    renderHelpers::RenderHelper& gRenderInstance;
};
}