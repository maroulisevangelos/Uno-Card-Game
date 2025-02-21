#pragma once

#include "player.h"
#include "card.h"
#include <list>

class Game {
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_GAME_OVER} status_t;
	Player * player = nullptr;
	std::list<Player*> player1;
	std::list<Player*> player2;
	std::list<Card*> cards;
	Card * droppedcard = nullptr;
	Card* previousDroppedcard = nullptr;
	Player* active_player = nullptr;
	Player* previous_player = nullptr;
	float init_pos_x;
	float init_pos_y;
	int checkedCards;
	int round = 1;
	bool h = false;

	bool player_initialized = false;
	status_t status = STATUS_START;

	unsigned int window_width=WINDOW_WIDTH,
		         window_height=WINDOW_HEIGHT;
	
	void updateStartScreen();
	void updatePlayingScreen();
	void updateGameOverScreen();
	void drawStartScreen();
	void drawPlayingScreen();
	void drawGameOverScreen();
public:
	void update();
	void draw();
	void init();
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	Game();
	~Game();
};
