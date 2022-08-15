#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Projectile(const QPixmap& _pixmap);
    ~Projectile();
private slots:
    void updatePos();

signals:
private:
QTimer m_timer;
};

#endif // PROJECTILE_H
