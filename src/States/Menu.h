#pragma once
#include <Core/GameState.h>
#include <NonCopy.h>
#include <NonMovable.h>
#include <Utilities/Timer.h>
#include <GFX/2D/Sprite.h>
#include <GFX/UI/TextRenderer.h>
#include <Audio/AudioClip.h>

using namespace Stardust;

class MenuState : public Core::GameState, NonCopyable, NonMovable {
public:
	MenuState();

	void init();
	void cleanup();

	void enter();
	void pause();
	void resume();

	void update(Core::GameStateManager* st);
	void draw(Core::GameStateManager* st);

private:
	GFX::Render2D::Sprite* logo, *blood, *button;
	Audio::AudioClip* music;
	unsigned int logoTex, bloodTex, buttonTex;
	GFX::UI::TextRenderer text;

	int sel;
};