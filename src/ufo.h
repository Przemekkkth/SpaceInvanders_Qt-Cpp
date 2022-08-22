#ifndef UFO_H
#define UFO_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>
#include "game.h"

class Ufo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Ufo();
    ~Ufo();
    void move();
    void setPosition(int grid_x, int grid_y);
    void setPosition(QPoint grid_point);
    void hit(int healthPoint = 1);
    static QList<Ufo*> s_ufoManager;
signals:
    void deadIsActivated();
private slots:
    void updatePixmap();

private:
    Game::Direction m_direction;
    int m_currentFrame;
    QPixmap m_pixmap;
    QTimer m_timer;
    QPoint m_srcPoint;
    int m_health;
};

#endif // UFO_H
