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
}

void MainState::cleanup()
{
	ambient->Stop();
	delete ambient;
	delete player;
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
	player->update();
}

void MainState::draw(Core::GameStateManager* st)
{
	player->draw();
}
