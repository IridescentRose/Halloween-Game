#include "Splash.h"
#include "Menu.h"

#ifdef NDEBUG
#define S_TIME 0.0
#else
#define S_TIME 4.0
#endif

SplashState::SplashState(): sprt()
{
}

void SplashState::init()
{
	tex = GFX::g_TextureManager->loadTex("./assets/splash/logo.png", GFX_FILTER_LINEAR, GFX_FILTER_LINEAR, true);
	
	sprt = new GFX::Render2D::Sprite(tex, { 512, 512 });
	sprt->setPosition(240, 136);
}

void SplashState::cleanup()
{
	GFX::g_TextureManager->deleteTex(tex);
	delete sprt;
}

void SplashState::enter()
{
}

void SplashState::pause()
{
}

void SplashState::resume()
{
}
MenuState* menu;
void SplashState::update(Core::GameStateManager* st)
{
	Utilities::g_AppTimer.deltaTime();
	if (Utilities::g_AppTimer.elapsed() >= S_TIME) {
		menu = new MenuState();
		menu->init();
		st->changeState(menu);
	}
}

void SplashState::draw(Core::GameStateManager* st)
{
	sprt->draw();
}
