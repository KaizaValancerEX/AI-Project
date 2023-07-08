#include <pch.h>
#include "L_FindHighestAppeal.h"

void L_FindHighestAppeal::on_enter()
{
	auto& bb = agent->get_blackboard();


	Agent* tAgent = bb.get_value<Agent*>("Target");
	if (tAgent) {
		highestAppeal = tAgent->get_Appeal();
	}

	

	for (auto& f_agent : agents->get_all_agents()) {
		if (agent == f_agent)
			continue;

		if (agent->get_Appeal() < f_agent->get_Appeal()) {
			if ((agent->get_position() - f_agent->get_position()).Length() < radius) {
				if (f_agent->get_Appeal() > highestAppeal) {
					highestAppeal = f_agent->get_Appeal();
					tAgent = f_agent;
				}
			}
		}
	}

	if (!tAgent) on_success();

	else {
		bb.set_value("Target", tAgent);
		agent->set_targetAgent(tAgent);
		agent->set_AGrole(Agent_ROLE::FOLLOWER);
		on_success();
	}

	display_leaf_text();
}