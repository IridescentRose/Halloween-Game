#include "Menu.h"
#include <Utilities/Input.h>

MenuState::MenuState()
{
}

#if CURRENT_PLATFORM == PLATFORM_PSP
#define SOUND_EXT ".bgm"
#else
#define SOUND_EXT ".ogg"
#endif

void MenuState::init()
{
	music = new Audio::AudioClip("./assets/snd/menu" + std::string(SOUND_EXT), true);
	music->SetLoop(true);
	music->Play();

	logoTex = GFX::g_TextureManager->loadTex("./assets/logo.png", GFX_FILTER_LINEAR, GFX_FILTER_LINEAR, true);
	bloodTex = GFX::g_TextureManager->loadTex("./assets/blood.png", GFX_FILTER_LINEAR, GFX_FILTER_LINEAR, true);
	buttonTex = GFX::g_TextureManager->loadTex("./assets/button.png", GFX_FILTER_LINEAR, GFX_FILTER_LINEAR, true);

	logo = new GFX::Render2D::Sprite(logoTex);
	blood = new GFX::Render2D::Sprite(bloodTex);
	button = new GFX::Render2D::Sprite(buttonTex);
	button->setScale(2.0f, 2.0f);

	logo->setPosition(240, 32);
	blood->setPosition(360, 48);

	text.init("./assets/font.pgf");
	text.setStyle({ 255, 255, 255, 255, 1.0f, TEXT_RENDERER_CENTER, TEXT_RENDERER_CENTER, 0.0f, 0 });

	sel = 0;
}

void MenuState::cleanup()
{
	text.cleanup();
	music->Stop();
	delete music;
	GFX::g_TextureManager->deleteTex(logoTex);
	delete logo;
}

void MenuState::enter()
{
}

void MenuState::pause()
{
}

void MenuState::resume()
{
}

void MenuState::update(Core::GameStateManager* st)
{
	if (Utilities::KeyPressed(GLFW_KEY_UP) || Utilities::KeyPressed(PSP_CTRL_UP)) {
		sel--;
		if (sel < 0) {
			sel = 0;
		}
	}

	if (Utilities::KeyPressed(GLFW_KEY_DOWN) || Utilities::KeyPressed(PSP_CTRL_DOWN)) {
		sel++;
		if (sel > 1) {
			sel = 1;
		}
	}

	if (Utilities::KeyPressed(GLFW_KEY_SPACE) || Utilities::KeyPressed(GLFW_KEY_ENTER) || Utilities::KeyPressed(PSP_CTRL_CROSS) || Utilities::KeyPressed(PSP_CTRL_START)) {
		if (sel == 0) {
			//Load the game
		}
		else {
#if CURRENT_PLATFORM == PLATFORM_PSP
			Platform::exitPlatform();
#else
			exit(0);
#endif
		}
	}
}

void MenuState::draw(Core::GameStateManager* st)
{
	blood->draw();
	logo->draw();

	button->setPosition(240, 136);
	button->draw();
	if (sel == 0) {
		text.setStyle({ 255, 0, 0, 255, 1.0f, TEXT_RENDERER_CENTER, TEXT_RENDERER_CENTER, 0.0f, 0 });
	}
	else {
		text.setStyle({ 255, 255, 255, 255, 1.0f, TEXT_RENDERER_CENTER, TEXT_RENDERER_CENTER, 0.0f, 0 });
	}
	text.draw("Start", { 240, 136 });

	button->setPosition(240, 136 + 64);
	button->draw();
	if (sel) {
		text.setStyle({ 255, 0, 0, 255, 1.0f, TEXT_RENDERER_CENTER, TEXT_RENDERER_CENTER, 0.0f, 0 });
	}
	else {
		text.setStyle({ 255, 255, 255, 255, 1.0f, TEXT_RENDERER_CENTER, TEXT_RENDERER_CENTER, 0.0f, 0 });
	}
	text.draw("Exit", { 240, 136 + 64 });
}
