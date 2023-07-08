#pragma once

// Include all node headers in this file

// Example Control Flow Nodes
#include "ControlFlow/C_ParallelSequencer.h"
#include "ControlFlow/C_RandomSelector.h"
#include "ControlFlow/C_Selector.h"
#include "ControlFlow/C_Sequencer.h"

// Student Control Flow Nodes


// Example Decorator Nodes
#include "Decorator/D_Delay.h"
#include "Decorator/D_InvertedRepeater.h"
#include "Decorator/D_RepeatFourTimes.h"


// Student Decorator Nodes
#include "Decorator/D_Follower.h"
#include "Decorator/D_Searcher.h"
#include "Decorator/D_Leader.h"
#include "Decorator/D_Initialize.h"


// Example Leaf Nodes
#include "Leaf/L_CheckMouseClick.h"
#include "Leaf/L_Idle.h"
#include "Leaf/L_MoveToFurthestAgent.h"
#include "Leaf/L_MoveToMouseClick.h"
#include "Leaf/L_MoveToRandomPosition.h"
#include "Leaf/L_PlaySound.h"

// Student Leaf Nodes
#include "Leaf/L_CheckForEventTrigger.h"
#include "Leaf/L_Whiplash.h"
#include "Leaf/L_Wandering.h"
#include "Leaf/L_Follow.h"
#include "Leaf/L_FindHighestAppeal.h"
#include "Leaf/L_InitializeBlackBoard.h"
#include "Leaf/L_CheckConfidence.h"