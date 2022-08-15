#include "projectile.h"
#include "game.h"
#include <QGraphicsScene>


Projectile::Projectile(const QPixmap& _pixmap)
{
    setPixmap(_pixmap);
    connect(&m_timer, &QTimer::timeout, this, &Projectile::updatePos);
    m_timer.start(int(1000.0f/Game::FPS));
}

Projectile::~Projectile()
{
    qDebug() << "Projectile Object is Deleted";
}

void Projectile::updatePos()
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
