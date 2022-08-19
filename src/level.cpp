#include "level.h"
#include <QFile>
#include <QTextStream>
#include "enemy.h"
#include "ufo.h"

Level::Level(QGraphicsScene *scene)
{
    m_scene = scene;
}

void Level::loadLevel(QString pathToFile)
{
    QFile file(pathToFile);
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File " << pathToFile << " not exist";
    }
    m_currentPathLevel = pathToFile;
    while(!in.atEnd()) {
        QString line = in.readLine();
        if(line.startsWith("//"))
        {
            continue;
        }
        QStringList data = line.split(";");
        for(int i = 0; i < data.size(); ++i)
        {
            QStringList propertiesOfElement = data.at(i).split(",");
            if(propertiesOfElement.isEmpty())
            {
                continue;
            }
            if(propertiesOfElement.size() != 4)
            {
                qFatal("Invalid file format: Enemy{e0,...e4}|Ufo{u},x,y,direction(-1left.1right);");
            }
            if(propertiesOfElement.at(0) == "e0")
            {
                Enemy* enemy = new Enemy(0, propertiesOfElement.at(3).toInt() == 1 ? Game::Direction::RIGHT : Game::Direction::LEFT);
                enemy->setPosition(propertiesOfElement.at(1).toInt(), propertiesOfElement.at(2).toInt());
                m_scene->addItem(enemy);
            }
            else if(propertiesOfElement.at(0) == "e1")
            {
                Enemy* enemy = new Enemy(1, propertiesOfElement.at(3).toInt() == 1 ? Game::Direction::RIGHT : Game::Direction::LEFT);
                enemy->setPosition(propertiesOfElement.at(1).toInt(), propertiesOfElement.at(2).toInt());
                m_scene->addItem(enemy);
            }
            else if(propertiesOfElement.at(0) == "e2")
            {
                Enemy* enemy = new Enemy(2, propertiesOfElement.at(3).toInt() == 1 ? Game::Direction::RIGHT : Game::Direction::LEFT);
                enemy->setPosition(propertiesOfElement.at(1).toInt(), propertiesOfElement.at(2).toInt());
                m_scene->addItem(enemy);
            }
            else if(propertiesOfElement.at(0) == "e3")
            {
                Enemy* enemy = new Enemy(3, propertiesOfElement.at(3).toInt() == 1 ? Game::Direction::RIGHT : Game::Direction::LEFT);
                enemy->setPosition(propertiesOfElement.at(1).toInt(), propertiesOfElement.at(2).toInt());
                m_scene->addItem(enemy);
            }
            else if(propertiesOfElement.at(0) == "e4")
            {
                Enemy* enemy = new Enemy(4, propertiesOfElement.at(3).toInt() == 1 ? Game::Direction::RIGHT : Game::Direction::LEFT);
                enemy->setPosition(propertiesOfElement.at(1).toInt(), propertiesOfElement.at(2).toInt());
                m_scene->addItem(enemy);
            }
            else if(propertiesOfElement.at(0) == "u")
            {
                Ufo *ufo = new Ufo();
                ufo->setPosition(propertiesOfElement.at(1).toInt(), propertiesOfElement.at(2).toInt());
                m_scene->addItem(ufo);
            }

        }
    }
    file.close();
}

void Level::reset()
{
    loadLevel(m_currentPathLevel);
}
