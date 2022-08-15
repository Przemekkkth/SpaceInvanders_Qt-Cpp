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
    static const QString PATH_TO_BG_PIXMAP;
    constexpr static const int FPS = 60;
    constexpr static const float SPACESHIP_SPEED = 4.f;
    constexpr static const float SPACESHIP_PROJECTILE_SPEED = 4.f;
    constexpr static const int   SPACESHIP_SHOOT_COUNTER = 2 * (1000.0f/FPS);
};

#endif // GAME_H
