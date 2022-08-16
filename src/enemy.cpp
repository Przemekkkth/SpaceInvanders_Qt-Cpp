#include "enemy.h"

Enemy::Enemy(int type)
    : QGraphicsPixmapItem(QPixmap(Game::PATH_TO_ENEMIES_PIXMAP)), m_currentFrame(0)
{
    m_direcion = Game::Direction::RIGHT;
    m_pixmap = pixmap().copy(type * Game::ENEMY_SIZE * Game::COUNT_OF_ENEMY_ANIM_FRAMES, 0, Game::COUNT_OF_ENEMY_ANIM_FRAMES*Game::ENEMY_SIZE, Game::ENEMY_SIZE);
    setPixmap(m_pixmap.copy(0,0, Game::ENEMY_SIZE, Game::ENEMY_SIZE));
    connect(&m_timer, &QTimer::timeout, this, &Enemy::updatePixmap);
    m_timer.start(Game::TIME_OF_ENEMY_FRAME);
}

void Enemy::move()
{
    if(m_direcion == Game::Direction::RIGHT)
    {
        moveBy(Game::ENEMY_SPEED, 0);
        m_srcPoint = QPoint( (Game::GRID_WIDTH-1)*Game::GRID_SIZE, y());
    }
    else if(m_direcion == Game::Direction::LEFT)
    {
        moveBy(-Game::ENEMY_SPEED, 0);
        m_srcPoint = QPoint( 0, y());
    }
    else if(m_direcion == Game::Direction::DOWN)
    {
        moveBy(0, Game::ENEMY_SPEED);
        m_srcPoint = QPoint( x(), Game::convertPixelToGridPoint(y()) * Game::GRID_SIZE);
    }

    if(pos().toPoint() == m_srcPoint)
    {
        if(m_direcion == Game::Direction::LEFT || m_direcion == Game::Direction::RIGHT)
        {
            m_direcion = Game::Direction::DOWN;
        }
        else if(m_direcion == Game::Direction::DOWN)
        {
            if(x() == 0)
            {
                m_direcion = Game::Direction::RIGHT;
            }
            else
            {
                m_direcion = Game::Direction::LEFT;
            }
        }
    }
}

void Enemy::updatePixmap()
{
    m_currentFrame++;
    m_currentFrame %= Game::COUNT_OF_ENEMY_ANIM_FRAMES;
    setPixmap(m_pixmap.copy(m_currentFrame * Game::ENEMY_SIZE, 0, Game::ENEMY_SIZE, Game::ENEMY_SIZE));
}