#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>
#include "game.h"
#include <QList>
#include <QSoundEffect>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemy(int type = 0, Game::Direction direction = Game::Direction::RIGHT);
    ~Enemy();

    void move();
    void setPosition(int grid_x, int grid_y);
    void setPosition(QPoint grid_point);
    static QList<Enemy*> s_enemyManager;
    static void decrementShootCounter();
    static void tryShoot();
    void makeShoot();
    void hit(int healthPoint = 1);
signals:
    void deadIsActivated();
private slots:
    void updatePixmap();
private:
    void checkCollisionWithSpaceship();

    Game::Direction m_direction;
    QPoint m_srcPoint;
    QTimer m_timer;
    int m_currentFrame;
    QPixmap m_pixmap;
    int m_health;

    static int s_shootCounter;
};

#endif // ENEMY_H
