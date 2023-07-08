#pragma once
#include "BehaviorNode.h"

class L_Follow : public BaseNode<L_Follow>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Agent* targetAgent;
};