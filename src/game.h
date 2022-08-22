#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QString>
#include <QPoint>
#include <QColor>
#include <QUrl>

class Game
{
public:
    Game();

    //Utilities
    constexpr static const QSize RESOLUTION = QSize(640, 480);
    constexpr static const int FPS = 60;
    enum class Direction{
        NONE = 0, LEFT, RIGHT, DOWN
    };
    constexpr static const int GRID_SIZE = 32;
    constexpr static const int GRID_WIDTH = RESOLUTION.width()/GRID_SIZE;
    constexpr static const int GRID_HEIGHT = RESOLUTION.height()/GRID_SIZE;
    static int convertPixelToGridPoint(int pixelVal);
    static int convertGridPointToPixel(int gridPointVal);
    static const QStringList PATH_TO_LEVELS;

    //Sprite
    static const QString PATH_TO_SPACESHIP_PIXMAP;
    static const QString PATH_TO_PROJECTILE_PIXMAP;
    static const QString PATH_TO_ENEMY_PROJECTILE_PIXMAP;
    static const QString PATH_TO_BG_PIXMAP;
    static const QString PATH_TO_ENEMIES_PIXMAP;
    static const QString PATH_TO_EXPLOSION_PIXMAP;
    static const QString PATH_TO_UFO_PIXMAP;
    static const QString PATH_TO_POWERUP_PIXMAP;
    static const QString PATH_TO_SPACESHIP_SPRITE_PIXMAP;

    //Font
    static const QString PATH_TO_FONT;
    constexpr static const QColor FONT_COLOR = QColor(255, 255, 255);

    //SFX
    static const QUrl ExplosionSFX;
    static const QUrl InvaderKilledSFX;
    static const QUrl ShootSFX;


    //Spaceship
    constexpr static const float SPACESHIP_SPEED = 4.f;
    constexpr static const float SPACESHIP_PROJECTILE_SPEED = 4.f;
    constexpr static const int   SPACESHIP_SHOOT_COUNTER = 33;
    enum class SpaceshipStatus{
        NORMAL, SHIELD, TRIPLE_SHOOT, SUPER_SHOOT
    };
    constexpr static const int SPACESHIP_SIZE = 64;
    constexpr static const QPoint SPACESHIP_NORMAL = QPoint(0,0);
    constexpr static const QPoint SPACESHIP_TRIPLE_PROJECTILE = QPoint(64, 0);
    constexpr static const QPoint SPACESHIP_SHIELD = QPoint(128, 0);
    constexpr static const QPoint SPACESHIP_SUPER_PROJECTILE = QPoint(192, 0);
    static bool SPACESHIP_DEAD;

    //Projectile
    enum class Projectile{
        SPACESHIP, ENEMY
    };

    //Enemy
    constexpr static const int ENEMY_SIZE = 32;
    constexpr static float ENEMY_SPEED = 2;
    constexpr static const int COUNT_OF_ENEMY_ANIM_FRAMES = 2;
    constexpr static const int TIME_OF_ENEMY_FRAME = 250;
    static int   MIN_ENEMY_SHOOT_COUNTER;
    static int   MAX_ENEMY_SHOOT_COUNTER;

    //ExplosionAnim
    constexpr static const int COUNT_OF_EXPLOSION_ANIM_FRAMES = 11;
    constexpr static const int TIME_OF_EXPLOSION_ANIM_FRAME = 50;

    //UFO
    constexpr static const int UFO_SIZE = GRID_SIZE;
    constexpr static const int COUNT_OF_UFO_ANIM_FRAMES = 4;
    constexpr static const int TIME_OF_UFO_FRAME = 250;
    constexpr static float UFO_SPEED = 3.5f;

    //PowerUp
    constexpr static const int POWER_UP_SIZE = GRID_SIZE/2;
    constexpr static const int COUNT_OF_POWER_UP_TYPE = 3;
    constexpr static const float POWER_UP_FALL_DOWN_SPEED = 1.5f;
    enum class PowerUpType{
        SHIELD = 0, TRIPLE_PROJECTILE, SUPER_PROJECTILE
    };
    constexpr static const int TIME_OF_POWER_UP_WORKS = 3000;//ms
};

#endif // GAME_H
