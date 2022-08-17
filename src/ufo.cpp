#include "ufo.h"


Ufo::Ufo()
    : QGraphicsPixmapItem(Game::PATH_TO_UFO_PIXMAP), m_currentFrame(0)
{
    m_direction = Game::Direction::RIGHT;
    m_pixmap = pixmap();

    connect(&m_timer, &QTimer::timeout, this, &Ufo::updatePixmap);
    m_timer.start(Game::TIME_OF_ENEMY_FRAME);
}

void Ufo::move()
{
    if(m_direction == Game::Direction::RIGHT)
    {
        moveBy(Game::ENEMY_SPEED, 0);
        m_srcPoint = QPoint( (Game::GRID_WIDTH-1)*Game::GRID_SIZE, y());
    }
    else if(m_direction == Game::Direction::LEFT)
    {
        moveBy(-Game::ENEMY_SPEED, 0);
        m_srcPoint = QPoint( 0, y());
    }
    else if(m_direction == Game::Direction::DOWN)
    {
        moveBy(0, Game::ENEMY_SPEED);
        m_srcPoint = QPoint( x(), Game::convertPixelToGridPoint(y()) * Game::GRID_SIZE);
    }

    if(pos().toPoint() == m_srcPoint)
    {
        if(y() < 0)
        {
            if(m_direction == Game::Direction::LEFT || m_direction == Game::Direction::RIGHT)
            {
                m_direction = Game::Direction::DOWN;
            }
            else if(m_direction == Game::Direction::DOWN)
            {
                if(x() == 0)
                {
                    m_direction = Game::Direction::RIGHT;
                }
                else
                {
                    m_direction = Game::Direction::LEFT;
                }
            }
        }
        else
        {
            if(m_direction == Game::Direction::LEFT)
            {
                m_direction = Game::Direction::RIGHT;
            }
            else
            {
                m_direction = Game::Direction::LEFT;

            }
        }

    }
    if(x() + boundingRect().width() > Game::RESOLUTION.width())
    {
        m_direction = Game::Direction::LEFT;
    }
    if(x() < 0)
    {
        m_direction = Game::Direction::RIGHT;

    }
}

void Ufo::setPosition(int grid_x, int grid_y)
{
    int x = Game::convertGridPointToPixel(grid_x);
    int y = Game::convertGridPointToPixel(grid_y);
    setPos(x, y);
}

void Ufo::setPosition(QPoint grid_point)
{
    setPosition(grid_point.x(), grid_point.y());
}

void Ufo::updatePixmap()
{
    m_currentFrame++;
    m_currentFrame %= Game::COUNT_OF_UFO_ANIM_FRAMES;
    setPixmap(m_pixmap.copy(m_currentFrame * Game::UFO_SIZE, 0, Game::UFO_SIZE, Game::UFO_SIZE));
}
