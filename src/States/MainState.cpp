#include "MainState.h"
#include <Utilities/Timer.h>

MainState::MainState()
{
	
}

void MainState::init()
{
	player = new Player();
	player->x = 240;
	player->y = 136;
}

void MainState::cleanup()
{

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
