#include "spaceship.h"
#include "game.h"
#include <QGraphicsScene>
#include "projectile.h"

Spaceship::Spaceship()
    : QGraphicsPixmapItem(QPixmap(Game::PATH_TO_SPACESHIP_SPRITE_PIXMAP)), m_shoutCounter(0)
{
    m_pixmap = pixmap();
    setPixmap(m_pixmap.copy(Game::SPACESHIP_NORMAL.x(), Game::SPACESHIP_NORMAL.y(), Game::SPACESHIP_SIZE, Game::SPACESHIP_SIZE));
    m_health = 999;

    m_status = Game::SpaceshipStatus::NORMAL;
    connect(&m_timer, &QTimer::timeout, this, &Spaceship::updatePixmap);
    m_timer.start(1000);
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

void Spaceship::addShield()
{
    m_status = Game::SpaceshipStatus::SHIELD;
}

void Spaceship::addTripleShoot()
{
    m_status = Game::SpaceshipStatus::TRIPLE_SHOOT;
}

void Spaceship::addSuperShoot()
{
    m_status = Game::SpaceshipStatus::SUPER_SHOOT;
}

void Spaceship::updatePixmap()
{
    if(m_status == Game::SpaceshipStatus::SHIELD)
    {
        setPixmap(m_pixmap.copy(Game::SPACESHIP_SHIELD.x(), Game::SPACESHIP_SHIELD.y(), Game::SPACESHIP_SIZE, Game::SPACESHIP_SIZE));
    }
    else if(m_status == Game::SpaceshipStatus::SUPER_SHOOT)
    {
        setPixmap(m_pixmap.copy(Game::SPACESHIP_SUPER_PROJECTILE.x(), Game::SPACESHIP_SUPER_PROJECTILE.y(), Game::SPACESHIP_SIZE, Game::SPACESHIP_SIZE));
    }
    else if(m_status == Game::SpaceshipStatus::TRIPLE_SHOOT)
    {
        setPixmap(m_pixmap.copy(Game::SPACESHIP_TRIPLE_PROJECTILE.x(), Game::SPACESHIP_TRIPLE_PROJECTILE.y(), Game::SPACESHIP_SIZE, Game::SPACESHIP_SIZE));
    }
    else
    {
        setPixmap(m_pixmap.copy(Game::SPACESHIP_NORMAL.x(), Game::SPACESHIP_NORMAL.y(), Game::SPACESHIP_SIZE, Game::SPACESHIP_SIZE));
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
