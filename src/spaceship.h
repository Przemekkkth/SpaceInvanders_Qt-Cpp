#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Spaceship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Spaceship(const QPixmap &_pixmap);
    void moveLeft();
    void moveRight();
    void shootUp();
    void decrementShoutCounter();
    void hit();
signals:

private:
    void clampX();
    int m_shoutCounter;
    int m_health;
};

#endif // SPACESHIP_H
