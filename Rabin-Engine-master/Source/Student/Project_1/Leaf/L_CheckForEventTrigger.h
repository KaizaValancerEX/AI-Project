#pragma once
#include "BehaviorNode.h"

class L_CheckForEventTrigger : public BaseNode<L_CheckForEventTrigger>
{
protected:
    virtual void on_update(float dt);

private:
    Agent* deadagent = nullptr;
};
