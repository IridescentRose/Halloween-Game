#include "MainState.h"
#include <Utilities/Timer.h>

#if CURRENT_PLATFORM == PLATFORM_PSP
#define S_EXT ".bgm"
#else
#define S_EXT ".ogg"
#endif

MainState::MainState(){
	
}

void MainState::init()
{
	player = new Player();
	ambient = new Audio::AudioClip("./assets/snd/ambience" + std::string(S_EXT), true);
	ambient->SetLoop(true);
	ambient->Play();
	roomManager = new RoomManager();
	
	bedroomTex = GFX::g_TextureManager->loadTex("./assets/bedroom.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	bedroom = new GFX::Render2D::Sprite(bedroomTex);
	bedroom->setScale(3.0f, 3.0f);
	roomManager->addRoom(Room::BedRoom, bedroom);

	std::vector<glm::vec4>* vec = new std::vector<glm::vec4>();
	vec->push_back({ -128, -10, 550, 200 });
	vec->push_back({ -128, 165, 100, 200 });
	vec->push_back({ 250, 165, 550, 200 });
	vec->push_back({ -128, 16, -32, 160 });
	roomManager->addBounds(Room::BedRoom, vec);

	nurseryTex = GFX::g_TextureManager->loadTex("./assets/nursery.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	nursery = new GFX::Render2D::Sprite(nurseryTex);
	nursery->setScale(3.0f, 3.0f);
	roomManager->addRoom(Room::Nursery, nursery);

	std::vector<glm::vec4>* vec3 = new std::vector<glm::vec4>();
	vec3->push_back({ -8, -56, 500, 300 });
	vec3->push_back({ -8, 280, 96, 300 });
	vec3->push_back({ 180, 280, 300, 300 });
	vec3->push_back({ 180, 80, 280, 200 });
	roomManager->addBounds(Room::Nursery, vec3);

	guestTex = GFX::g_TextureManager->loadTex("./assets/guest.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	guest = new GFX::Render2D::Sprite(guestTex);
	guest->setScale(3.0f, 3.0f);
	roomManager->addRoom(Room::Guest, guest);

	std::vector<glm::vec4>* vec4 = new std::vector<glm::vec4>();
	vec4->push_back({ 52, 4, 412, 272 });
	vec4->push_back({ 312, 144, 412, 272 });
	vec4->push_back({ 52, 144, 152, 272 });
	vec4->push_back({ 52, 232, 224, 272 });
	vec4->push_back({ 260, 232, 412, 272 });
	roomManager->addBounds(Room::Guest, vec4);


	hallwayTex = GFX::g_TextureManager->loadTex("./assets/hallway.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	hallway = new GFX::Render2D::Sprite(hallwayTex);
	hallway->setScale(3.0f, 3.0f);
	roomManager->addRoom(Room::Hallway, hallway);

	std::vector<glm::vec4>* vec2 = new std::vector<glm::vec4>();
	vec2->push_back({ -400, -240, 840, 700 }); //Main box
	vec2->push_back({ 248, -240, 1200, 440 }); //Hall r
	vec2->push_back({ -1200, -240, 32, 440 }); //Hall L
	vec2->push_back({ -1200, 440, -312, 540 }); //Bot
	vec2->push_back({ 732, 440, 840, 544 }); //Bot
	vec2->push_back({ 768, 640, 840, 700 });
	vec2->push_back({ 360, 668, 716, 700 });
	vec2->push_back({ -200, 668, 16, 700 });
	roomManager->addBounds(Room::Hallway, vec2);

	roomManager->switchRoom(Room::Guest);

	vignetteTex = GFX::g_TextureManager->loadTex("./assets/vignette.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, false);
	vignette = new GFX::Render2D::Sprite(vignetteTex);
	vignette->setPosition(240, 136);

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
	vignette->draw();
}
