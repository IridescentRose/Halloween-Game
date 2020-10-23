#include "RoomManager.h"

RoomManager::RoomManager()
{
	currentRoom = Room::BedRoom;
}

RoomManager::~RoomManager()
{
}

void RoomManager::switchRoom(Room)
{
}

void RoomManager::addRoom(Room r, GFX::Render2D::Sprite* s)
{
	spritemap.emplace(r, s);
}

void RoomManager::update(glm::vec2 pos){
	if (spritemap.find(currentRoom) != spritemap.end()) {
		spritemap[currentRoom]->setPosition(480 - pos.x, pos.y);
	}
}

void RoomManager::draw()
{
	if (spritemap.find(currentRoom) != spritemap.end()) {
		spritemap[currentRoom]->draw();
	}
}
