#pragma once
#include "BehaviorNode.h"

class L_MoveToNearestNPC : public BaseNode<L_MoveToNearestNPC>
{

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float radius = 5.f;
    float nearest = 100.f;
    Agent* NearestAgent = nullptr;
    Vec3 targetPoint{};
};
