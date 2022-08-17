#include "game.h"

const QString Game::PATH_TO_SPACESHIP_PIXMAP  = ":/res/spaceship.png";
const QString Game::PATH_TO_ENEMY_PROJECTILE_PIXMAP = ":/res/enemy_projectile.png";
const QString Game::PATH_TO_PROJECTILE_PIXMAP = ":/res/projectile.png";
const QString Game::PATH_TO_BG_PIXMAP         = ":/res/bg.png";
const QString Game::PATH_TO_ENEMY_PIXMAP      = ":/res/enemy1.png";
const QString Game::PATH_TO_ENEMIES_PIXMAP    = ":/res/enemies.png";
const QString Game::PATH_TO_EXPLOSION_PIXMAP  = ":/res/explosion.png";
const QString Game::PATH_TO_UFO_PIXMAP        = ":/res/ufo.png";
const QString Game::PATH_TO_POWERUP_PIXMAP    = ":/res/power_ups.png";

Game::Game()
{

}

int Game::convertPixelToGridPoint(int pixelVal)
{
    return int(pixelVal/GRID_SIZE);
}

int Game::convertGridPointToPixel(int gridPointVal)
{
    return gridPointVal*GRID_SIZE;
}
