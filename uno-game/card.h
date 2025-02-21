#pragma once
#include "gameobject.h"
#include "config.h"
#include "util.h"

class Card : public GameObject {
	int number;
	char color;
	float height = 1.0f;
	float pos_x = CARD_WIDTH / 8; float pos_y = CARD_HEIGHT / 2;
	bool m_highlighted = false;
	bool m_active = false;
	bool dropped = false;
public:
	Card(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	void setPosX(float x);
	void setPosY(float y);
	void setHighlight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }
	void setDropped(bool d) { dropped = d; }
	bool contains(float x, float y);
	void setNumber(int num) { number = num; }
	int getNumber() { return number; }
	void setColor(char c){ color=c; }
	char getColor() { return color; }

};
