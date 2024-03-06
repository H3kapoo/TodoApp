#include "TodoScrollArea.hpp"
#include "hkui/treeHelpers/RectNodeABC.hpp"
#include "hkui/utils/CommonUtils.hpp"

namespace todo
{

TodoScrollArea::TodoScrollArea()
    : treeHelpers::RectNodeABC()
    , gRenderInstance{renderHelpers::RenderHelper::get()}
{
    gMesh.gColor = utils::hexToVec4("#33ff331b");
    gMesh.gUniKeeper.watch("uInnerColor", &gMesh.gColor);
    gMesh.gUniKeeper.watch("uResolution", &gMesh.gBox.scale);
    gMesh.gUniKeeper.defaultVec4("uBorderColor");
    gMesh.gUniKeeper.defaultVec4("uBorderSize");

    append(&gTodoBox);
}

void TodoScrollArea::onRenderDone()
{
    auto& todoMesh = gTodoBox.gMesh;
    todoMesh.gBox.pos.x = 0;
    todoMesh.gBox.pos.y = 0;
    todoMesh.gBox.scale.x = gMesh.gBox.scale.x * 0.5f;
    todoMesh.gBox.scale.y = gMesh.gBox.scale.y * 0.5f;

    utils::print(gMesh.gBox.pos);
    gRenderInstance.renderRectNode(gTodoBox);
}
} // namespace todo