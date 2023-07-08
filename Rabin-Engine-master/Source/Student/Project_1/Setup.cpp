#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
	//Create your inital agents
	for (int i = 0; i <= 100; ++i) {

		agents->create_behavior_agent("MainAgent", BehaviorTreeTypes::Main_AI);
		//agents->create_behavior_agent("LashAgent", BehaviorTreeTypes::LashTest);
		
	}


	int i = 0;
	for (auto T_agent : agents->get_all_agents()) {
		//float size = (float)agents->get_all_agents().size();
		
		T_agent->set_yaw(RNG::range<float>(-6.28319f, 6.28319f));
		T_agent->set_position(RNG::world_position());
		T_agent->set_AGrole(Agent_ROLE::SEARCHER);
		T_agent->set_color({ 0,0,0 });
		T_agent->set_Appeal(RNG::range<int>(50, 100));
		T_agent->set_Confidence(RNG::range<int>(50, 100));

		T_agent->set_scaling(1.0f);
		i++;
	}



	// you can technically load any map you want, even create your own map file,
	// but behavior agents won't actually avoid walls or anything special, unless you code that yourself
	// that's the realm of project 2 though
	terrain->goto_map(0);

	// you can also enable the pathing layer and set grid square colors as you see fit
	// works best with map 0, the completely blank map
	terrain->pathLayer.set_enabled(true);
	terrain->pathLayer.set_value(0, 0, Colors::Red);

	// camera position can be modified from this default as well
	auto camera = agents->get_camera_agent();
	camera->set_position(Vec3(150.0f, 70.0f, terrain->mapSizeInWorld * 0.5f));
	camera->set_pitch(2.53073); // 35 degrees

	audioManager->SetVolume(0.5f);
	audioManager->PlaySoundEffect(L"Assets\\Audio\\glassclang.wav");
	// uncomment for example on playing music in the engine (must be .wav)
	audioManager->PlayMusic(L"Assets\\Audio\\broadcastermumble.wav", true);
	// audioManager->PauseMusic(...);
	// audioManager->ResumeMusic(...);
	// audioManager->StopMusic(...);
}