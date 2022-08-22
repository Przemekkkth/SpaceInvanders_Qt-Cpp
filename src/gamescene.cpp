#include "gamescene.h"
#include "game.h"
#include <QKeyEvent>
#include <QDir>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_spaceship(),
      m_leftArrowPressed(false), m_rightArrowPressed(false), m_spacebarPressed(false), m_loopTime(0.0f),
      m_deltaTime(0.0f), m_loopSpeed(int(1000.0f/Game::FPS)), m_level(this)
{
    m_enemyDeadSFX.setSource(Game::InvaderKilledSFX);
    srand(time(0));
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    m_bgItem = new QGraphicsPixmapItem(QPixmap(Game::PATH_TO_BG_PIXMAP));
    m_bgItem->setZValue(-1);
    addItem(m_bgItem);

    m_level.loadLevel(":/res/level/level1.lvl");


    addItem(&m_spaceship);
    m_spaceship.setPos(Game::RESOLUTION.width()/2-m_spaceship.pixmap().width()/2,400);

    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/Game::FPS));
    m_elapsedTimer.start();
}

void GameScene::playEnemyDeadSFX()
{
    m_enemyDeadSFX.play();
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

        checkNextLevelActivated();
        //qDebug() << "Enemy count " << Enemy::s_enemyManager.size();
    }
    else if(Game::SPACESHIP_DEAD)
    {
        m_level.drawGameOverText();
    }
}

void GameScene::checkNextLevelActivated()
{
    if(Enemy::s_enemyManager.isEmpty())
    {
        //Game::SPACESHIP_DEAD = true;
        m_level.incrementCurrentLevel();
        m_level.loadLevel(Game::PATH_TO_LEVELS[m_level.currentLevel()]);
        Game::SPACESHIP_DEAD = false;
    }
}

void GameScene::saveScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
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
        if(event->key() == Qt::Key_N && Game::SPACESHIP_DEAD)
        {
           Game::SPACESHIP_DEAD = false;
           clear();
           m_bgItem = new QGraphicsPixmapItem(QPixmap(Game::PATH_TO_BG_PIXMAP));
           m_bgItem->setZValue(-1);
           addItem(m_bgItem);

           m_level.incrementCurrentLevel();
           m_level.loadLevel(Game::PATH_TO_LEVELS[m_level.currentLevel()]);

           addItem(&m_spaceship);
           m_spaceship.setPos(Game::RESOLUTION.width()/2-m_spaceship.pixmap().width()/2,400);
        }
        if(event->key() == Qt::Key_Z)
        {
           // saveScene();
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
