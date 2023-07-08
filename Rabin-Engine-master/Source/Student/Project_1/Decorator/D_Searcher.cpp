#include <pch.h>
#include "D_Searcher.h"



void D_Searcher::on_enter()
{
    agent->set_color({ 1,1,0 });
    BehaviorNode::on_enter();

}

void D_Searcher::on_update(float dt)
{

    // repeat the child until 4 successes, stop on any failure
    BehaviorNode* child = children.front();

    child->tick(dt);

    if (child->succeeded() == true && agent->get_AGrole() == Agent_ROLE::SEARCHER)
    {
        on_success();
    }

    else if (agent->get_AGrole() != Agent_ROLE::SEARCHER) {
        on_failure();
    }

    else if (child->failed() == true) {
        on_failure();
    }

    display_leaf_text();

}
