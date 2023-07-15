#include <pch.h>
#include "L_Dead.h"

L_Dead::L_Dead() : timer(0.0f)
{}

void L_Dead::on_enter()
{
    timer = RNG::range(1.0f, 2.0f);

    BehaviorNode::on_leaf_enter();
}

void L_Dead::on_update(float dt)
{
    timer -= dt;

    agent->set_pitch(PI/2.f);

    if (timer < 0.0f)
    {
        on_success();

    }



    display_leaf_text();
}