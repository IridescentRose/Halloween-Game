#include <Platform/Platform.h>
#include <GFX/RenderCore.h>

using namespace Stardust;

auto main() -> int {
	Platform::initPlatform();

	GFX::g_RenderCore->setClearColor(1.0f, 0.0f, 0.0f, 1.0f);


	while (
#if CURRENT_PLATFORM == PLATFORM_WIN
		!Platform::PC::g_Window->shouldClose()
#else
		true
#endif
		) {
		GFX::g_RenderCore->beginFrame();
		GFX::g_RenderCore->clear();


		GFX::g_RenderCore->endFrame();
		Platform::platformUpdate();
	}

	Platform::exitPlatform();
}