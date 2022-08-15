#include "spaceship.h"
#include "game.h"
#include <QGraphicsScene>
#include "projectile.h"

Spaceship::Spaceship(const QPixmap &_pixmap)
{
    setPixmap(_pixmap);
}

void Spaceship::moveLeft()
{
    moveBy(-Game::SPACESHIP_SPEED, 0);
    //setPos(x()-Game::SPACESHIP_SPEED, y());
    clampX();
}

void Spaceship::moveRight()
{
    moveBy(Game::SPACESHIP_SPEED, 0);
    clampX();
}

void Spaceship::shootUp()
{
    if(scene())
    {
        Projectile* p = new Projectile(QPixmap(Game::PATH_TO_PROJECTILE_PIXMAP));
        p->setPos(x()+30, y());
        scene()->addItem(p);
    }
}

void Spaceship::clampX()
{
    if(x() < 0)
    {
        setX(0);
    }
    else if(x() + pixmap().width() > Game::RESOLUTION.width())
    {
        setX(Game::RESOLUTION.width() - pixmap().width());
    }
}
