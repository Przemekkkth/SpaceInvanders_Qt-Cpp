#ifndef POWERUP_H
#define POWERUP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "game.h"
#include <QTimer>

class PowerUp : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit PowerUp();
    ~PowerUp();
    Game::PowerUpType powerUpType() const;
private slots:
    void updatePos();

signals:

private:
    void checkCollideWithSpaceship();
    Game::PowerUpType m_type;
    QTimer m_timer;
};

#endif // POWERUP_H
