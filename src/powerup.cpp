#include "powerup.h"
#include <QGraphicsScene>

PowerUp::PowerUp()
{
    int n = rand() % Game::COUNT_OF_POWER_UP_TYPE;
    if(n == 0)
    {
        m_type = Game::PowerUpType::SHIELD;
    }
    else if(n == 1)
    {
        m_type = Game::PowerUpType::SUPER_PROJECTILE;
    }
    else
    {
        m_type = Game::PowerUpType::TRIPLE_PROJECTILE;
    }

    setPixmap(QPixmap(Game::PATH_TO_POWERUP_PIXMAP).copy( n * Game::POWER_UP_SIZE, 0, Game::POWER_UP_SIZE, Game::POWER_UP_SIZE));
    connect(&m_timer, &QTimer::timeout, this, &PowerUp::updatePos);
    m_timer.start(int(1000.0f/Game::FPS));
}

PowerUp::~PowerUp()
{
    qDebug() << "~PowerUp";
}

Game::PowerUpType PowerUp::powerUpType() const
{
    return m_type;
}

void PowerUp::updatePos()
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
