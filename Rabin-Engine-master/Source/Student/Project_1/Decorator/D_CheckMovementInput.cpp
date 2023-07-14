#include <pch.h>
#include "D_CheckMovementInput.h"

void D_CheckMovementInput::on_enter()
{
	BehaviorNode::on_enter();
	Wbtn = InputHandler::get_current_state(KBKeys::W);
	Abtn = InputHandler::get_current_state(KBKeys::A);
	Sbtn = InputHandler::get_current_state(KBKeys::S);
	Dbtn = InputHandler::get_current_state(KBKeys::D);
}

void D_CheckMovementInput::on_update(float dt)
{

	auto& agbb = agent->get_blackboard();
	if (Wbtn == InputHandler::InputState::PRESSED) {
		agbb.set_value<int>("KeyPressed", (int)DirEnum::Dir_UP);
		movementflag = true;
	}

	else if (Abtn == InputHandler::InputState::PRESSED) {
		agbb.set_value<int>("KeyPressed", (int)DirEnum::Dir_LEFT);
		movementflag = true;
	}

	else if (Sbtn == InputHandler::InputState::PRESSED) {
		agbb.set_value<int>("KeyPressed", (int)DirEnum::Dir_DOWN);
		movementflag = true;
	}

	else if (Dbtn == InputHandler::InputState::PRESSED) {
		agbb.set_value<int>("KeyPressed", (int)DirEnum::Dir_RIGHT);
		movementflag = true;
	}
	else {
		agbb.set_value<int>("KeyPressed", (int)DirEnum::No_Dir);
	}

	BehaviorNode* child = children.front();

	child->tick(dt);

	if (child->succeeded() == true && movementflag == true)
	{
		on_success();
	}

	else if (child->failed() == true || movementflag == false) {
		on_failure();
	}

	display_leaf_text();

}