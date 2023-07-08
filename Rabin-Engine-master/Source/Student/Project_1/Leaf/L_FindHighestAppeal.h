#pragma once
#include "BehaviorNode.h"

class L_FindHighestAppeal : public BaseNode<L_FindHighestAppeal>
{

protected:
    virtual void on_enter() override;

private:
    float radius = 5.f;
    int highestAppeal = 0;
};