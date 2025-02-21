#include "player.h"
#include "graphics.h"
#include "game.h"

Player::Player(const Game& mygame)
	:GameObject(mygame)
{

}

void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_UP)) {
		height += 0.01f * graphics::getDeltaTime();
		if (height > 3.0f) {
			height = 3.0f;
		}
	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		height -= 0.01f * graphics::getDeltaTime();
		if (height < 1.0f) {
			height = 1.0f;
		}
	}
}

void Player::draw()
{
	if (playercard) {

		graphics::Brush br;
		br.gradient = true;
		float h = 1.0f * m_highlighted;

		SETCOLOR(br.fill_color, h, h, h);
		br.outline_opacity = 1.0f * m_active;
		graphics::drawRect(pos_x, pos_y, CARD_WIDTH, CARD_HEIGHT, br);

		graphics::setScale(height, height);
		if (playerTurn) {
			br.texture = std::string(ASSET_PATH) + std::to_string(playercard->getNumber()) + "_" + playercard->getColor() + ".png";
		}
		else {
			br.texture = std::string(ASSET_PATH) + "uno.png";
		}
		br.outline_opacity = 0.0f;
		

		graphics::drawRect(pos_x, pos_y, CARD_WIDTH, CARD_HEIGHT, br);

		graphics::resetPose();

		br.texture = "";
	}
}

void Player::init()
{
}

void Player::setPosX(float x)
{
	pos_x = x;
}

void Player::setPosY(float y)
{
	pos_y = y;
}

bool Player::contains(float x, float y)
{
	return distance(x,y,pos_x,pos_y)<CARD_WIDTH/2.0f;
}
