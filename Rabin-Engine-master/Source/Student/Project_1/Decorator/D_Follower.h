#pragma once
#include "BehaviorNode.h"

class D_Follower : public BaseNode<D_Follower>
{
protected:
    virtual void on_update(float dt) override;
    //virtual void on_exit() override;
};