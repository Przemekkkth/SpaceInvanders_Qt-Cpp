#include "gamescene.h"
#include "game.h"
#include <QKeyEvent>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_spaceship(QPixmap(Game::PATH_TO_SPACESHIP_PIXMAP)),
      m_leftArrowPressed(false), m_rightArrowPressed(false), m_spacebarPressed(false), m_loopTime(0.0f),
      m_deltaTime(0.0f), m_loopSpeed(int(1000.0f/Game::FPS))
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    m_bgItem = new QGraphicsPixmapItem(QPixmap(Game::PATH_TO_BG_PIXMAP));
    m_bgItem->setZValue(-1);
    addItem(m_bgItem);

    addItem(&m_enemy);

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
    if( m_loopTime > m_loopSpeed)
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
        m_enemy.move();
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
