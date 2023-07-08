#include <pch.h>
#include "L_CheckForEventTrigger.h"
#include "../Agent/BehaviorAgent.h"

void L_CheckForEventTrigger::on_update(float dt)
{
    const auto KB_E = InputHandler::get_current_state(KBKeys::E);

    if (KB_E == InputHandler::InputState::PRESSED) {

        auto HitList = agents->get_all_agents();

        deadagent = HitList[RNG::AgentRNG(static_cast<int>(HitList.size() - 1))];

        if (deadagent->get_pitch() != 1.5708) {
            deadagent->set_pitch(1.5708);
            deadagent->set_color(Vec3(0.f, 0.f, 0.f));
            on_success();
        }

        else {
            on_failure();
        }

        
        
        
    }
    
    else
    {
        on_failure();
    }

    display_leaf_text();
}