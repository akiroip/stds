#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QSet>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QSoundEffect>
#include "bullet.h"

class player: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    player(QGraphicsItem *parent = nullptr);
    bool sceneEvent(QEvent *event);
    enum { Type = UserType + 3 };
    int type() const { return Type; }

    int getHealth() const;
    void setHealth(int value);

    int getHeight() const;
    void setHeight(int value);

    int getWidth() const;
    void setWidth(int value);

signals:
    void dead();
    void healthChanged(int health);

public slots:
    void checkCollisions();

private:
    QSet<int> pressedKeys;
    QTimer *timer, *hits;
    QSoundEffect *sound, *explosion;
    int health;
    int height;
    int width;
};

#endif // PLAYER_H
