#include "RoomManager.h"

#include <Utilities/Input.h>

RoomManager::RoomManager()
{
	currentRoom = Room::BedRoom;
	tpmap.clear();

	for (auto i = 0; i < 4; i++) {
		stateMap[i] = false;
	}
}

RoomManager::~RoomManager()
{
}

void RoomManager::switchRoom(Room r)
{
	currentRoom = r;
}

void RoomManager::addRoom(Room r, std::array<GFX::Render2D::Sprite*, 2> s)
{
	spritemap.emplace(r, s);
}

void RoomManager::addBounds(Room r, std::vector<glm::vec4> *bounds)
{
	boundsmap.emplace(r, bounds);
}

void RoomManager::addTeleport(Room r, std::vector<TPInfo>* info)
{
	tpmap.emplace(r, info);
}

void RoomManager::setRoomState(Room r, bool b)
{
	stateMap[(int)r] = b;
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

#include <iostream>
bool RoomManager::checkBounds2(glm::vec2 pos)
{
	if (tpmap.find(currentRoom) != tpmap.end()) {
		auto tpVec = *tpmap[currentRoom];

		for (auto& tp : tpVec) {
			glm::vec2 bot = { tp.bounds.x, tp.bounds.y };
			glm::vec2 top = { tp.bounds.z, tp.bounds.w };

			if (!(pos.y > top.y || pos.y < bot.y) && !(pos.x > top.x || pos.x < bot.x)) {
				tp.p->pos = tp.pos;
				switchRoom(tp.destination);
				return false;
				break;
			}
		}
	}

	if (boundsmap.find(currentRoom) != boundsmap.end()) {
		std::vector<glm::vec4>* v = boundsmap[currentRoom];

		for (int i = 1; i < v->size(); i ++) {
			auto vec = (*v)[i];
			glm::vec2 bot = { vec.x, vec.y };
			glm::vec2 top = { vec.z, vec.w };

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
		spritemap[currentRoom][0]->setPosition(480 - pos.x, pos.y);
		spritemap[currentRoom][1]->setPosition(480 - pos.x, pos.y);

		if (stateMap[(int)currentRoom]) {
			//Check if we have pressed X to close window.
			if (Utilities::KeyPressed(GLFW_KEY_X) || Utilities::KeyHold(PSP_CTRL_CROSS)) {
				switch (currentRoom) {
				case Room::BedRoom: {
					if (!(pos.y > 200 || pos.y < 180) && !(pos.x > 312 || pos.x < 72)) {
						setRoomState(currentRoom, false);
					}
					break;
				}

				case Room::Guest: {
					if (!(pos.y > 272 || pos.y < 224) && !(pos.x > 264 || pos.x < 200)) {
						setRoomState(currentRoom, false);
					}
					break;
				}

				case Room::Nursery: {
					if (!(pos.y > 300 || pos.y < 260) && !(pos.x > 460 || pos.x < 160)) {
						setRoomState(currentRoom, false);
					}
					break;
				}

				default: 
					break;
				}
			}
		}

	}
}

void RoomManager::draw()
{
	if (spritemap.find(currentRoom) != spritemap.end()) {
		if (stateMap[(int)currentRoom]) {
			spritemap[currentRoom][1]->draw();
		}
		else {
			spritemap[currentRoom][0]->draw();
		}
	}
}
