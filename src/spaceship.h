#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include "game.h"
#include <QSoundEffect>

class Spaceship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Spaceship();
    void moveLeft();
    void moveRight();
    void shootUp();
    void decrementShoutCounter();
    void hit(int healthPoint = 1);
    void addShield();
    void addTripleShoot();
    void addSuperShoot();
    void backToNormalStatus();
signals:
private slots:
    void updatePixmap();

private:
    void clampX();
    int m_shoutCounter;
    int m_health;
    Game::SpaceshipStatus m_status;
    QTimer m_timer;
    QPixmap m_pixmap;
    QSoundEffect m_explosionSFX;
    QSoundEffect m_shootSFX;
};

#endif // SPACESHIP_H
