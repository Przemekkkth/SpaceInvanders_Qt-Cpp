#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>
#include "game.h"

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemy(int type = 0, Game::Direction direction = Game::Direction::RIGHT);

    void move();
    void setPosition(int grid_x, int grid_y);
    void setPosition(QPoint grid_point);
signals:

private slots:
    void updatePixmap();
private:
    Game::Direction m_direcion;
    QPoint m_srcPoint;
    QTimer m_timer;
    int m_currentFrame;
    QPixmap m_pixmap;
};

#endif // ENEMY_H
