#pragma once

#include "hkui/treeHelpers/Button.hpp"
#include <hkui/treeHelpers/RectNodeABC.hpp>

namespace todo
{
/**
 * @brief Class that contains anything a TodoBox should: Id, Up/Down button, X/O button, todo text itself
 *
 */
class TodoBox : public treeHelpers::RectNodeABC
{
public:
    TodoBox();

private:
    IMPL_OF_PARENT(onRenderDone);

    treeHelpers::Button gCheckButton{"src/assets/shaders/baseV.glsl", "src/assets/shaders/baseF.glsl"};
    // Up/Down button
    // Id
    // X/O button
    // todo text itself
};
} // namespace todo