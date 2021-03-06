#include "MainState.h"
#include <Utilities/Timer.h>
#include <Utilities/Input.h>

#if CURRENT_PLATFORM == PLATFORM_PSP
#define S_EXT ".bgm"
#else
#define S_EXT ".ogg"
#endif

MainState::MainState(): newWindowTimer(5.0f){
	
}

void MainState::init()
{
	player = new Player();
	ambient = new Audio::AudioClip("./assets/snd/ambience" + std::string(S_EXT), true);
	ambient->SetLoop(true);

	thunderClap = new Audio::AudioClip("./assets/snd/thunder.wav", false);
	monster = new Audio::AudioClip("./assets/snd/monster.wav", false);
	creak = new Audio::AudioClip("./assets/snd/creak.wav", false);
	roomManager = new RoomManager();
	introDone = false;

	introTex = GFX::g_TextureManager->loadTex("./assets/bedroom-lit.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	intro = new GFX::Render2D::Sprite(introTex);
	intro->setScale(3.0f, 3.0f);
	intro->setPosition(480, 200);

	bedroomTex = GFX::g_TextureManager->loadTex("./assets/bedroom.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	bedroom = new GFX::Render2D::Sprite(bedroomTex);
	bedroom->setScale(3.0f, 3.0f);


	bedroom2Tex = GFX::g_TextureManager->loadTex("./assets/bedroom-e.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	bedroom2 = new GFX::Render2D::Sprite(bedroom2Tex);
	bedroom2->setScale(3.0f, 3.0f);

	roomManager->addRoom(Room::BedRoom, { bedroom, bedroom2 });

	std::vector<glm::vec4>* vec = new std::vector<glm::vec4>();
	vec->push_back({ -128, -10, 550, 200 });
	vec->push_back({ -128, 165, 100, 200 });
	vec->push_back({ 250, 165, 550, 200 });
	vec->push_back({ -128, 16, -32, 160 });


	std::vector<TPInfo>* tpvec = new std::vector<TPInfo>();
	tpvec->push_back({ { 72, -10, 312, 16 } , {100, -128}, Room::Hallway, player });
	roomManager->addBounds(Room::BedRoom, vec);
	roomManager->addTeleport(Room::BedRoom, tpvec);

	nurseryTex = GFX::g_TextureManager->loadTex("./assets/nursery.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	nursery = new GFX::Render2D::Sprite(nurseryTex);
	nursery->setScale(3.0f, 3.0f);

	nursery2Tex = GFX::g_TextureManager->loadTex("./assets/nursery-e.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	nursery2 = new GFX::Render2D::Sprite(nursery2Tex);
	nursery2->setScale(3.0f, 3.0f);
	roomManager->addRoom(Room::Nursery, { nursery, nursery2 });

	std::vector<glm::vec4>* vec3 = new std::vector<glm::vec4>();
	vec3->push_back({ -8, -56, 500, 300 });
	vec3->push_back({ -8, 280, 96, 300 });
	vec3->push_back({ 180, 280, 300, 300 });
	vec3->push_back({ 180, 80, 280, 200 });
	roomManager->addBounds(Room::Nursery, vec3);

	std::vector<TPInfo>* tpvec3 = new std::vector<TPInfo>();
	tpvec3->push_back({ { 460, -32, 500, 84 } , {684, 600}, Room::Hallway, player });
	roomManager->addTeleport(Room::Nursery, tpvec3);

	guestTex = GFX::g_TextureManager->loadTex("./assets/guest.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	guest = new GFX::Render2D::Sprite(guestTex);
	guest->setScale(3.0f, 3.0f);

	guest2Tex = GFX::g_TextureManager->loadTex("./assets/guest-e.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	guest2 = new GFX::Render2D::Sprite(guest2Tex);
	guest2->setScale(3.0f, 3.0f);
	roomManager->addRoom(Room::Guest, { guest, guest2 });

	std::vector<glm::vec4>* vec4 = new std::vector<glm::vec4>();
	vec4->push_back({ 52, 4, 412, 272 });
	vec4->push_back({ 312, 144, 412, 272 });
	vec4->push_back({ 52, 144, 152, 272 });
	vec4->push_back({ 52, 232, 224, 272 });
	vec4->push_back({ 260, 232, 412, 272 });
	roomManager->addBounds(Room::Guest, vec4);

	std::vector<TPInfo>* tpvec4 = new std::vector<TPInfo>();
	tpvec4->push_back({ { 200, 4, 264, 32} , {-260, 600}, Room::Hallway, player });
	roomManager->addTeleport(Room::Guest, tpvec4);
	timesOpened = 0;

	hallwayTex = GFX::g_TextureManager->loadTex("./assets/hallway.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	hallway = new GFX::Render2D::Sprite(hallwayTex);
	hallway->setScale(3.0f, 3.0f);
	roomManager->addRoom(Room::Hallway, { hallway, hallway });

	std::vector<glm::vec4>* vec2 = new std::vector<glm::vec4>();
	vec2->push_back({ -400, -240, 840, 700 }); //Main box
	vec2->push_back({ 248, -240, 1200, 440 }); //Hall r
	vec2->push_back({ -1200, -240, 32, 440 }); //Hall L
	vec2->push_back({ -1200, 440, -312, 540 }); //Bot
	vec2->push_back({ 732, 440, 840, 544 }); //Bot
	vec2->push_back({ 768, 640, 840, 700 });
	vec2->push_back({ 360, 668, 716, 700 });
	vec2->push_back({ -200, 668, 16, 700 });
	std::vector<TPInfo>* tpvec2 = new std::vector<TPInfo>();
	tpvec2->push_back({ { -64, -240, 256, -200 } , {192, 64}, Room::BedRoom, player });
	tpvec2->push_back({ { 680, 640, 840, 700 } , {400, 48}, Room::Nursery, player });
	tpvec2->push_back({ { -320, 660, -200, 700 } , {232, 72}, Room::Guest, player });

	roomManager->addTeleport(Room::Hallway, tpvec2);
	roomManager->addBounds(Room::Hallway, vec2);

	roomManager->switchRoom(Room::BedRoom);

	vignetteTex = GFX::g_TextureManager->loadTex("./assets/vignette.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	vignette = new GFX::Render2D::Sprite(vignetteTex);
	vignette->setPosition(240, 136);

	gameOverTex = GFX::g_TextureManager->loadTex("./assets/die.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	gameOver = new GFX::Render2D::Sprite(gameOverTex);
	gameOver->setPosition(240, 136);

	textR = new GFX::UI::TextRenderer();
	textR->init("./assets/font.pgf");
	textR->setStyle({ 255, 255, 255, 255, 1.0f, TEXT_RENDERER_CENTER, TEXT_RENDERER_CENTER, 0.0f, 0 });
	isDead = false;

	for (auto i = 0; i < 3; i++) {
		roomsDeathTimer[i] = 100000;
	}
}

void MainState::cleanup()
{
	ambient->Stop();
	delete ambient;
	delete player;
	delete roomManager;

	delete bedroom;
	GFX::g_TextureManager->deleteTex(bedroomTex);
}

void MainState::enter()
{
	Utilities::g_AppTimer.reset();
}

void MainState::pause()
{

}

void MainState::resume()
{

}

void MainState::update(Core::GameStateManager* st)
{
	if (!isDead) {
		double dt = Utilities::g_AppTimer.deltaTime();

		newWindowTimer -= dt;
		if (newWindowTimer <= 0) {
			timesOpened++;
			if (timesOpened > 10) {
				timesOpened = 10;
			}
			newWindowTimer = rand() % (20-timesOpened) + 12;
			
			creak->Play(5);
			if (roomManager->stateMap[0] && roomManager->stateMap[2] && roomManager->stateMap[3]) {
				//Well this is instant death
				die();
				return;
			}
			else {
				int r = rand() % 3;
				switch (r) {
				case 0: {
					if (!roomManager->stateMap[0]) {
						roomManager->stateMap[0] = true;
						roomsDeathTimer[0] = 60 - timesOpened;
					}
					else {
						if (!roomManager->stateMap[2]) {
							roomManager->stateMap[2] = true;
							roomsDeathTimer[1] = 60 - timesOpened;
						}
						else {
							roomManager->stateMap[3] = true;
							roomsDeathTimer[2] = 60 - timesOpened;
						}
					}
					break;
				}

				case 1: {
					if (!roomManager->stateMap[2]) {
						roomManager->stateMap[2] = true;
						roomsDeathTimer[1] = 60 - timesOpened;
					}
					else {
						if (!roomManager->stateMap[0]) {
							roomManager->stateMap[0] = true;
							roomsDeathTimer[0] = 60 - timesOpened;
						}
						else {
							roomManager->stateMap[3] = true;
							roomsDeathTimer[2] = 60 - timesOpened;
						}
					}
					break;
				}

				case 2: {
					if (!roomManager->stateMap[3]) {
						roomManager->stateMap[3] = true;
						roomsDeathTimer[2] = 60 - timesOpened;
					}
					else {
						if (!roomManager->stateMap[0]) {
							roomManager->stateMap[0] = true;
							roomsDeathTimer[0] = 60 - timesOpened;
						}
						else {
							roomManager->stateMap[2] = true;
							roomsDeathTimer[1] = 60 - timesOpened;
						}
					}
					break;
				}
				};

			}
		}

		if (roomManager->stateMap[0]) {
			roomsDeathTimer[0] -= dt;
		}

		if (roomManager->stateMap[2]) {
			roomsDeathTimer[1] -= dt;
		}

		if (roomManager->stateMap[3]) {
			roomsDeathTimer[2] -= dt;
		}

		for (auto i = 0; i < 3; i++) {
			if (roomsDeathTimer[i] < 0) {
				die();
			}
		}

		if (!introDone && Utilities::g_AppTimer.elapsed() < 5.0) {
			if (Utilities::g_AppTimer.elapsed() > 3.0 && Utilities::g_AppTimer.elapsed() < 3.1) {
				thunderClap->Play(1);
			}
		}
		else {
			if (!introDone) {
				ambient->Play();
			}
			introDone = true;
			if (Utilities::g_AppTimer.elapsed() > 0.20) {
				Utilities::g_AppTimer.reset();
				player->tick();
			}
			roomManager->update(player->pos);
			player->update(dt, roomManager);
		}
	}
	else {
		if (Utilities::KeyPressed(GLFW_KEY_X) || Utilities::KeyHold(PSP_CTRL_CROSS)) {
#if CURRENT_PLATFORM == PLATFORM_PSP
			Platform::exitPlatform();
#else
			exit(0);
#endif
		}
	}
}

void MainState::draw(Core::GameStateManager* st)
{
	if (!isDead) {
		if (!introDone && Utilities::g_AppTimer.elapsed() < 5.0) {
			if (Utilities::g_AppTimer.elapsed() > 3.1) {
				textR->draw("Keep all windows closed.", { 240, 136 });
			}
			else {
				intro->draw();
			}
		}
		else {
			roomManager->draw();
			player->draw();
			vignette->draw();
		}
	}
	else {
		gameOver->draw();
	}
}

void MainState::die()
{
	isDead = true;
	monster->Play(3);
	ambient->Stop();
}
