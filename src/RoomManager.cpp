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

void RoomManager::addBounds(Room r, std::vector<glm::vec4> *bounds)
{
	boundsmap.emplace(r, bounds);
}

bool RoomManager::checkBounds(glm::vec2 pos)
{
	if (boundsmap.find(currentRoom) != boundsmap.end()) {
		std::vector<glm::vec4>* v = boundsmap[currentRoom];

		auto vec = (*v)[0];
		glm::vec2 bot = { vec.x, vec.y };
		glm::vec2 top = { vec.z, vec.w };

		if (!(pos.x < top.x && pos.x > bot.x&& pos.y < top.y && pos.y > bot.y)) {
			return false;
		}
		return true;
	}
	return false;
}

bool RoomManager::checkBounds2(glm::vec2 pos)
{
	if (boundsmap.find(currentRoom) != boundsmap.end()) {
		std::vector<glm::vec4>* v = boundsmap[currentRoom];

		for (int i = 1; i < v->size(); i ++) {
			auto vec = (*v)[i];
			glm::vec2 bot = { vec.x, vec.y };
			glm::vec2 top = { vec.z, vec.w };

			//if (!(pos.x > top.x || pos.x < bot.x)) {
			//	return false;
			//}
			if (!(pos.y > top.y || pos.y < bot.y) && !(pos.x > top.x || pos.x < bot.x)) {
				return false;
			}
			
		}
		return true;
	}
	return false;
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
