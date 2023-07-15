#include <pch.h>
#include "D_Leader.h"

void D_Leader::on_enter()
{
    agent->set_color({ 1,0,0 });
    BehaviorNode::on_enter();

    

}

void D_Leader::on_update(float dt)
{

    BehaviorNode* child = children.front();

    child->tick(dt);

    if (child->succeeded() == true && agent->get_AGrole() == Agent_ROLE::LEADER)
    {
        on_success();
    }

    else if (agent->get_AGrole() != Agent_ROLE::LEADER) {
        on_failure();
    }

    else if (child->failed() == true) {
        on_failure();
    }

    display_leaf_text();

}