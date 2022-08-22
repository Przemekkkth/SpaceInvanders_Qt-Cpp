#include "enemy.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include "animation.h"
#include "projectile.h"
#include "spaceship.h"

QList<Enemy*> Enemy::s_enemyManager;
int Enemy::s_shootCounter;

Enemy::Enemy(int type, Game::Direction direction)
    : QGraphicsPixmapItem(QPixmap(Game::PATH_TO_ENEMIES_PIXMAP)), m_currentFrame(0)
{
    m_health = type+1; //1-5
    if(direction == Game::Direction::RIGHT)
    {
        m_direction = Game::Direction::RIGHT;
    }
    else
    {
        m_direction = Game::Direction::LEFT;
    }

    m_pixmap = pixmap().copy(type * Game::ENEMY_SIZE * Game::COUNT_OF_ENEMY_ANIM_FRAMES, 0, Game::COUNT_OF_ENEMY_ANIM_FRAMES*Game::ENEMY_SIZE, Game::ENEMY_SIZE);
    setPixmap(m_pixmap.copy(0,0, Game::ENEMY_SIZE, Game::ENEMY_SIZE));
    connect(&m_timer, &QTimer::timeout, this, &Enemy::updatePixmap);
    m_timer.start(Game::TIME_OF_ENEMY_FRAME);

    s_enemyManager.push_back(this);
}

Enemy::~Enemy()
{
    s_enemyManager.removeOne(this);
}

void Enemy::move()
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

    if(x() + boundingRect().width() > Game::RESOLUTION.width())
    {
        m_direction = Game::Direction::LEFT;
    }
    if(x() < 0)
    {
        m_direction = Game::Direction::RIGHT;

    }

    checkCollisionWithSpaceship();
}

void Enemy::setPosition(int grid_x, int grid_y)
{
    int x = Game::convertGridPointToPixel(grid_x);
    int y = Game::convertGridPointToPixel(grid_y);
    setPos(x, y);
}

void Enemy::setPosition(QPoint grid_point)
{
    setPosition(grid_point.x(), grid_point.y());
}

void Enemy::decrementShootCounter()
{
    s_shootCounter--;
    if(s_shootCounter < 0)
    {
        s_shootCounter = 0;
    }
}

void Enemy::tryShoot()
{
    decrementShootCounter();
    if(s_shootCounter == 0 && s_enemyManager.size())
    {
        s_shootCounter = QRandomGenerator::global()->bounded(Game::MIN_ENEMY_SHOOT_COUNTER, Game::MAX_ENEMY_SHOOT_COUNTER);
        int idx = rand() % s_enemyManager.size();
        s_enemyManager.at(idx)->makeShoot();
    }
}

void Enemy::makeShoot()
{
    if(scene())
    {
        Projectile* p = new Projectile(Game::Projectile::ENEMY);
        p->setPos(x()+Game::ENEMY_SIZE/2 - p->boundingRect().width()/2, y() + Game::ENEMY_SIZE - p->boundingRect().height()/2);
        scene()->addItem(p);
    }
}

void Enemy::hit(int healthPoint)
{
    m_health -= healthPoint;
    if(m_health <= 0)
    {
        if(scene())
        {
            Animation *explosionAnim = new Animation(QPixmap(Game::PATH_TO_EXPLOSION_PIXMAP), QSize(Game::ENEMY_SIZE, Game::ENEMY_SIZE), Game::COUNT_OF_EXPLOSION_ANIM_FRAMES, Game::TIME_OF_EXPLOSION_ANIM_FRAME);
            explosionAnim->setPos(pos());
            scene()->addItem(explosionAnim);
            scene()->removeItem(this);
            emit deadIsActivated();
            //connect(&m_soundEffect, &QSoundEffect::)
            delete this;
        }
    }
}

void Enemy::updatePixmap()
{
    m_currentFrame++;
    m_currentFrame %= Game::COUNT_OF_ENEMY_ANIM_FRAMES;
    setPixmap(m_pixmap.copy(m_currentFrame * Game::ENEMY_SIZE, 0, Game::ENEMY_SIZE, Game::ENEMY_SIZE));
}

void Enemy::checkCollisionWithSpaceship()
{
    QList<QGraphicsItem*> collidedList = collidingItems();
    for(int idx = collidedList.size() - 1; idx >= 0; --idx)
    {
        Spaceship* spaceship = dynamic_cast<Spaceship*>(collidedList[idx]);
        if(spaceship)
        {
            spaceship->hit(1000);
            hit(10);
        }
    }
}
