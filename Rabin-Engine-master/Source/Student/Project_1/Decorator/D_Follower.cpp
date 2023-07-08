#include <pch.h>
#include "D_Follower.h"

void D_Follower::on_update(float dt)
{

	// repeat the child until 4 successes, stop on any failure
	BehaviorNode* child = children.front();

	child->tick(dt);

	if (child->succeeded() == true && agent->get_AGrole() == Agent_ROLE::FOLLOWER)
	{

		on_success();
	}

	else if (agent->get_AGrole() != Agent_ROLE::FOLLOWER) {
		on_failure();
	}

	else if (child->failed() == true) {
		on_failure();
	}

	display_leaf_text();

}
