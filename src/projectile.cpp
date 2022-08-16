#include "projectile.h"

#include <QGraphicsScene>


Projectile::Projectile(Game::Projectile type)
{
    m_type = type;
    if(m_type == Game::Projectile::SPACESHIP)
    {
        setPixmap(QPixmap(Game::PATH_TO_PROJECTILE_PIXMAP));
    }
    else
    {
        setPixmap(QPixmap(Game::PATH_TO_ENEMY_PROJECTILE_PIXMAP));
    }

    connect(&m_timer, &QTimer::timeout, this, &Projectile::updatePos);
    m_timer.start(int(1000.0f/Game::FPS));
}

Projectile::~Projectile()
{
    qDebug() << "Projectile Object is Deleted";
}

void Projectile::updatePos()
{
    if(m_type == Game::Projectile::SPACESHIP)
    {
        moveBy(0, -Game::SPACESHIP_PROJECTILE_SPEED);
        if(y() + pixmap().height() < 0)
        {
            if(scene())
            {
                scene()->removeItem(this);
                delete this;
            }
        }
    }
    else if(m_type == Game::Projectile::ENEMY)
    {
        moveBy(0, +Game::SPACESHIP_PROJECTILE_SPEED);
        if(y() > Game::RESOLUTION.height())
        {
            if(scene())
            {
                scene()->removeItem(this);
                delete this;
            }
        }
    }

}
