#pragma once
#include "BehaviorNode.h"

class D_Searcher : public BaseNode<D_Searcher>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
    //virtual void on_exit() override;
};