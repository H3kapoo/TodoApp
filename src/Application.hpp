#pragma once

#include <hkui/renderHelpers/RenderHelper.hpp>
#include <hkui/shaderHelpers/ShaderHelper.hpp>
#include <hkui/stateHelpers/WindowState.hpp>
#include <hkui/treeHelpers/ConcreteNode.hpp>
#include <hkui/treeHelpers/TextNode.hpp>

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
    void onButtonAction(int button, int action, int);
    void onMouseMoveAction(double xPos, double yPos);

    bool gTerminated{false};

private:
    void setTitle(const std::string& title);
    void setSimpleNodeWithColor(treeHelpers::ConcreteNode& node, const std::string colorSHex);

    std::string gBasicVert{"src/assets/shaders/baseV.glsl"};
    std::string gBasicFrag{"src/assets/shaders/baseF.glsl"};

    std::string gTextVert{"src/assets/shaders/textV.glsl"};
    std::string gTextFrag{"src/assets/shaders/textF.glsl"};

    std::string gLinGradVert{"src/assets/shaders/linGradV.glsl"};
    std::string gLinGradFrag{"src/assets/shaders/linGradF.glsl"};
    /* Basic mesh */
    treeHelpers::ConcreteNode gRootNode{gBasicVert, gBasicFrag};
    treeHelpers::ConcreteNode gLeftNode{gBasicVert, gBasicFrag};
    treeHelpers::ConcreteNode gRightNode{gBasicVert, gBasicFrag};
    treeHelpers::ConcreteNode gVSepNode{gBasicVert, gBasicFrag};
    treeHelpers::TextNode gOngoingTextNode{gTextVert, gTextFrag, gLinGradVert, gLinGradFrag};
    treeHelpers::TextNode gDoneTextNode{gTextVert, gTextFrag, gLinGradVert, gLinGradFrag};

    stateHelpers::WindowState gWindowState;

    bool gReload{false};

    GLFWwindow* gWindowHandle{nullptr};
    shaderHelpers::ShaderHelper& gShInstance;
    renderHelpers::RenderHelper& gRenderInstance;
};
} // namespace todo