#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QGraphicsScene>

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QGraphicsScene* scene);
    void loadLevel(QString pathToFile);
signals:

private:
    QGraphicsScene* m_scene;
};

#endif // LEVEL_H
