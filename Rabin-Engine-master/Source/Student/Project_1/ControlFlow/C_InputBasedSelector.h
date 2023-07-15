#pragma once
#include "BehaviorNode.h"

class C_InputBasedSelector : public BaseNode<C_InputBasedSelector>
{
public:
    C_InputBasedSelector();

    enum class IBSEnum : short {
        IBSE_NA = -1,

        IBSE_KB_W = 0,
        IBSE_KB_A,
        IBSE_KB_S,
        IBSE_KB_D,
        IBSE_KB_E,

        IBSE_ENUM_COUNT
    }inputSelect;

protected:
    size_t currentIndex;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};