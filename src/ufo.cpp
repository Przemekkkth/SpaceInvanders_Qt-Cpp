#include "ufo.h"
#include "animation.h"
#include "powerup.h"
#include <QGraphicsScene>

QList<Ufo*> Ufo::s_ufoManager;

Ufo::Ufo()
    : QGraphicsPixmapItem(Game::PATH_TO_UFO_PIXMAP), m_currentFrame(0), m_health(1)
{
    m_direction = Game::Direction::RIGHT;
    m_pixmap = pixmap();
    setPixmap(m_pixmap.copy(m_currentFrame * Game::UFO_SIZE, 0, Game::UFO_SIZE, Game::UFO_SIZE));

    connect(&m_timer, &QTimer::timeout, this, &Ufo::updatePixmap);
    m_timer.start(Game::TIME_OF_ENEMY_FRAME);

    s_ufoManager.push_back(this);
}

Ufo::~Ufo()
{
    s_ufoManager.removeOne(this);
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

void Ufo::hit(int healthPoint)
{
    m_health -= healthPoint;
    if(m_health <= 0)
    {
        if(scene())
        {
            Animation *explosionAnim = new Animation(QPixmap(Game::PATH_TO_EXPLOSION_PIXMAP), QSize(Game::ENEMY_SIZE, Game::ENEMY_SIZE), Game::COUNT_OF_EXPLOSION_ANIM_FRAMES, Game::TIME_OF_EXPLOSION_ANIM_FRAME);
            explosionAnim->setPos(pos());
            scene()->addItem(explosionAnim);

            PowerUp *powerUp = new PowerUp();
            powerUp->setPos(x() + powerUp->boundingRect().width()/2, y() - powerUp->boundingRect().height()/2);
            scene()->addItem(powerUp);

            emit deadIsActivated();

            scene()->removeItem(this);
            delete this;
        }
    }
}

void Ufo::updatePixmap()
{
    m_currentFrame++;
    m_currentFrame %= Game::COUNT_OF_UFO_ANIM_FRAMES;
    setPixmap(m_pixmap.copy(m_currentFrame * Game::UFO_SIZE, 0, Game::UFO_SIZE, Game::UFO_SIZE));
}
