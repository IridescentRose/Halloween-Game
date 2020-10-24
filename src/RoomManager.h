#pragma once
#include <map>
#include <vector>
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
	void addBounds(Room, std::vector<glm::vec4> *bounds);

	bool checkBounds(glm::vec2 pos);
	bool checkBounds2(glm::vec2 pos);

	void update(glm::vec2 pos);
	void draw();
private:
	Room currentRoom;

	std::map<Room, GFX::Render2D::Sprite*> spritemap;
	std::map<Room, std::vector<glm::vec4>*> boundsmap;
};