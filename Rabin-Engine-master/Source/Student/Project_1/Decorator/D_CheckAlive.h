#pragma once
#include "BehaviorNode.h"

class D_CheckAlive : public BaseNode<D_CheckAlive>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
    //virtual void on_exit() override;
};