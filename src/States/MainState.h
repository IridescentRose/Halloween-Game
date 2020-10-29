#pragma once
#include <Core/GameState.h>
#include <NonCopy.h>
#include <NonMovable.h>
#include <Utilities/Timer.h>
#include <GFX/2D/Sprite.h>
#include "../Player.h"
#include <Audio/AudioClip.h>
#include "../RoomManager.h"
#include <GFX/UI/TextRenderer.h>

using namespace Stardust;

class MainState : public Core::GameState, NonCopyable, NonMovable {
public:
	MainState();

	void init();
	void cleanup();

	void enter();
	void pause();
	void resume();

	void update(Core::GameStateManager* st);
	void draw(Core::GameStateManager* st);

	void die();
private:
	Player* player;
	Audio::AudioClip* ambient, *thunderClap, *monster;
	RoomManager* roomManager;

	GFX::Render2D::Sprite* bedroom, *bedroom2, *intro, *hallway, *nursery, *nursery2, *guest, *guest2, *vignette, *gameOver;
	unsigned int bedroomTex, bedroom2Tex, introTex, hallwayTex, nurseryTex, nursery2Tex, guestTex, guest2Tex, vignetteTex, gameOverTex;
	bool introDone;
	bool isDead;
	GFX::UI::TextRenderer* textR;
};