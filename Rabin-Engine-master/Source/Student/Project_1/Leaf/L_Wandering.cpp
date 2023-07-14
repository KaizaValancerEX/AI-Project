#include <pch.h>
#include "L_Wandering.h"
#include "Agent/BehaviorAgent.h"

void L_Wandering::on_enter()
{
	Vec3 agnt_pos = agent->get_position();
	float radius = RNG::range<float>(8.f, 10.f);
	float x = RNG::range<float>(-5.f, 5.f);
	float z = RNG::range<float>(-5.f, 5.f);

	agent->set_pitch(0);

	Vec3 rnd = Vec3{ x,0,z };

	rnd.Normalize();

	targetPoint = agnt_pos + ((rnd * radius) + agent->get_forward_vector()*10);

	

	if (agent->get_position().x > 100 || agent->get_position().x < 0
		|| agent->get_position().z > 100 || agent->get_position().z < 0)
	{
		targetPoint = RNG::world_position();
	}
	

	BehaviorNode::on_leaf_enter();
}

void L_Wandering::on_update(float dt)
{
	const auto result = agent->move_toward_point({targetPoint.x,0.f,targetPoint.z}, dt);
	


	if (result == true)
	{
		on_success();
	}

	//agent->set_pitch(1.5708);

	display_leaf_text();

}
