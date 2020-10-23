#pragma once
#include <map>
#include <GFX/2D/Sprite.h>

using namespace Stardust;

enum class Room {
	BedRoom = 0,
};

class RoomManager {
public:
	RoomManager();
	~RoomManager();

	void switchRoom(Room);

	void addRoom(Room, GFX::Render2D::Sprite*);

	void update(glm::vec2 pos);
	void draw();
private:
	Room currentRoom;

	std::map<Room, GFX::Render2D::Sprite*> spritemap;
};