#pragma once
#include "BehaviorNode.h"

class D_Initialize : public BaseNode<D_Initialize>
{
protected:
    virtual void on_enter() override;
    //virtual void on_exit() override;

private:
    bool init_flag = false;
};