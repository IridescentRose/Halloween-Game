#include "MainState.h"
#include <Utilities/Timer.h>

#if CURRENT_PLATFORM == PLATFORM_PSP
#define S_EXT ".bgm"
#else
#define S_EXT ".ogg"
#endif

MainState::MainState()
{
	
}

void MainState::init()
{
	player = new Player();
	ambient = new Audio::AudioClip("./assets/snd/ambience" + std::string(S_EXT), true);
	ambient->SetLoop(true);
	ambient->Play();
	roomManager = new RoomManager();
	
	bedroomTex = GFX::g_TextureManager->loadTex("./assets/bedroom-lit.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	bedroom = new GFX::Render2D::Sprite(bedroomTex);
	bedroom->setScale(3.0f, 3.0f);
	roomManager->addRoom(Room::BedRoom, bedroom);

	std::vector<glm::vec4>* vec = new std::vector<glm::vec4>();

	vec->push_back({ -128, -10, 550, 200 });
	vec->push_back({ -128, 165, 100, 200 });
	vec->push_back({ 250, 165, 550, 200 });
	vec->push_back({ -128, 16, -32, 160 });
	
	roomManager->addBounds(Room::BedRoom, vec);
}

void MainState::cleanup()
{
	ambient->Stop();
	delete ambient;
	delete player;
	delete roomManager;
}

void MainState::enter()
{

}

void MainState::pause()
{

}

void MainState::resume()
{

}

void MainState::update(Core::GameStateManager* st)
{
	double dt = Utilities::g_AppTimer.deltaTime();

	if (Utilities::g_AppTimer.elapsed() > 0.20) {
		Utilities::g_AppTimer.reset();
		player->tick();
	}
	roomManager->update(player->pos);
	player->update(dt, roomManager);
}

void MainState::draw(Core::GameStateManager* st)
{
	roomManager->draw();
	player->draw();
}
