#include <pch.h>
#include "L_MoveSouth.h"
#include "Agent/BehaviorAgent.h"

void L_MoveSouth::on_enter()
{
	BehaviorNode::on_leaf_enter();
	targetPoint = agent->get_position();
	const auto& agbb = agent->get_blackboard();
	StepSize = agbb.get_value<float>("StepSize");
	trailing = agbb.get_value<Vec3>("TrailColor");

}

void L_MoveSouth::on_update(float dt)
{


	if (targetPoint.x - StepSize < 0) {
		on_failure();
	}

	else {
		targetPoint = Vec3{ targetPoint.x -= StepSize,targetPoint.y,targetPoint.z };
		const auto result = agent->move_toward_point(targetPoint, dt);

		if (terrain->is_valid_grid_position(terrain->get_grid_position(targetPoint)))
			terrain->set_color(terrain->get_grid_position(targetPoint), Color{ trailing.x,trailing.y,trailing.z });

		on_success();
	}

	display_leaf_text();
}