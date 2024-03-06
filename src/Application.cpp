#include "Application.hpp"
#include "hkui/treeHelpers/TextNode.hpp"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <hkui/utils/CommonUtils.hpp>

namespace todo
{

Application::Application(GLFWwindow* windowHandle)
    : gWindowHandle{windowHandle}
    , gShInstance{shaderHelpers::ShaderHelper::get()}
    , gRenderInstance{renderHelpers::RenderHelper::get()}
{}

void Application::setSimpleNodeWithColor(treeHelpers::ConcreteNode& node, const std::string colorHex)
{
    node.gMesh.gColor = utils::hexToVec4(colorHex);
    node.gMesh.gUniKeeper.watch("uInnerColor", &node.gMesh.gColor);
    node.gMesh.gUniKeeper.watch("uResolution", &node.gMesh.gBox.scale);
    node.gMesh.gUniKeeper.defaultVec4("uBorderColor");
    node.gMesh.gUniKeeper.defaultVec4("uBorderSize");
}

void Application::setup()
{
    printf("Setup called\n");
    setTitle("TodoApp");

    glfwGetWindowSize(gWindowHandle, &gWindowState.winWidth, &gWindowState.winHeight);

    /* Note: Highest Z renders in front of everything */
    glm::mat4 projMatrix = glm::ortho(0.0f, (float)gWindowState.winWidth, (float)gWindowState.winHeight, 0.0f,
        renderHelpers::RenderHelper::MAX_LAYERS, 0.0f);
    gRenderInstance.setProjectionMatrix(projMatrix);

    setSimpleNodeWithColor(gRootNode, "#1F323C");
    setSimpleNodeWithColor(gVSepNode, "#1F3A48");
    setSimpleNodeWithColor(gLeftNode, "#1F3A4800");
    setSimpleNodeWithColor(gRightNode, "#1F3A4800");

    gRootNode.setStateSource(&gWindowState);

    /* Push Child to root node */
    gRootNode.append(&gVSepNode);
    gRootNode.append(&gLeftNode);
    gRootNode.append(&gRightNode);

    gLeftNode.append(&gOngoingTextNode);
    gRightNode.append(&gDoneTextNode);
    gRightNode.append(&gTodoBox);

    gRootNode.enableFastTreeSort();
    gRootNode.updateFastTree();

    gOngoingTextNode.setFont("src/assets/fonts/cmr10.ttf", 32);
    gOngoingTextNode.setText("Ongoing");
    gOngoingTextNode.alignTextToHorizontal(treeHelpers::TextNode::Direction::PreCenter);
    gOngoingTextNode.setTextHorizontalPadding(20);
    gOngoingTextNode.gStyle.gGradColor1 = utils::hexToVec4("#132128");
    gOngoingTextNode.gStyle.gGradColor2 = utils::hexToVec4("#1F323C");
    gOngoingTextNode.gMesh.gUniKeeper.watch("uColStart", &gOngoingTextNode.gStyle.gGradColor1);
    gOngoingTextNode.gMesh.gUniKeeper.watch("uColEnd", &gOngoingTextNode.gStyle.gGradColor2);

    gDoneTextNode.setFont("src/assets/fonts/cmr10.ttf", 32);
    gDoneTextNode.setText("Done");
    gDoneTextNode.alignTextToHorizontal(treeHelpers::TextNode::Direction::PostCenter);
    gDoneTextNode.setTextHorizontalPadding(20);
    gDoneTextNode.gStyle.gGradColor1 = utils::hexToVec4("#1F323C");
    gDoneTextNode.gStyle.gGradColor2 = utils::hexToVec4("#132128");
    gDoneTextNode.gMesh.gUniKeeper.watch("uColStart", &gDoneTextNode.gStyle.gGradColor1);
    gDoneTextNode.gMesh.gUniKeeper.watch("uColEnd", &gDoneTextNode.gStyle.gGradColor2);
}

void Application::loop()
{
    const int32_t vSepScale = 10;
    const int32_t emptySpaceX = 10 + vSepScale + 10;

    auto& rootMesh = gRootNode.gMesh;
    rootMesh.gBox.pos.x = 0;
    rootMesh.gBox.pos.y = 0;
    rootMesh.gBox.scale.x = gWindowState.winWidth;
    rootMesh.gBox.scale.y = gWindowState.winHeight;

    auto& leftMesh = gLeftNode.gMesh;
    leftMesh.gBox.pos.x = rootMesh.gBox.pos.x;
    leftMesh.gBox.pos.y = rootMesh.gBox.pos.y;
    leftMesh.gBox.scale.x = rootMesh.gBox.scale.x * 0.5f - emptySpaceX * 0.5f;
    leftMesh.gBox.scale.y = rootMesh.gBox.scale.y;

    auto& vSepMesh = gVSepNode.gMesh;
    vSepMesh.gBox.pos.x = (leftMesh.gBox.pos.x + leftMesh.gBox.scale.x) + 10;
    vSepMesh.gBox.pos.y = rootMesh.gBox.pos.y + 10;
    vSepMesh.gBox.scale.x = vSepScale;
    vSepMesh.gBox.scale.y = rootMesh.gBox.scale.y - 20;

    auto& rightMesh = gRightNode.gMesh;
    rightMesh.gBox.pos.x = (vSepMesh.gBox.pos.x + vSepMesh.gBox.scale.x) + 10;
    rightMesh.gBox.pos.y = rootMesh.gBox.pos.y;
    rightMesh.gBox.scale.x = rootMesh.gBox.scale.x * 0.5f - emptySpaceX * 0.5f;
    rightMesh.gBox.scale.y = rootMesh.gBox.scale.y;

    auto& ongoingTextMesh = gOngoingTextNode.gMesh;
    ongoingTextMesh.gBox.pos.x = leftMesh.gBox.pos.x;
    ongoingTextMesh.gBox.pos.y = leftMesh.gBox.pos.y;
    ongoingTextMesh.gBox.scale.x = 300;
    ongoingTextMesh.gBox.scale.y = 64;

    auto& doneTextMesh = gDoneTextNode.gMesh;
    doneTextMesh.gBox.pos.x = (rightMesh.gBox.pos.x + rightMesh.gBox.scale.x) - 300;
    doneTextMesh.gBox.pos.y = rightMesh.gBox.pos.y;
    doneTextMesh.gBox.scale.x = 300;
    doneTextMesh.gBox.scale.y = 64;

    // todo box
    auto& todoMesh = gTodoBox.gMesh;
    todoMesh.gBox.pos.x = rootMesh.gBox.pos.x + 10;
    todoMesh.gBox.pos.y = rootMesh.gBox.pos.y + (ongoingTextMesh.gBox.pos.y + ongoingTextMesh.gBox.scale.y) + 10;
    todoMesh.gBox.scale.x = rootMesh.gBox.scale.x * 0.5f - emptySpaceX * 0.5f - 10;
    todoMesh.gBox.scale.y = rootMesh.gBox.scale.y - ongoingTextMesh.gBox.scale.y - 20;

    /* Render stuff, order independent (depends only on Z) */
    gRenderInstance.clearScreen();
    gRenderInstance.renderRectNode(gRootNode);
    gRenderInstance.renderRectNode(gVSepNode);
    gRenderInstance.renderRectNode(gLeftNode);
    gRenderInstance.renderRectNode(gRightNode);
    gRenderInstance.renderRectNode(gOngoingTextNode);
    gRenderInstance.renderRectNode(gDoneTextNode);

    gRenderInstance.renderRectNode(gTodoBox);
}

// TODO: Add helper for this inside LIB
void Application::setTitle(const std::string& title)
{
    /*This shall be abstracted by the window helpers eventually */
    glfwSetWindowTitle(gWindowHandle, title.c_str());
}

/* -------------- Window event propagation zone --------------- */
void Application::onWindowResize(int width, int height)
{
    gWindowState.winWidth = width;
    gWindowState.winHeight = height;

    glm::mat4 projMatrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f, renderHelpers::RenderHelper::MAX_LAYERS,
        0.0f);
    gRenderInstance.setProjectionMatrix(projMatrix);

    /* glViewport is needed after changing the ortho matrix change or else
       the NDC coordinates will not be mapped correctly to screen coordinates. */
    glViewport(0, 0, width, height);

    // keepRatio();
    gRootNode.emitEvent(inputHelpers::Event::WindowResize);
}

void Application::onKeyPress(int key, int, int action, int)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS) { gReload = !gReload; }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { gTerminated = true; }
}

void Application::onButtonAction(int button, int action, int)
{
    gWindowState.mouseClicked = action == GLFW_PRESS ? true : false;
    gWindowState.button = button; /*Left, Right, Middle, etc */
    gRootNode.emitEvent(inputHelpers::Event::MouseButton);
}

void Application::onMouseMoveAction(double xPos, double yPos)
{
    gWindowState.mouseX = xPos;
    gWindowState.mouseY = yPos;
    gRootNode.emitEvent(inputHelpers::Event::MouseMove);
}
} // namespace todo