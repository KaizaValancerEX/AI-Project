#include <pch.h>
#include "L_MoveToNearestNPC.h"

void L_MoveToNearestNPC::on_enter()
{
	auto& bb = agent->get_blackboard();

	for (auto& t_agent : agents->get_all_agents()) {
		if (agent == t_agent) continue;

		if ((agent->get_position() - t_agent->get_position()).Length() < nearest) {
			nearest = (agent->get_position() - t_agent->get_position()).Length();
			NearestAgent = t_agent;
		}
	}

	targetPoint = NearestAgent->get_position();

	BehaviorNode::on_leaf_enter();
}

void L_MoveToNearestNPC::on_update(float dt)
{
	const auto result = agent->move_toward_point(targetPoint, dt);



	if (result == true)
	{
		NearestAgent->set_DOA(false);
		on_success();
	}

	//agent->set_pitch(1.5708);

	display_leaf_text();
}