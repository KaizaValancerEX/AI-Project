#pragma once
#include "BehaviorNode.h"

class D_Panic : public BaseNode<D_Panic>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
    //virtual void on_exit() override;

    float distFromCommotion;
    float countdown;
};