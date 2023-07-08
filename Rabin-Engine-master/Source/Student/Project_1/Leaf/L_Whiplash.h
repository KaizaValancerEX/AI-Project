#pragma once
#include "BehaviorNode.h"

class L_Whiplash : public BaseNode<L_Whiplash>
{
protected:
    //virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float pitch = 0;
    float speed = 5;
};
