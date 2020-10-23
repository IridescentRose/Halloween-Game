#include <Platform/Platform.h>
#include <GFX/RenderCore.h>
#include <Core/StateManager.h>
#include "States/Splash.h"
using namespace Stardust;

auto main() -> int {
	Platform::initPlatform("DLII");

	GFX::g_RenderCore->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Core::GameStateManager gsm = Core::GameStateManager();
	SplashState* state = new SplashState();
	state->init();
	gsm.changeState(state);
	GFX::g_RenderCore->setDefault2DMode();

		while (
#if CURRENT_PLATFORM == PLATFORM_WIN
			!Platform::PC::g_Window->shouldClose()
#else
			true
#endif
			&& gsm.isRunning()
		) {
		GFX::g_RenderCore->beginFrame();
		GFX::g_RenderCore->clear();

		gsm.update();
		gsm.draw();

		GFX::g_RenderCore->endFrame();
		Platform::platformUpdate();
	}

	Platform::exitPlatform();
}