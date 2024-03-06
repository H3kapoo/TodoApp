#pragma once

#include "TodoBox.hpp"
#include <hkui/renderHelpers/RenderHelper.hpp>
#include <hkui/treeHelpers/RectNodeABC.hpp>

namespace todo
{
/**
 * @brief Class that contains TodoBoxes as a scrolling view
 *
 */
class TodoScrollArea : public treeHelpers::RectNodeABC
{
public:
    TodoScrollArea();

private:
    IMPL_OF_PARENT(onRenderDone);

    TodoBox gTodoBox;

    renderHelpers::RenderHelper& gRenderInstance;
};
} // namespace todo