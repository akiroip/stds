#include "enemy.h"

enemy::enemy(QGraphicsItem *parent, int img)
{
    QString name;
    switch(img){
    case 0:
        name = ":/images/enemy1.png";
        break;
    case 1:
        name = ":/images/enemy2.png";
        break;
    case 2:
        name = ":/images/enemy3.png";
        break;
    case 3:
        name = ":/images/enemy4.png";
        break;
    }
    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/sounds/gun.wav"));
    sound->setVolume(0.25);

    explosion = new QSoundEffect();
    explosion->setSource(QUrl::fromLocalFile(":/sounds/hit.wav"));
    explosion->setVolume(0.4);

    QPixmap image(name);
    image = image.scaled(QSize(80,80), Qt::KeepAspectRatio);
    setPixmap(image);
    health = 50;
    if(randomBetween(0,1))
       directon *=-1;

    moveTimer = new QTimer();
    connect(moveTimer,SIGNAL(timeout()),this, SLOT(move()));
    moveTimer->start(randomBetween(50,200));

    shooter = new QTimer();
    connect(shooter,SIGNAL(timeout()),this, SLOT(shoot()));
    shooter->start(randomBetween(500,2000));
}

void enemy::move()
{
    if(checkCollisions())
        return;
    if(x() < 20 || x() > 700)
        directon *= -1;
    setX(x() + (10 * directon));
}

void enemy::shoot()
{
    bullet *b = new bullet(this, 180, true);
    b->setPos(x()+37,y()+37);
    scene()->addItem(b);
    sound->setLoopCount(1);
    sound->play();
}

int enemy::randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

bool enemy::checkCollisions()
{
    QList<QGraphicsItem *> collided = collidingItems();
    for(int i = 0; i < collided.size(); ++i){
        if(typeid((*collided[i])) == typeid(bullet)){
            bool enemy = (dynamic_cast<bullet*> (collided[i]))->getIsFromEnemy();
            if(!enemy){
                (dynamic_cast<bullet*> (collided[i]))->getTimer()->stop();
                delete (dynamic_cast<bullet*> (collided[i]));
                if(health < 10){
                    emit healthChanged(100);
                    emit dead(this);
                    return true;
                }
                else{
                    health -= 10;
                    explosion->setLoopCount(1);
                    explosion->play();
                    emit healthChanged(10);
                }
            }
        }
    }
    return false;
}
