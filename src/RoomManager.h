#pragma once
#include <map>
#include <vector>
#include <GFX/2D/Sprite.h>
#include "Player.h"
#include <Audio/AudioClip.h>
using namespace Stardust;


class Player;

enum class Room {
	BedRoom = 0,
	Hallway = 1,
	Nursery = 2,
	Guest = 3,
};

struct TPInfo {
	glm::vec4 bounds;
	glm::vec2 pos;
	Room destination;
	Player* p;
};

class RoomManager {
public:
	RoomManager();
	~RoomManager();

	void switchRoom(Room);

	void addRoom(Room, std::array<GFX::Render2D::Sprite*, 2>);
	void addBounds(Room, std::vector<glm::vec4> *bounds);
	void addTeleport(Room, std::vector<TPInfo> *info);
	void setRoomState(Room, bool);

	bool checkBounds(glm::vec2 pos);
	bool checkBounds2(glm::vec2 pos);

	void update(glm::vec2 pos);
	void draw();
	bool stateMap[4];
private:
	Room currentRoom;

	std::map<Room, std::array<GFX::Render2D::Sprite*, 2>> spritemap;
	std::map<Room, std::vector<TPInfo>*> tpmap;
	std::map<Room, std::vector<glm::vec4>*> boundsmap;
	Audio::AudioClip* close;
};