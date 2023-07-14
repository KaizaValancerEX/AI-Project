#include <pch.h>
#include "D_RepeatXTimes.h"

D_RepeatXTimes::D_RepeatXTimes() : counter(0)
{}

void D_RepeatXTimes::on_enter()
{
    counter = 0;
    Random_Cap = RNG::range(10, 20);
    BehaviorNode::on_enter();
}

void D_RepeatXTimes::on_update(float dt)
{
    // repeat the child until 4 successes, stop on any failure
    BehaviorNode* child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        ++counter;

        if (counter == Random_Cap)
        {
            on_success();
        }
        else
        {
            child->set_status(NodeStatus::READY);
        }
    }
    else if (child->failed() == true)
    {
        on_failure();
    }
}