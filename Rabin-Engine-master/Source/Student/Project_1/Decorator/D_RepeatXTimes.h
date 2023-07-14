#pragma once
#include "BehaviorNode.h"

class D_RepeatXTimes : public BaseNode<D_RepeatXTimes>
{
public:
    D_RepeatXTimes();

protected:
    unsigned counter;
    int Random_Cap;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};