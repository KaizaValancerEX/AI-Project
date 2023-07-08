#include <pch.h>
#include "L_CheckConfidence.h"

void L_CheckConfidence::on_enter()
{
	if (agent->get_AGrole() == Agent_ROLE::SEARCHER) {
		auto& bb = agent->get_blackboard();

		for (auto& fAgent : agents->get_all_agents()) {
			if (fAgent->get_targetAgent()) {
				if (agent->get_id() == fAgent->get_targetAgent()->get_id()) {
					if ((agent->get_position() - fAgent->get_position()).Length() < 5.f) {
						BestConfidence = agent->get_Confidence() + fAgent->get_Confidence();
						BestConfidence /= 2;



						if (BestConfidence >= 45 && BestConfidence <= 65) {
							agent->set_idealMatch(fAgent);
							fAgent->set_idealMatch((Agent*)agent);

							if (agent->get_Confidence() > fAgent->get_Confidence()) {
								agent->set_AGrole(Agent_ROLE::LEADER);
								fAgent->set_AGrole(Agent_ROLE::FOLLOWER);
								audioManager->StopMusic(L"Assets\\Audio\\letsgetiton.wav");
								audioManager->PlayMusic(L"Assets\\Audio\\letsgetiton.wav");
							}
							on_success();
						}

						else {
							agent->set_AGrole(Agent_ROLE::SEARCHER);
						}
					}

					else {
						continue;
					}
				}

				else {
					continue;
				}
			}

			else {
				on_failure();
			}
		}
	}

	else if (agent->get_AGrole() == Agent_ROLE::FOLLOWER) {
		on_success();
	}

	else if (agent->get_AGrole() == Agent_ROLE::LEADER) {
		on_success();
	}

	else {
		on_failure();
	}

	display_leaf_text();
}
