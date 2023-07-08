#include <pch.h>
#include "L_InitializeBlackBoard.h"

void L_InitializeBlackBoard::on_enter()
{
	auto& bb = agent->get_blackboard();

	bb.set_value<Agent*>("Target", nullptr);
	bb.set_value<Agent*>("Ideal Match", nullptr);

	on_success();

	display_leaf_text();
}