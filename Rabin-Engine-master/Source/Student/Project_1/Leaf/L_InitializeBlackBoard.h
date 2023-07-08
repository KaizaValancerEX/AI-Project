#pragma once
#include "BehaviorNode.h"

class L_InitializeBlackBoard : public BaseNode<L_InitializeBlackBoard>
{

protected:
    virtual void on_enter() override;

private:
    float radius = 5.f;
    int highestAppeal = 0;
};