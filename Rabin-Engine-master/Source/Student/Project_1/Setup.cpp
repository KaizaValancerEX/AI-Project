#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
	//Create your inital agents

	agents->create_behavior_agent("PlayerAgent", BehaviorTreeTypes::InputTester);



	auto agent = agents->get_all_agents();
	agent[0]->set_position(Vec3{ 50,0,50 });

	for (int i = 0; i <= 10; ++i) {

		//agents->create_behavior_agent("MainAgent", BehaviorTreeTypes::Main_AI);
		agents->create_behavior_agent("AIAgent", BehaviorTreeTypes::MoveTester);

	}



	int i = 0;
	for (auto T_agent : agents->get_all_agents()) {
		//float size = (float)agents->get_all_agents().size();
		T_agent->set_scaling(1.0f);


		T_agent->set_yaw(RNG::range<float>(-6.28319f, 6.28319f));
		Vec3 rngwp = RNG::world_position();
		//if (terrain->is_valid_grid_position(terrain->get_grid_position(rngwp)))
		T_agent->set_position(rngwp);
		//T_agent->set_AGrole(Agent_ROLE::SEARCHER);
		T_agent->set_color({ 0,0,0 });
		//T_agent->set_Appeal(RNG::range<int>(50, 100));
		//T_agent->set_Confidence(RNG::range<int>(50, 100));

		//T_agent->set_roll(1.5708f);
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
	std::cout << "X: " << camera->get_position().x << " Y: " << camera->get_position().y << " Z: " << camera->get_position().z << " Pitch: " << camera->get_pitch() << std::endl;
	camera->set_position(Vec3(-60, 90, 50));
	camera->set_pitch(0.6981f);

	audioManager->SetVolume(0.5f);
	//audioManager->PlaySoundEffect(L"Assets\\Audio\\glassclang.wav");
	// uncomment for example on playing music in the engine (must be .wav)
	audioManager->PlayMusic(L"Assets\\Audio\\Ambient3.wav", true);
	// audioManager->PauseMusic(...);
	// audioManager->ResumeMusic(...);
	// audioManager->StopMusic(...);
}