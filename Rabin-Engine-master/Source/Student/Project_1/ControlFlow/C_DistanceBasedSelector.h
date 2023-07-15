#pragma once
#include "BehaviorNode.h"

class C_DistanceBasedSelector : public BaseNode<C_DistanceBasedSelector>
{
public:
    C_DistanceBasedSelector();

protected:
    size_t currentIndex;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;

    float DistFromCommotion;
};