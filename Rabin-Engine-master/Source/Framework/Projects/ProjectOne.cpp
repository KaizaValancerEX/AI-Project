/******************************************************************************/
/*!
\file		ProjectOne.cpp
\project	CS380/CS580 AI Framework
\author		Dustin Holmes
\summary	Specification for project one - behavior trees

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include <pch.h>
#include "ProjectOne.h"


bool ProjectOne::initialize()
{
	std::cout << "Initializing Project One..." << std::endl;

	// create all the systems that project one requires
	terrain = std::make_unique<Terrain>();
	agents = std::make_unique<AgentOrganizer>();
	ui = std::make_unique<UICoordinator>();
	treeBuilder = std::make_unique<BehaviorTreeBuilder>();
	audioManager = std::make_unique<AudioManager>();

	return terrain->initialize() &&
		agents->initialize() &&
		ui->initialize() &&
		treeBuilder->initialize();
}

bool ProjectOne::finalize()
{
	build_ui();

	link_input();

	setup();

	return true;
}

void ProjectOne::shutdown()
{
	std::cout << "Shutting Down Project One..." << std::endl;

	treeBuilder->shutdown();
	treeBuilder.reset();

	ui->shutdown();
	ui.reset();

	agents->shutdown();
	agents.reset();

	terrain->shutdown();
	terrain.reset();
}

void ProjectOne::draw_meshes()
{
	terrain->draw();
	agents->draw();
}

void ProjectOne::draw_sprites()
{
	ui->draw_sprites();
}

void ProjectOne::draw_text()
{
	ui->draw_text();
}

void ProjectOne::draw_debug()
{
	terrain->draw_debug();
	agents->draw_debug();
	ui->draw_debug();
}

void ProjectOne::update()
{
	// have the ui coordinator determine its state
	ui->update();

	// have the input system update its current state and send out notifications
	InputHandler::update();

	//auto agent = agents->get_all_agents();
	//auto agentpos = agent[0]->get_position();

	//auto UP = InputHandler::get_current_state(KBKeys::W)
	//	, DOWN = InputHandler::get_current_state(KBKeys::S)
	//	, LEFT = InputHandler::get_current_state(KBKeys::A)
	//	, RIGHT = InputHandler::get_current_state(KBKeys::D);

	//if (UP == InputHandler::InputState::PRESSED) {
	//	if (!(agentpos.z + 1.f > 100.f))
	//		agentpos = Vec3(agentpos.x, agentpos.y, agentpos.z += 0.1f);
	//}



	////else if (UP == InputHandler::InputState::PRESSED &&
	////	LEFT == InputHandler::InputState::PRESSED
	////	) {
	////	if (!(agentpos.z + 0.0707f > 100.f))
	////		agentpos = Vec3(agentpos.x, agentpos.y, agentpos.z += 0.0707f);
	////	if (!(agentpos.x - 0.0707f < 0))
	////		agentpos = Vec3(agentpos.x -= 0.0707f, agentpos.y, agentpos.z);
	////}

	////else if (UP == InputHandler::InputState::PRESSED &&
	////	RIGHT == InputHandler::InputState::PRESSED
	////	) {
	////	if (!(agentpos.z + 0.0707f > 100.f))
	////		agentpos = Vec3(agentpos.x, agentpos.y, agentpos.z += 0.0707f);
	////	if (!(agentpos.x + 0.0707f > 100.f))
	////		agentpos = Vec3(agentpos.x += 0.0707f, agentpos.y, agentpos.z);

	////}

	//if (DOWN == InputHandler::InputState::PRESSED) {
	//	if (!(agentpos.z - 1.f < 0))
	//		agentpos = Vec3(agentpos.x, agentpos.y, agentpos.z -= 0.1f);

	//}

	////else if (DOWN == InputHandler::InputState::PRESSED &&
	////	LEFT == InputHandler::InputState::PRESSED
	////	) {
	////	if (!(agentpos.z - 0.0707f < 0))
	////		agentpos = Vec3(agentpos.x, agentpos.y, agentpos.z -= 0.0707f);
	////	if (!(agentpos.x - 0.0707f < 0))
	////		agentpos = Vec3(agentpos.x -= 0.0707f, agentpos.y, agentpos.z);

	////}

	////else if (DOWN == InputHandler::InputState::PRESSED &&
	////	RIGHT == InputHandler::InputState::PRESSED
	////	) {
	////	if (!(agentpos.z - 0.0707f < 0))
	////		agentpos = Vec3(agentpos.x, agentpos.y, agentpos.z -= 0.0707f);
	////	if (!(agentpos.x + 0.0707f > 100.f))
	////		agentpos = Vec3(agentpos.x += 0.0707f, agentpos.y, agentpos.z);

	////}

	//if (LEFT == InputHandler::InputState::PRESSED) {
	//	if (!(agentpos.x - 1.f < 0))
	//		agentpos = Vec3(agentpos.x -= 0.1f, agentpos.y, agentpos.z);

	//}

	//if (RIGHT == InputHandler::InputState::PRESSED) {
	//	if (!(agentpos.x + 1.f > 100.f))
	//		agentpos = Vec3(agentpos.x += 0.1f, agentpos.y, agentpos.z);

	//}

	//agent[0]->set_position(agentpos);

	agents->update(deltaTime);
}

void ProjectOne::build_ui()
{
	// add a text field at the top for the project
	auto projectText = ui->create_text_field(UIAnchor::TOP, 0, 32, UIAnchor::CENTER, L"Project One");

	// add some text on the left side for displaying fps
	TextGetter fpsGetter = std::bind(&Engine::get_fps_text, engine.get());
	auto fpsText = ui->create_value_text_field(UIAnchor::TOP_LEFT, 90, 32, L"FPS:", fpsGetter);
}

void ProjectOne::link_input()
{
	Callback f2CB = std::bind(&ProjectOne::on_f2, this);
	InputHandler::notify_when_key_pressed(KBKeys::F2, f2CB);

	Callback f3CB = std::bind(&ProjectOne::on_f3, this);
	InputHandler::notify_when_key_pressed(KBKeys::F3, f3CB);
}

void ProjectOne::on_f2()
{
	engine->change_projects(Project::Type::TWO);
}

void ProjectOne::on_f3()
{
	engine->change_projects(Project::Type::THREE);
}

