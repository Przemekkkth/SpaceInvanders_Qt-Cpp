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
    void reset();
signals:

private:
    QString m_currentPathLevel;
    QGraphicsScene* m_scene;
};

#endif // LEVEL_H
