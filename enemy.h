#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QtMath>
#include <QRandomGenerator>
#include <QDateTime>
#include <QSoundEffect>
#include "bullet.h"

class enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    enemy(QGraphicsItem *parent = nullptr, int img = 0);
    enum { Type = UserType + 2 };
    int type() const { return Type; }

signals:
    void dead(enemy *e);
    void healthChanged(int health);

public slots:
    void move();
    void shoot();

private:
    static int randomBetween(int low, int high);
    bool checkCollisions();
    QTimer *moveTimer, *shooter;
    QSoundEffect *sound, *explosion;
    int health;
    int directon = 1;
};

#endif // ENEMY_H
