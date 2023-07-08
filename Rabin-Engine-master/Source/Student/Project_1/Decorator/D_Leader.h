#pragma once
#include "BehaviorNode.h"

class D_Leader : public BaseNode<D_Leader>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
    //virtual void on_exit() override;
};