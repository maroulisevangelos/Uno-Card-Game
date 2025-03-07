#include "graphics.h"
#include "game.h"
#include "config.h"

void resize(int w, int h) {
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->setWindowDimensions((unsigned int)w, (unsigned int)h);
}

void update(float ms)
{
    Game* game = reinterpret_cast<Game *>(graphics::getUserData());
    game->update();
}

void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game mygame;
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "UNO Game v1.0");

    graphics::setUserData(&mygame);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();
    graphics::startMessageLoop();

    return 0;
}