#pragma once
#include "BehaviorNode.h"

class L_Dead : public BaseNode<L_Dead>
{
public:
    L_Dead();

protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
