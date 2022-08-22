#include "spaceship.h"
#include "game.h"
#include "animation.h"
#include <QGraphicsScene>
#include "projectile.h"

Spaceship::Spaceship()
    : QGraphicsPixmapItem(QPixmap(Game::PATH_TO_SPACESHIP_SPRITE_PIXMAP)), m_shoutCounter(0)
{
    m_pixmap = pixmap();
    setPixmap(m_pixmap.copy(Game::SPACESHIP_NORMAL.x(), Game::SPACESHIP_NORMAL.y(), Game::SPACESHIP_SIZE, Game::SPACESHIP_SIZE));
    m_health = 1;

    m_status = Game::SpaceshipStatus::NORMAL;
    connect(&m_timer, &QTimer::timeout, this, &Spaceship::updatePixmap);
    m_timer.start(1000);

    m_explosionSFX.setSource(Game::ExplosionSFX);
    m_shootSFX.setSource(Game::ShootSFX);
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
        m_shootSFX.play();
        if(scene())
        {
            if(m_status == Game::SpaceshipStatus::TRIPLE_SHOOT)
            {
                Projectile* p0 = new Projectile(Game::Projectile::SPACESHIP);
                p0->setPos(x()+30, y()+1);
                scene()->addItem(p0);
                Projectile* p1 = new Projectile(Game::Projectile::SPACESHIP);
                p1->setPos(x()+8, y()+18);
                scene()->addItem(p1);
                Projectile* p2 = new Projectile(Game::Projectile::SPACESHIP);
                p2->setPos(x()+52, y()+18);
                scene()->addItem(p2);
            }
            else if(m_status == Game::SpaceshipStatus::SUPER_SHOOT)
            {
                Projectile* p0 = new Projectile(Game::Projectile::SPACESHIP);
                p0->setPos(x()+30, y()*1);
                scene()->addItem(p0);
                Projectile* p1 = new Projectile(Game::Projectile::SPACESHIP);
                p1->setPos(x()+25, y()+4);
                scene()->addItem(p1);
                Projectile* p2 = new Projectile(Game::Projectile::SPACESHIP);
                p2->setPos(x()+35, y()+4);
                scene()->addItem(p2);
            }
            else
            {
                Projectile* p = new Projectile(Game::Projectile::SPACESHIP);
                p->setPos(x()+30, y());
                scene()->addItem(p);
            }

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
    if(m_status == Game::SpaceshipStatus::SHIELD)
    {
        return;
    }
    m_health -= healthPoint;
    if(m_health <= 0)
    {
        Game::SPACESHIP_DEAD = true;
        if(scene())
        {
            Animation *explosionAnim = new Animation(QPixmap(Game::PATH_TO_EXPLOSION_PIXMAP), QSize(Game::ENEMY_SIZE, Game::ENEMY_SIZE), Game::COUNT_OF_EXPLOSION_ANIM_FRAMES, Game::TIME_OF_EXPLOSION_ANIM_FRAME);
            explosionAnim->setPos(pos());
            scene()->addItem(explosionAnim);
            scene()->removeItem(this);
            m_explosionSFX.play();
            //delete this;
        }
    }
}

void Spaceship::addShield()
{
    m_status = Game::SpaceshipStatus::SHIELD;
    QTimer::singleShot(Game::TIME_OF_POWER_UP_WORKS, [this](){
        backToNormalStatus();
    });
}

void Spaceship::addTripleShoot()
{
    m_status = Game::SpaceshipStatus::TRIPLE_SHOOT;
    QTimer::singleShot(Game::TIME_OF_POWER_UP_WORKS, [this](){
        backToNormalStatus();
    });
}

void Spaceship::addSuperShoot()
{
    m_status = Game::SpaceshipStatus::SUPER_SHOOT;
    QTimer::singleShot(Game::TIME_OF_POWER_UP_WORKS, [this](){
        backToNormalStatus();
    });
}

void Spaceship::backToNormalStatus()
{
    m_status = Game::SpaceshipStatus::NORMAL;
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
