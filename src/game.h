#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QString>

class Game
{
public:
    Game();
    constexpr static const QSize RESOLUTION = QSize(640, 480);
    static const QString PATH_TO_SPACESHIP_PIXMAP;
    static const QString PATH_TO_PROJECTILE_PIXMAP;
    static const QString PATH_TO_ENEMY_PROJECTILE_PIXMAP;
    static const QString PATH_TO_BG_PIXMAP;
    static const QString PATH_TO_ENEMY_PIXMAP;
    static const QString PATH_TO_ENEMIES_PIXMAP;
    constexpr static const int FPS = 60;
    constexpr static const float SPACESHIP_SPEED = 4.f;
    constexpr static const float SPACESHIP_PROJECTILE_SPEED = 4.f;
    constexpr static const int   SPACESHIP_SHOOT_COUNTER = 2 * (1000.0f/FPS);

    enum class Projectile{
        SPACESHIP, ENEMY
    };

    enum class Direction{
        NONE = 0, LEFT, RIGHT, DOWN
    };

    constexpr static const int ENEMY_SIZE = 32;

    constexpr static const int GRID_SIZE = 32;
    constexpr static const int GRID_WIDTH = RESOLUTION.width()/ENEMY_SIZE;
    constexpr static const int GRID_HEIGHT = RESOLUTION.height()/ENEMY_SIZE;
    constexpr static float ENEMY_SPEED = 2;
    static int convertPixelToGridPoint(int pixelVal);
    static int convertGridPointToPixel(int gridPointVal);

    constexpr static const int COUNT_OF_ENEMY_ANIM_FRAMES = 2;
    constexpr static const int TIME_OF_ENEMY_FRAME = 250;

    constexpr static const int   MIN_ENEMY_SHOOT_COUNTER = 0.75 * (1000.0f/FPS);
    constexpr static const int   MAX_ENEMY_SHOOT_COUNTER = 1.75 * (1000.0f/FPS);
};

#endif // GAME_H
