#include <pch.h>
#include "L_InitializeBlackBoard.h"

void L_InitializeBlackBoard::on_enter()
{

	agent->set_color(Vec3{ 0,1,0 });
	agent->set_DOA(true);
	agent->set_movement_speed(37.5f);
	auto& bb = agent->get_blackboard();

	//bb.set_value<const char*>("AgentName", "Agent");
	bb.set_value<Agent*>("Target", nullptr);
	//bb.set_value<Agent*>("Ideal Match", nullptr);
	bb.set_value<int>("KeyPressed", -1);
	bb.set_value<float>("StepSize", 5.f);
	bb.set_value<int>("LastActiveNode", 10);

	Vec3 trail = { RNG::range<float>(0.0f,1.0f),RNG::range<float>(0.0f,1.0f) ,RNG::range<float>(0.0f,1.0f) };
	bb.set_value<Vec3>("TrailColor", trail);
	bb.set_value<bool>("Alive", true);
	bb.set_value<bool>("Panic", false);


	on_success();

	display_leaf_text();
}