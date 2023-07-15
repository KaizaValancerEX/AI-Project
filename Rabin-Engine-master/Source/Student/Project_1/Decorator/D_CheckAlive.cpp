#include <pch.h>
#include "D_CheckAlive.h"

void D_CheckAlive::on_enter()
{
	agent->set_color({ 0,0,0 });
	BehaviorNode::on_enter();
}

void D_CheckAlive::on_update(float dt)
{

	if (agent->get_DOA() == true) {
		on_failure();
	}

	else if (agent->get_DOA() == false) {
		BehaviorNode* child = children.front();

		child->tick(dt);

		if (child->succeeded() == true)
		{
			on_success();
		}

		else if (child->failed() == true) {
			on_failure();
		}

	}






	display_leaf_text();

}