#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include "spaceship.h"


class QGraphicsPixmapItem;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private slots:
    void loop();

private:
    Spaceship m_spaceship;

    bool m_leftArrowPressed, m_rightArrowPressed, m_spacebarPressed;
    // QGraphicsScene interface
    float m_loopTime, m_deltaTime;
    const float m_loopSpeed;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;

    QGraphicsPixmapItem *m_bgItem;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
