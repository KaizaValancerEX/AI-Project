#include <pch.h>
#include "C_InputBasedSelector.h"

C_InputBasedSelector::C_InputBasedSelector() : currentIndex(0), inputSelect(IBSEnum::IBSE_NA)
{}

void C_InputBasedSelector::on_enter()
{
	const auto agbb = agent->get_blackboard();
	int movementkey = agbb.get_value<int>("KeyPressed");
	switch (movementkey)
	{
	case 0:
		currentIndex = (int)IBSEnum::IBSE_KB_W;
		break;
	case 2:
		currentIndex = (int)IBSEnum::IBSE_KB_A;
		break;
	case 1:
		currentIndex = (int)IBSEnum::IBSE_KB_S;
		break;
	case 3:
		currentIndex = (int)IBSEnum::IBSE_KB_D;
		break;
	case 4:
		currentIndex = (int)IBSEnum::IBSE_KB_E;
		break;
	default:
		currentIndex = (int)IBSEnum::IBSE_NA;
		break;
	}

	BehaviorNode::on_enter();
}

void C_InputBasedSelector::on_update(float dt)
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

		else if(currentNode->failed()) {
			on_failure();
		}
	}
}