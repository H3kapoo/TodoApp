#include "Application.hpp"

#include <hkui/utils/CommonUtils.hpp>

namespace todo
{

Application::Application(GLFWwindow* windowHandle)
    : gWindowHandle{ windowHandle }
    , gShInstance{ shaderHelpers::ShaderHelper::get() }
    , gRenderInstance{ renderHelpers::RenderHelper::get() }
{}

void Application::setup()
{
    printf("Setup called\n");
    setTitle("TodoApp");

    glfwGetWindowSize(gWindowHandle, &gWindowState.winWidth, &gWindowState.winHeight);

    /* Note: Highest Z renders in front of everything */
    glm::mat4 projMatrix = glm::ortho(0.0f, (float)gWindowState.winWidth, (float)gWindowState.winHeight,
        0.0f, renderHelpers::RenderHelper::MAX_LAYERS, 0.0f);
    gRenderInstance.setProjectionMatrix(projMatrix);

    gRootNode.gMesh.gColor = utils::hexToVec4("#1F323C");
    gRootNode.gStyle.gBorderSize = glm::vec4(4, 4, 4, 4);
    gRootNode.gStyle.gBorderColor = utils::hexToVec4("#349798");

    gTopNode.gMesh.gColor = utils::hexToVec4("#b41818");
    gTopNode.gStyle.gBorderColor = utils::hexToVec4("#349798");
    gTopNode.gStyle.gBorderSize = glm::vec4(4, 4, 4, 4);
    gTopNode.gMesh.gUniKeeper.watch("uInnerColor", &gTopNode.gMesh.gColor);
    gTopNode.gMesh.gUniKeeper.watch("uBorderSize", &gTopNode.gStyle.gBorderSize);

    gLeftNode.gMesh.gColor = utils::hexToVec4("#2818b4");
    gLeftNode.gStyle.gBorderColor = utils::hexToVec4("#349798");
    gLeftNode.gStyle.gBorderSize = glm::vec4(4, 4, 4, 4);
    gLeftNode.gMesh.gUniKeeper.watch("uInnerColor", &gLeftNode.gMesh.gColor);
    gLeftNode.gMesh.gUniKeeper.watch("uBorderSize", &gLeftNode.gStyle.gBorderSize);

    gRightNode.gMesh.gColor = utils::hexToVec4("#2818b4");
    gRightNode.gStyle.gBorderColor = utils::hexToVec4("#349798");
    gRightNode.gStyle.gBorderSize = glm::vec4(4, 4, 4, 4);
    gRightNode.gMesh.gUniKeeper.watch("uInnerColor", &gRightNode.gMesh.gColor);
    gRightNode.gMesh.gUniKeeper.watch("uBorderSize", &gRightNode.gStyle.gBorderSize);

    gRootNode.gMesh.gUniKeeper.watch("uInnerColor", &gRootNode.gMesh.gColor);
    gRootNode.gMesh.gUniKeeper.watch("uBorderColor", &gRootNode.gStyle.gBorderColor);
    gRootNode.gMesh.gUniKeeper.watch("uBorderSize", &gRootNode.gStyle.gBorderSize);

    // printf("ceva\n");
    gRootNode.setStateSource(&gWindowState);
    gRootNode.enableFastTreeSort();

    /* Push Child to root node */
    gRootNode.append(&gTopNode);
    gRootNode.append(&gLeftNode);
    gRootNode.append(&gRightNode);

    gRootNode.updateFastTree();
}

void Application::loop()
{
    // if (gReload == true)
    // {
    //     gRootNode.gStyle.gBorderSize = glm::vec4(0);
    //     gTopNode.gStyle.gBorderSize = glm::vec4(0);
    //     gLeftNode.gStyle.gBorderSize = glm::vec4(0);
    // }
    // else
    // {
    //     gRootNode.gStyle.gBorderSize = glm::vec4(4);
    //     gTopNode.gStyle.gBorderSize = glm::vec4(4);
    //     gLeftNode.gStyle.gBorderSize = glm::vec4(4);
    // }

    auto& rootMesh = gRootNode.gMesh;
    rootMesh.gBox.pos.x = 10;
    rootMesh.gBox.pos.y = 10;
    rootMesh.gBox.scale.x = gWindowState.winWidth - 20;
    rootMesh.gBox.scale.y = gWindowState.winHeight - 20;

    auto& topMesh = gTopNode.gMesh;
    topMesh.gBox.pos.x = rootMesh.gBox.pos.x + 10 + 4;
    topMesh.gBox.pos.y = rootMesh.gBox.pos.y + 10 + 4;
    topMesh.gBox.scale.x = rootMesh.gBox.scale.x - 20 - 8;
    topMesh.gBox.scale.y = rootMesh.gBox.scale.y * 0.25f;

    auto& leftMesh = gLeftNode.gMesh;
    leftMesh.gBox.pos.x = topMesh.gBox.pos.x;
    leftMesh.gBox.pos.y = topMesh.gBox.pos.y + topMesh.gBox.scale.y + 10;
    leftMesh.gBox.scale.x = rootMesh.gBox.scale.x * 0.5f - 10 - 8;
    leftMesh.gBox.scale.y = rootMesh.gBox.scale.y - topMesh.gBox.scale.y - 38;

    auto& rightMesh = gRightNode.gMesh;
    rightMesh.gBox.pos.x = leftMesh.gBox.pos.x + leftMesh.gBox.scale.x + 8;
    rightMesh.gBox.pos.y = topMesh.gBox.pos.y + topMesh.gBox.scale.y + 10;
    rightMesh.gBox.scale.x = rootMesh.gBox.scale.x * 0.5f - 10 - 8;
    rightMesh.gBox.scale.y = rootMesh.gBox.scale.y - topMesh.gBox.scale.y - 38;

    /* Render stuff, order independent (depends only on Z) */
    gRenderInstance.clearScreen();
    gRenderInstance.renderRectNode(gRootNode);
    gRenderInstance.renderRectNode(gTopNode);
    gRenderInstance.renderRectNode(gLeftNode);
    gRenderInstance.renderRectNode(gRightNode);
}

//TODO: Add helper for this inside LIB
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

    glm::mat4 projMatrix = glm::ortho(0.0f, (float)width, (float)height,
        0.0f, renderHelpers::RenderHelper::MAX_LAYERS, 0.0f);
    gRenderInstance.setProjectionMatrix(projMatrix);

    /* glViewport is needed after changing the ortho matrix change or else
       the NDC coordinates will not be mapped correctly to screen coordinates. */
    glViewport(0, 0, width, height);

    // keepRatio();
    gRootNode.emitEvent(inputHelpers::Event::WindowResize);
}

void Application::onKeyPress(int key, int, int action, int)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        gReload = !gReload;
    }
}

}