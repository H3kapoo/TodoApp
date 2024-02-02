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
    void onKeyPress(int key, int, int action, int);

private:
    void setTitle(const std::string& title);

    std::string gBasicVert{ "src/assets/shaders/baseV.glsl" };
    std::string gBasicFrag{ "src/assets/shaders/baseF.glsl" };

    /* Basic mesh */
    treeHelpers::ConcreteNode gRootNode{ gBasicVert, gBasicFrag };
    treeHelpers::ConcreteNode gTopNode{ gBasicVert, gBasicFrag };
    treeHelpers::ConcreteNode gLeftNode{ gBasicVert, gBasicFrag };
    treeHelpers::ConcreteNode gRightNode{ gBasicVert, gBasicFrag };

    stateHelpers::WindowState gWindowState;

    bool gReload{ false };

    GLFWwindow* gWindowHandle{ nullptr };
    shaderHelpers::ShaderHelper& gShInstance;
    renderHelpers::RenderHelper& gRenderInstance;
};
}