#include <pch.h>
#include "L_LookAtPoint.h"
#include "Agent/BehaviorAgent.h"

void L_LookAtPoint::on_enter()
{
	auto& agbb = agent->get_blackboard();
	targetPoint = agbb.get_value<Agent*>("Target")->get_position();

	Delta = targetPoint - agent->get_position();
	yaw = std::atan2(Delta.x, Delta.z);
	delay = 10.f;
	agent->set_yaw(yaw);
	BehaviorNode::on_leaf_enter();
;

}

void L_LookAtPoint::on_update(float dt)
{
	//auto& agbb = agent->get_blackboard();
	//delay = -dt;
	//if (delay < 0.0f) {

	on_success();

	//}

	//else {
		//is_running();
	//}

	display_leaf_text();
}