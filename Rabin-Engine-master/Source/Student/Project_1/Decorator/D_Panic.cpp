#include <pch.h>
#include "D_Panic.h"

void D_Panic::on_enter()
{
	agent->set_color({ 0.5f,0.1f,0.9f });

	auto& agbb = agent->get_blackboard();

	for (const auto& t_agent : agents->get_all_agents()) {
		if (t_agent->get_DOA() == false) {
			agbb.set_value<Agent*>("Target", t_agent);
			agbb.set_value<bool>("Panic", true);
			countdown = 5.f;
			break;
		}
	}

	BehaviorNode::on_enter();

}

void D_Panic::on_update(float dt)
{

	auto& agbb = agent->get_blackboard();

	if (agbb.get_value<bool>("Panic") == true) {
		BehaviorNode* child = children.front();
		if (child) {
			child->tick(dt);
			countdown -= dt;

			if (countdown <= 0.f) {
				agbb.set_value("Panic", false);
				agents->destroy_agent(agbb.get_value<Agent*>("Target"));
				agbb.set_value<Agent*>("Target", nullptr);
			}

			if (child->succeeded() == true)
			{
				on_success();
			}

			else if (child->failed() == true || agbb.get_value<bool>("Panic") == false) {
				on_failure();
			}
		}

	}

	else {
		on_failure();
	}


	display_leaf_text();

}