#pragma once
#include "gameobject.h"
#include "config.h"
#include "card.h"

class Player : public GameObject {
	float pos_x=CANVAS_WIDTH * 0.84, pos_y=CANVAS_HEIGHT/2.1f;
	float height = 1.0f;
	Card * playercard = nullptr;

	bool m_highlighted = false;
	bool m_active = false;
	bool playerTurn = false;
public:
	Player(const class Game & mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	void setPosX(float x);
	void setPosY(float y);

	void setCard(Card* c) { playercard = c; }
	Card* getCard() { return playercard; }

	void setHighLight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }
	void setTurn(bool t) { playerTurn = t; }

	bool contains(float x, float y);
};
