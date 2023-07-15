#pragma once
#include "BehaviorNode.h"

class D_CheckMovementInput : public BaseNode<D_CheckMovementInput>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
    //virtual void on_exit() override;

    InputHandler::InputState Wbtn, Abtn, Sbtn, Dbtn, Ebtn;

    enum class DirEnum:int
    {
        No_Dir=-1,

        Dir_UP,
        Dir_DOWN,
        Dir_LEFT,
        Dir_RIGHT,
        Dir_KillNearestNPC
    };

    bool movementflag = false;
};
