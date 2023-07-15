#include <pch.h>
#include "C_DistanceBasedSelector.h"

C_DistanceBasedSelector::C_DistanceBasedSelector() : currentIndex(-1),DistFromCommotion(0)
{}

void C_DistanceBasedSelector::on_enter()
{
	auto& agbb = agent->get_blackboard();

	DistFromCommotion = (agbb.get_value<Agent*>("Target")->get_position() - agent->get_position()).Length();

	if (DistFromCommotion < 40.f) {
		currentIndex = 0;
	}

	else
		currentIndex = 1;

	BehaviorNode::on_enter();
}

void C_DistanceBasedSelector::on_update(float dt)
{

	if (currentIndex == -1)
		on_failure();

	else {
		BehaviorNode* currentNode = children[currentIndex];
		currentNode->tick(dt);

		if (currentNode->succeeded() == true)
		{
			on_success();
		}

		else if (currentNode->failed()) {
			on_failure();
		}
	}
}