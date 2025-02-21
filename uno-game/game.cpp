#include "game.h"
#include "graphics.h"
#include "config.h"
#include <math.h>
#include <iostream>
#include "gameobject.h"

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	if (distance(CANVAS_WIDTH / 2, CANVAS_HEIGHT - 50, mx, my) < BUTTON_HEIGHT) {
		h = true;
	}
	else {
		h = false;
	}

	if (ms.button_left_pressed && distance(CANVAS_WIDTH / 2, CANVAS_HEIGHT - 50, mx, my) < BUTTON_HEIGHT) {
		status = STATUS_PLAYING;
	}
}

void Game::updatePlayingScreen()
{
	
	for (auto p1 : player1) {
		p1->update();
	}
	for (auto p2 : player2) {
		p2->update();
	}
	for (auto c : cards) {
		c->update();
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	graphics::Brush br;
	char info[40];
	sprintf_s(info, "%6.2f, %6.2f", mx, my);
	



	Player* cur_player = nullptr;
	if (round % 2 == 0) {
		for (auto p2 : player2) {
			p2->setTurn(false);
		}
		checkedCards = 0;
		for (auto p1 : player1) {
			p1->setTurn(true);
			if (p1->contains(mx, my)) {
				p1->setHighLight(true);
				cur_player = p1;
			}
			else {
				p1->setHighLight(false);
			}
			if (droppedcard) {
				if (p1->getCard()->getColor() != droppedcard->getColor() && p1->getCard()->getNumber() != droppedcard->getNumber()) {
					checkedCards += 1;
				}
			}
		}
		if (checkedCards == player1.size()) {
			if (cards.front()->contains(mx, my) && ms.button_left_pressed) {
				Player* p = new Player(*this);
				p->setCard(cards.front());
				player1.push_front(p);
				cards.pop_front();
			}
		}
	}
	else {
		for (auto p1 : player1) {
			p1->setTurn(false);
		}
		checkedCards = 0;
		for (auto p2 : player2) {
			p2->setTurn(true);
			if (p2->contains(mx, my)) {
				p2->setHighLight(true);
				cur_player = p2;
			}
			else {
				p2->setHighLight(false);
			}
			if (droppedcard) {
				if (p2->getCard()->getColor() != droppedcard->getColor() && p2->getCard()->getNumber() != droppedcard->getNumber()) {
					checkedCards += 1;
				}
			}
		}
		if (checkedCards == player2.size()) {
			if (cards.front()->contains(mx, my) && ms.button_left_pressed) {
				Player* p = new Player(*this);
				p->setCard(cards.front());
				player2.push_front(p);
				cards.pop_front();
			}
		}
	}


	if (ms.button_left_pressed && cur_player) {
		active_player = cur_player;
		active_player->setActive(true);

		init_pos_x = active_player->getPosX();
		init_pos_y = active_player->getPosY();
	}

	if (ms.dragging && active_player) {
		active_player->setPosX(mx);
		active_player->setPosY(my);
	}

	if (ms.button_left_released && active_player) {
		if (droppedcard == nullptr) {
			if (distance(active_player->getPosX(), active_player->getPosY(), init_pos_x, init_pos_y) > distance(active_player->getPosX(), active_player->getPosY(), CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f)) {
				active_player->setPosX(CANVAS_WIDTH / 2.0f);
				active_player->setPosY(CANVAS_HEIGHT / 2.0f);
				droppedcard = active_player->getCard();
				droppedcard->setPosX(active_player->getPosX());
				droppedcard->setPosY(active_player->getPosY());
				droppedcard->setDropped(true);
				Player* act = active_player;
				player1.remove_if([act](Player* p) {return p == act; });
				player2.remove_if([act](Player* p) {return p == act; });
			}

			else {
				active_player->setPosX(init_pos_x);
				active_player->setPosY(init_pos_y);
			}
		}
		else {
			if (distance(active_player->getPosX(), active_player->getPosY(), init_pos_x, init_pos_y) > distance(active_player->getPosX(), active_player->getPosY(), CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f)) {
				if (active_player->getCard()->getColor() == droppedcard->getColor() or active_player->getCard()->getNumber() == droppedcard->getNumber()) {
					active_player->setPosX(CANVAS_WIDTH / 2.0f);
					active_player->setPosY(CANVAS_HEIGHT / 2.0f);
					droppedcard = active_player->getCard();
					droppedcard->setPosX(active_player->getPosX());
					droppedcard->setPosY(active_player->getPosY());
					droppedcard->setDropped(true);
					Player* act = active_player;
					player1.remove_if([act](Player* p) {return p == act; });
					player2.remove_if([act](Player* p) {return p == act; });
				}
			}
			else {
				active_player->setPosX(init_pos_x);
				active_player->setPosY(init_pos_y);
			}
		}

		if (droppedcard && active_player->getPosY() != init_pos_y) {

			if (droppedcard->getNumber() == 12 && round % 2 == 0) {
				for (int i = 0; i < 2; i++) {
					Player* p = new Player(*this);
					p->setCard(cards.front());
					cards.pop_front();
					player2.push_front(p);
				}
			}
			else if (droppedcard->getNumber() == 12 && round % 2 != 0) {
				for (int i = 0; i < 2; i++) {
					Player* p = new Player(*this);
					p->setCard(cards.front());
					cards.pop_front();
					player1.push_front(p);
				}
			}

			if (active_player->getPosX() == CANVAS_WIDTH / 2.0f && active_player->getPosY() == CANVAS_HEIGHT / 2.0f) {
				round += 1;
			}
			else if (round % 2 == 0 && checkedCards == player1.size() && player1.front()->getCard()->getColor() != droppedcard->getColor() && player1.front()->getCard()->getNumber() != droppedcard->getNumber()) {
				round += 1;
			}
			else if (round % 2 != 0 && checkedCards == player2.size() && player2.front()->getCard()->getColor() != droppedcard->getColor() && player2.front()->getCard()->getNumber() != droppedcard->getNumber()) {
				round += 1;
			}

			if (droppedcard->getNumber() == 10 || droppedcard->getNumber() == 11) {
				round += 1;
			}
		}

		active_player->setActive(false);
		active_player = nullptr;

		if (player1.size() == 0 || player2.size() == 0) {
			status = STATUS_GAME_OVER;
			return;
		}

		int pos = 0;
		for (auto p1 : player1) {
			p1->setPosX(CANVAS_WIDTH * (pos + 0.5f) / float(player1.size()));
			p1->setPosY(CANVAS_HEIGHT * (0.3f) / 2.0f);
			pos += 1;
		}

		pos = 0;
		for (auto p2 : player2) {
			p2->setPosX(CANVAS_WIDTH * (pos + 0.5f) / float(player2.size()));
			p2->setPosY(CANVAS_HEIGHT * (1.7f) / 2.0f);
			pos += 1;
		}

	}
}

void Game::updateGameOverScreen()
{
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "startpic.png";
	br.outline_opacity = 0.0f;

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush cr;
	cr.outline_opacity = 0.0f;
	float x = 1.0f * h;
	SETCOLOR(cr.fill_color, x, x, x);
	cr.texture = std::string(ASSET_PATH) + "playbtn.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT - 50, BUTTON_WIDTH + 10, BUTTON_HEIGHT + 10, cr);
	//draw play button
	br.texture = std::string(ASSET_PATH) + "playbtn.png";
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT - 50, BUTTON_WIDTH, BUTTON_HEIGHT, br);

	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	char info[40];
	sprintf_s(info, "Press PLAY or ENTER to start");
	graphics::drawText(CANVAS_WIDTH / 4.0f, CANVAS_HEIGHT / 10.0f, 40, info, br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	br.texture = "";
	graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10, br);
}

void Game::drawPlayingScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw player
	for (auto p1 : player1) {
		p1->draw();
	}
	for (auto p2 : player2) {
		p2->draw();
	}
	for (auto c : cards) {
		c->draw();
	}

	if (droppedcard) {
		droppedcard->draw();
	}
	graphics::drawText(CANVAS_WIDTH / 120.0f, CANVAS_HEIGHT - 340, 30, "Player 1", br);
	graphics::drawText(CANVAS_WIDTH / 120.0f, CANVAS_HEIGHT - 140, 30, "Player 2", br);

	graphics::Brush cr;
	cr.fill_color[0] = 0.4f;
	cr.fill_color[1] = 0.8f;
	cr.fill_color[2] = 0.2f;
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	cr.texture = "";
	graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10, cr);
}

void Game::drawGameOverScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "images.png";
	br.outline_opacity = 0.0f;

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush cr;
	cr.outline_opacity = 0.0f;

	cr.fill_color[0] = 0.4f;
	cr.fill_color[1] = 0.7f;
	cr.fill_color[2] = 0.7f;
	cr.texture = "";
	cr.fill_secondary_color[0] = 0.0f;
	cr.fill_secondary_color[1] = 0.0f;
	cr.fill_secondary_color[2] = 0.4f;
	cr.gradient = true;
	cr.gradient_dir_u = 0.74f;
	cr.gradient_dir_v = 0.74f;
	graphics::drawRect(CANVAS_WIDTH / 4.0f + 250, CANVAS_HEIGHT / 5.0f - 20, 560, 100, cr);

	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	char info[40];
	sprintf_s(info, "GAME OVER");
	graphics::drawText(CANVAS_WIDTH / 4.0f, CANVAS_HEIGHT / 5.0f, 100, info, br);

	SETCOLOR(br.fill_color, 0.5f, 0.4f, 0.5f);
	if (player1.size() == 0) {
		graphics::drawText(CANVAS_WIDTH / 4.0f, CANVAS_HEIGHT / 2.0f, 100, "Player 1 wins", br);
	}
	else if (player2.size() == 0) {
		graphics::drawText(CANVAS_WIDTH / 4.0f, CANVAS_HEIGHT / 2.0f, 100, "Player 2 wins", br);
	}

	
	SETCOLOR(cr.fill_color, 0.0f, 0.0f, 0.9f);
	graphics::drawRect(CANVAS_WIDTH / 4.0f + 255, CANVAS_HEIGHT / 2.0f + 135, 700, 80, cr);

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawText(CANVAS_WIDTH / 4.0f - 80, CANVAS_HEIGHT / 2.0f + 150, 63, "Thank you!! Sofia-Vagelis", br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	br.texture = "";
	graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10, br);
}

void Game::update()
{
	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING) {
		updatePlayingScreen();
	}
	else {
		updateGameOverScreen();
	}
}

void Game::draw()
{
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING) {
		drawPlayingScreen();
	}
	else
		drawGameOverScreen();
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "Maguiston.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "whistling.mp3", 0.5f, true,4000);
	srand(time(0));
	for (int i = 0; i < 50; i++) {
		Card* c = new Card(*this);
		c->setNumber(rand0to14());
		c->setColor(randcolor());
		cards.push_front(c);
		c->setPosX(CANVAS_WIDTH * 0.93);
		c->setPosY(CANVAS_HEIGHT / 2.0f);
	}

	for (int i = 0; i < 7; i++) {
		Player* p = new Player(*this);
		p->setCard(cards.front());
		cards.pop_front();
		player1.push_front(p);
		p->setPosX(CANVAS_WIDTH * (i + 0.5f) / 7.0f);
		p->setPosY(CANVAS_HEIGHT * (0.3f) / 2.0f);
	}

	for (int i = 0; i < 7; i++) {
		Player* p = new Player(*this);
		p->setCard(cards.front());
		cards.pop_front();
		player2.push_front(p);
		p->setPosX(CANVAS_WIDTH * (i + 0.5f) / 7.0f);
		p->setPosY(CANVAS_HEIGHT * (1.7f) / 2.0f);
	}

	droppedcard = cards.front();
	droppedcard->setPosX(CANVAS_WIDTH / 2.0f);
	droppedcard->setPosY(CANVAS_HEIGHT / 2.0f);
	droppedcard->setDropped(true);
	cards.pop_front();
}

float Game::window2canvasX(float x)
{

	return x * CANVAS_WIDTH / (float)window_width;
}

float Game::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

Game::Game()
{
}

Game::~Game()
{
	for (auto p : player1) {
		delete p;
	}
	player1.clear();

	for (auto p : player2) {
		delete p;
	}
	player2.clear();

	for (auto c : cards) {
		delete c;
	}
	cards.clear();
}
