#include <pch.h>
#include "L_MoveWest.h"
#include "Agent/BehaviorAgent.h"

void L_MoveWest::on_enter()
{
	BehaviorNode::on_leaf_enter();
	targetPoint = agent->get_position();
	const auto& agbb = agent->get_blackboard();
	Speed = agbb.get_value<float>("Speed");
}

void L_MoveWest::on_update(float dt)
{


	if (targetPoint.z - 1.f < 0) {
		on_failure();
	}

	else {
		targetPoint = Vec3{ targetPoint.x,targetPoint.y,targetPoint.z -= Speed };
		const auto result = agent->move_toward_point(targetPoint, dt);

		if (terrain->is_valid_grid_position(terrain->get_grid_position(targetPoint)))
			terrain->set_color(terrain->get_grid_position(targetPoint), Color{ 0,1,0 });

		on_success();
	}


	display_leaf_text();
}