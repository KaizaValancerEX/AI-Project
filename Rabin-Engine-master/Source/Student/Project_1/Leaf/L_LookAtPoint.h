#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_LookAtPoint : public BaseNode<L_LookAtPoint>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    Vec3 Delta;
    float delay;
    float yaw;
};
