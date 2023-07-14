#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_MoveWest : public BaseNode<L_MoveWest>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    float Speed;
};
