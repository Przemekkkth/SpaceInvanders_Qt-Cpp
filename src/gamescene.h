#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include "level.h"
#include "spaceship.h"
#include "enemy.h"
#include "ufo.h"

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
    Enemy *m_enemy1, *m_enemy2, *m_enemy3, *m_enemy4, *m_enemy5;
    Ufo *m_ufo;
    bool m_leftArrowPressed, m_rightArrowPressed, m_spacebarPressed;
    // QGraphicsScene interface
    float m_loopTime, m_deltaTime;
    const float m_loopSpeed;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    QGraphicsPixmapItem *m_bgItem;
    Level m_level;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
