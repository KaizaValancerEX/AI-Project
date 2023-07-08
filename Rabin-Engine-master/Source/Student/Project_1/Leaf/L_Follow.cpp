#include <pch.h>
#include "L_Follow.h"
#include "Agent/BehaviorAgent.h"

void L_Follow::on_enter()
{

		const auto& bb = agent->get_blackboard();

		agent->set_color({ 0,0,1 });
		agent->set_pitch(0);

		targetAgent = bb.get_value<Agent*>("Target");
		if (!targetAgent) {
			on_failure();
		}

		if (targetAgent) {
			if ((targetAgent->get_position() - agent->get_position()).Length() > 15.f) {
				agent->set_movement_speed(15.f);
			}

			else {
				agent->set_movement_speed(10.f);
			}
		}

		if (targetAgent) {
			if (targetAgent->get_AGrole() == Agent_ROLE::LEADER) {
				if (targetAgent->get_idealMatch() != agent)
					agent->set_AGrole(Agent_ROLE::SEARCHER);
			}
		}

		float radius = RNG::range<float>(0.1f, 10.f);
		float x = RNG::range<float>(-5.f, 5.f);
		float z = RNG::range<float>(-5.f, 5.f);

		Vec3 rnd = Vec3{ x,0,z };

		rnd.Normalize();

		if (targetAgent)
			targetPoint = targetAgent->get_position() - targetAgent->get_forward_vector() * -10 + rnd * radius;

		BehaviorNode::on_leaf_enter();
}

void L_Follow::on_update(float dt)
{

	const auto result = agent->move_toward_point(Vec3(targetPoint.x, 0, targetPoint.z), dt);



	if (result == true)
	{
		on_success();
	}

	//agent->set_pitch(1.5708);

	display_leaf_text();

}
