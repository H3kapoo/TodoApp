#include "TodoBox.hpp"
#include "hkui/treeHelpers/RectNodeABC.hpp"
#include "hkui/utils/CommonUtils.hpp"

namespace todo
{

TodoBox::TodoBox()
    : treeHelpers::RectNodeABC()
{
    gMesh.gColor = utils::hexToVec4("#00fd00ff");
    gMesh.gUniKeeper.watch("uInnerColor", &gMesh.gColor);
    gMesh.gUniKeeper.watch("uResolution", &gMesh.gBox.scale);
    gMesh.gUniKeeper.defaultVec4("uBorderColor");
    gMesh.gUniKeeper.defaultVec4("uBorderSize");
}

void TodoBox::onRenderDone()
{
    // utils::print(gMesh.gBox.pos);
}
} // namespace todo