#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include "game.h"

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Projectile(Game::Projectile type);
    ~Projectile();
private slots:
    void updatePos();

signals:
private:
    QTimer m_timer;
    Game::Projectile m_type;

    bool collideWithSpaceship();
    bool collideWithEnemy();
};

#endif // PROJECTILE_H
