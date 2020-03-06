#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QSet>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QtMath>

class bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    bullet(QGraphicsItem *parent = nullptr, qreal angle = 0.0, bool type = false);
    QTimer *getTimer() const;
    bool getIsFromEnemy() const;
    enum { Type = UserType + 1 };
    int type() const { return Type; }

public slots:
    void move();

private:
    bool isFromEnemy;
    QTimer *timer;
    QPixmap *shot;
    qreal xSpeed = 0;
    qreal ySpeed = 0;
};

#endif // BULLET_H
