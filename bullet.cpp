#include "bullet.h"

bullet::bullet(QGraphicsItem *parent, qreal angle,  bool type)
{
    isFromEnemy = type;
    QTransform transform;
    transform.rotateRadians(qDegreesToRadians(angle));
    if(isFromEnemy)
        shot = new QPixmap(":/images/laserRed.png");
    else
        shot = new QPixmap(":/images/laserGreen.png");
    *shot = shot->transformed(transform);
    *shot = shot->scaled(QSize(30,30), Qt::KeepAspectRatio);
    setPixmap(*shot);

    ySpeed = 10 * qCos(qDegreesToRadians(angle));
    xSpeed = -10 * qSin(qDegreesToRadians(angle));

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));
    timer->start(50);
}

void bullet::move()
{
    if((x() > 0 && x() < 800) && (y() > 0 && y() < 600)){
        setY(y() - ySpeed);
        setX(x() - xSpeed);
    }
    else
        delete this;
}

bool bullet::getIsFromEnemy() const
{
    return isFromEnemy;
}

QTimer *bullet::getTimer() const
{
    return timer;
}
