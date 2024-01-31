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

    gRootNode.gMesh.gColor = utils::hexToVec4("#6ebcb4");
    gRootNode.gStyle.gBorderSize = glm::vec4(4, 4, 4, 4);
    gRootNode.gStyle.gBorderColor = utils::hexToVec4("#349798");

    gRootNode.gMesh.gUniKeeper.watch("uInnerColor", &gRootNode.gMesh.gColor);
    gRootNode.gMesh.gUniKeeper.watch("uResolution", &gRootNode.gMesh.gBox.scale);
    gRootNode.gMesh.gUniKeeper.defaultVec4("uBorderColor");
    gRootNode.gMesh.gUniKeeper.defaultVec4("uBorderSize");

    // printf("ceva\n");
    // gRootNode.setStateSource(&gWindowState);
    gRootNode.enableFastTreeSort();
    // gRootNode.updateFastTree();
}

void Application::loop()
{
    auto& rootMesh = gRootNode.gMesh;
    rootMesh.gBox.pos.x = 10;
    rootMesh.gBox.pos.y = 10;
    rootMesh.gBox.scale.x = gWindowState.winWidth - 20;
    rootMesh.gBox.scale.y = gWindowState.winHeight - 20;

    /* Render stuff, order independent (depends only on Z) */
    gRenderInstance.clearScreen();
    gRenderInstance.renderRectNode(gRootNode);
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

}