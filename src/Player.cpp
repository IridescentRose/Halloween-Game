#include "Player.h"
#include <Utilities/Input.h>

Player::Player() : x(0), y(0), mainSprite(nullptr), mcTex(0)
{
	mcTex = GFX::g_TextureManager->loadTex("./assets/mc.png", GFX_FILTER_NEAREST, GFX_FILTER_NEAREST, true);
	mainSprite = new GFX::Render2D::CharacterSprite({64, 64}, new GFX::TextureAtlas(4), mcTex);

	down = new GFX::Render2D::CharacterAnimInfo();
	down->animLength = 4;
	down->indexStart = 0;

	left = new GFX::Render2D::CharacterAnimInfo();
	left->animLength = 4;
	left->indexStart = 4;

	right = new GFX::Render2D::CharacterAnimInfo();
	right->animLength = 4;
	right->indexStart = 8;

	top = new GFX::Render2D::CharacterAnimInfo();
	top->animLength = 4;
	top->indexStart = 12;

	idown = new GFX::Render2D::CharacterAnimInfo();
	idown->animLength = 1;
	idown->indexStart = 0;

	ileft = new GFX::Render2D::CharacterAnimInfo();
	ileft->animLength = 1;
	ileft->indexStart = 4;

	iright = new GFX::Render2D::CharacterAnimInfo();
	iright->animLength = 1;
	iright->indexStart = 8;

	itop = new GFX::Render2D::CharacterAnimInfo();
	itop->animLength = 1;
	itop->indexStart = 12;

	mainSprite->addAnimEvent("left", left);
	mainSprite->addAnimEvent("top", top);
	mainSprite->addAnimEvent("down", down);
	mainSprite->addAnimEvent("right", right);


	mainSprite->addAnimEvent("ileft", ileft);
	mainSprite->addAnimEvent("itop", itop);
	mainSprite->addAnimEvent("idown", idown);
	mainSprite->addAnimEvent("iright", iright);

	mainSprite->triggerAnimEvent("idown");
	mainSprite->tickPhase();

	currentTickCount = 0;
}

Player::~Player()
{
}

void Player::update()
{
	if (Utilities::KeyPressed(GLFW_KEY_DOWN) || Utilities::KeyPressed(GLFW_KEY_S) || Utilities::KeyPressed(PSP_CTRL_DOWN)) {
		if (direction != Direction::Down) {
			direction = Direction::Down;
		}
		mainSprite->triggerAnimEvent("down");

		currentTickCount = 0;
	}

	if (Utilities::KeyPressed(GLFW_KEY_LEFT) || Utilities::KeyPressed(GLFW_KEY_A) || Utilities::KeyPressed(PSP_CTRL_LEFT)) {
		if (direction != Direction::Left) {
			direction = Direction::Left;
		}
		mainSprite->triggerAnimEvent("left");
		currentTickCount = 0;
	}

	if (Utilities::KeyPressed(GLFW_KEY_RIGHT) || Utilities::KeyPressed(GLFW_KEY_D) || Utilities::KeyPressed(PSP_CTRL_RIGHT)) {
		if (direction != Direction::Right) {
			direction = Direction::Right;
		}
		mainSprite->triggerAnimEvent("right");
		currentTickCount = 0;
	}
	
	if (Utilities::KeyPressed(GLFW_KEY_UP) || Utilities::KeyPressed(GLFW_KEY_W) || Utilities::KeyPressed(PSP_CTRL_UP)) {
		if (direction != Direction::Top) {
			direction = Direction::Top;
		}
		mainSprite->triggerAnimEvent("top");
		currentTickCount = 0;
	}
}

void Player::tick()
{
	mainSprite->tickPhase();

	if (currentTickCount % 2 == 0) {
		if (!(Utilities::KeyPressed(GLFW_KEY_DOWN) || Utilities::KeyPressed(GLFW_KEY_S) || Utilities::KeyPressed(PSP_CTRL_DOWN))) {
			if (!(Utilities::KeyPressed(GLFW_KEY_UP) || Utilities::KeyPressed(GLFW_KEY_W) || Utilities::KeyPressed(PSP_CTRL_UP))) {
				if (!(Utilities::KeyPressed(GLFW_KEY_LEFT) || Utilities::KeyPressed(GLFW_KEY_A) || Utilities::KeyPressed(PSP_CTRL_LEFT))) {
					if (!(Utilities::KeyPressed(GLFW_KEY_RIGHT) || Utilities::KeyPressed(GLFW_KEY_D) || Utilities::KeyPressed(PSP_CTRL_RIGHT))) {
						//We should return to idle.

						switch (direction) {
						case Direction::Top: {
							mainSprite->triggerAnimEvent("itop");
							break;
						}

						case Direction::Down: {
							mainSprite->triggerAnimEvent("idown");
							break;
						}

						case Direction::Left: {
							mainSprite->triggerAnimEvent("ileft");
							break;
						}

						case Direction::Right: {
							mainSprite->triggerAnimEvent("iright");
							break;
						}
						}

					}
				}
			}
		}
	}
}

void Player::draw()
{
	mainSprite->setPosition(x, y);
	mainSprite->draw();
}