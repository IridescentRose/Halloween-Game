#pragma once
#include <GFX/2D/CharacterSprite.h>
#include "RoomManager.h"

using namespace Stardust;

enum class Direction {
	Down, 
	Left,
	Right, 
	Top
};

class Player {
public:
	Player();
	~Player();

	void update(double dt, RoomManager* rm);
	void tick();
	void draw();

	glm::vec2 pos;

private:
	GFX::Render2D::CharacterSprite* mainSprite;
	GFX::Render2D::CharacterAnimInfo* left, * top, * down, * right;
	GFX::Render2D::CharacterAnimInfo* ileft, * itop, * idown, * iright;
	Direction direction;
	int currentTickCount;
	int mcTex;
};