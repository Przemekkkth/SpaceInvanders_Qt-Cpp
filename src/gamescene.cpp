#include "gamescene.h"
#include "game.h"
#include <QKeyEvent>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_spaceship(),
      m_leftArrowPressed(false), m_rightArrowPressed(false), m_spacebarPressed(false), m_loopTime(0.0f),
      m_deltaTime(0.0f), m_loopSpeed(int(1000.0f/Game::FPS)), m_level(this)
{
    srand(time(0));
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    m_bgItem = new QGraphicsPixmapItem(QPixmap(Game::PATH_TO_BG_PIXMAP));
    m_bgItem->setZValue(-1);
    addItem(m_bgItem);

    m_level.loadLevel(":/res/level/level2.lvl");
    //    m_enemy1 = new Enemy(0);
    //    addItem(m_enemy1);
    //    m_enemy2 = new Enemy(1, Game::Direction::LEFT);
    //    m_enemy2->setPosition(2,2);
    //    addItem(m_enemy2);
    //    m_enemy3 = new Enemy(2, Game::Direction::LEFT);
    //    m_enemy3->setPosition(3,2);
    //    addItem(m_enemy3);
    //    m_enemy4 = new Enemy(3, Game::Direction::DOWN);
    //    m_enemy4->setPosition(3,4);
    //    addItem(m_enemy4);

    //    m_enemy5 = new Enemy(4);
    //    m_enemy5->setPosition(4,4);
    //    addItem(m_enemy5);

    m_ufo = new Ufo();
    m_ufo->setPosition(0,9);
    addItem(m_ufo);

    addItem(&m_spaceship);
    m_spaceship.setPos(Game::RESOLUTION.width()/2-m_spaceship.pixmap().width()/2,400);

    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/Game::FPS));
    m_elapsedTimer.start();

}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed && !Game::SPACESHIP_DEAD)
    {
        m_loopTime -= m_loopSpeed;
        if(m_leftArrowPressed)
        {
            m_spaceship.moveLeft();
        }
        else if(m_rightArrowPressed)
        {
            m_spaceship.moveRight();
        }
        if(m_spacebarPressed)
        {
            m_spaceship.shootUp();
        }
        m_spaceship.decrementShoutCounter();

        for(int idx = Enemy::s_enemyManager.size()-1; idx >= 0; --idx)
        {
            Enemy::s_enemyManager.at(idx)->move();
        }
        Enemy::tryShoot();

        for(int idx = Ufo::s_ufoManager.size()-1; idx >= 0; --idx)
        {
            Ufo::s_ufoManager.at(idx)->move();
        }

    }
    else if(Game::SPACESHIP_DEAD)
    {
        m_level.drawGameOverText();
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key())
    {
        switch (event->key())
        {
        case Qt::Key_Left:
        {
            m_leftArrowPressed = true;
        }
            break;
        case Qt::Key_Right:
        {
            m_rightArrowPressed = true;
        }
            break;
        case Qt::Key_Space:
        {
            m_spacebarPressed = true;
        }
            break;
        }
    }
    if(!event->isAutoRepeat())
    {
        if(event->key() == Qt::Key_R && Game::SPACESHIP_DEAD)
        {
           Game::SPACESHIP_DEAD = false;
           clear();
           m_bgItem = new QGraphicsPixmapItem(QPixmap(Game::PATH_TO_BG_PIXMAP));
           m_bgItem->setZValue(-1);
           addItem(m_bgItem);
           m_level.reset();
           addItem(&m_spaceship);
           m_spaceship.setPos(Game::RESOLUTION.width()/2-m_spaceship.pixmap().width()/2,400);
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key())
    {
        switch (event->key())
        {
        case Qt::Key_Left:
        {
            m_leftArrowPressed = false;
        }
            break;
        case Qt::Key_Right:
        {
            m_rightArrowPressed = false;
        }
            break;
        case Qt::Key_Space:
        {
            m_spacebarPressed = false;
        }
            break;
        }
    }
    QGraphicsScene::keyReleaseEvent(event);
}
