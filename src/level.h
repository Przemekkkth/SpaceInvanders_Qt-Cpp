#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QFont>

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QGraphicsScene* scene);
    void loadLevel(QString pathToFile);
    void reset();
    void drawGameOverText();
signals:

private:
    void initTextItem();
    QString m_currentPathLevel, m_fontFamily;
    QGraphicsScene* m_scene;
    QGraphicsSimpleTextItem *m_gameOverText, *m_restartTextItem, *m_nextTextItem;
    QFont m_mainTextFont, m_subTextFont;
};

#endif // LEVEL_H
