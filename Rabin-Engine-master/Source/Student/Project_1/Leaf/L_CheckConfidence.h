#pragma once
#include "BehaviorNode.h"

class L_CheckConfidence : public BaseNode<L_CheckConfidence>
{

protected:
    virtual void on_enter() override;

private:
    float radius = 5.f;
    int BestConfidence = 100;
};