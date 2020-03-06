#include "player.h"

player::player(QGraphicsItem *parent)
{
    QPixmap ship(":/images/playerShip.png");
    height = 80;
    width = 80;
    ship = ship.scaled(QSize(getWidth(),getHeight()), Qt::KeepAspectRatio);
    setPixmap(ship);
    health = 100;

    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/sounds/laser.wav"));
    sound->setVolume(0.25);

    explosion = new QSoundEffect();
    explosion->setSource(QUrl::fromLocalFile(":/sounds/hit.wav"));
    explosion->setVolume(0.4);


    timer = new QTimer();
    timer->setSingleShot(true);

    hits = new QTimer();
    connect(hits,SIGNAL(timeout()),this, SLOT(checkCollisions()));
    hits->start(50);
}

bool player::sceneEvent(QEvent *event)
{
    if(event->type()==QEvent::KeyPress) {
        pressedKeys += ((QKeyEvent*)event)->key();
        if(pressedKeys.contains(Qt::Key_Space)){
            if(!timer->isActive()){
                bullet *b = new bullet(this, 0, false);
                sound->setLoopCount(1);
                sound->play();
                b->setPos(x()+36,y()-37);
                scene()->addItem(b);
                qreal speed = 3000/qLn(health*1.2);
                //qDebug() << speed;
                timer->start(speed);
            }
        }
        if(pressedKeys.contains(Qt::Key_Left)){
            if(x() - 10 >= 0)
                setPos(x() - 10, y());
        }
        else if(pressedKeys.contains(Qt::Key_Right)){
            if(x() + 10 + getWidth() <= scene()->width())
                setPos(x() + 10, y());
        }
    }
    else if(event->type()==QEvent::KeyRelease){
        if(((QKeyEvent*)event)->key() == Qt::Key_Space){
            if(pressedKeys.contains(Qt::Key_Left)){
                if(x() - 10 >= 0)
                    setPos(x() - 10, y());
            }
            else if(pressedKeys.contains(Qt::Key_Right)){
                if(x() + 10 + getWidth() <= scene()->width())
                    setPos(x() + 10, y());
            }
        }
        pressedKeys -= ((QKeyEvent*)event)->key();
   }
   return false;
}

int player::getHealth() const
{
    return health;
}

void player::setHealth(int value)
{
    health = value;
}

int player::getHeight() const
{
    return height;
}

void player::setHeight(int value)
{
    height = value;
}

int player::getWidth() const
{
    return width;
}

void player::setWidth(int value)
{
    width = value;
}

void player::checkCollisions()
{
    QList<QGraphicsItem *> collided = collidingItems();
    for(int i = 0; i < collided.size(); ++i){
        if(typeid((*collided[i])) == typeid(bullet)){
            bool enemy = (dynamic_cast<bullet*> (collided[i]))->getIsFromEnemy();
            if(enemy){
                (dynamic_cast<bullet*> (collided[i]))->getTimer()->stop();
                delete (dynamic_cast<bullet*> (collided[i]));
                if(health < 9){
                    emit healthChanged(0);
                    emit dead();
                }
                else{
                    health -= 9;
                    explosion->setLoopCount(1);
                    explosion->play();
                    emit healthChanged(health);
                }
            }
        }
    }
}
