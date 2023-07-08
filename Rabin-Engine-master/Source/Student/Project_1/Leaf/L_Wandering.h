#pragma once
#include "BehaviorNode.h"

class L_Wandering : public BaseNode<L_Wandering>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
};