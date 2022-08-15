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
signals:

private:
    void clampX();
};

#endif // SPACESHIP_H
