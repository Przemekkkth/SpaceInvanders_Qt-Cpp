#include "spaceship.h"
#include "game.h"
#include <QGraphicsScene>
#include "projectile.h"

Spaceship::Spaceship(const QPixmap &_pixmap)
    : m_shoutCounter(0)
{
    setPixmap(_pixmap);
    m_health = 999;
}

void Spaceship::moveLeft()
{
    moveBy(-Game::SPACESHIP_SPEED, 0);
    clampX();
}

void Spaceship::moveRight()
{
    moveBy(Game::SPACESHIP_SPEED, 0);
    clampX();
}

void Spaceship::shootUp()
{
    if(m_shoutCounter == 0)
    {
        m_shoutCounter = Game::SPACESHIP_SHOOT_COUNTER;
        if(scene())
        {
            Projectile* p = new Projectile(Game::Projectile::SPACESHIP);
            p->setPos(x()+30, y());
            scene()->addItem(p);
        }
    }

}

void Spaceship::decrementShoutCounter()
{
    m_shoutCounter--;
    if(m_shoutCounter < 0)
    {
        m_shoutCounter = 0;
    }
}

void Spaceship::hit(int healthPoint)
{
    m_health -= healthPoint;
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
