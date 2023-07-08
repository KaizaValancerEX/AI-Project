#include <pch.h>
#include "L_Whiplash.h"
#include "Agent/BehaviorAgent.h"

//void L_Whiplash::on_enter()
//{
//	
//	auto Rbtn = InputHandler::get_current_state(KBKeys::R);
//
//	if (Rbtn == InputHandler::InputState::PRESSED) {
//		BehaviorNode::on_enter();
//		pitch = agent->get_pitch();
//	}
//
//
//	else {
//		on_failure();
//	}
//	BehaviorNode::on_leaf_enter();
//}

void L_Whiplash::on_update(float dt)
{
	if (pitch < -0.610865f) {
		speed = -speed;
	}

	if (pitch > 0.610865f) {
		speed = -speed;
	}
	pitch += speed * dt;
	agent->set_pitch(pitch);

	on_success();
	
	display_leaf_text();
}
