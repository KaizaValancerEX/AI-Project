#include <pch.h>

#include "D_Initialize.h"
#include "D_Follower.h"

void D_Initialize::on_enter()
{
	BehaviorNode* child = children.front();

	if (!init_flag) {
		child->tick(0);
		init_flag = true;
		on_success();
	}

	else {
		on_failure();
	}

	display_leaf_text();

}
