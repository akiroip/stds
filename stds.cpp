#include "stds.h"
#include "ui_stds.h"

stds::stds(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::stds)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(800,600);
    ui->gameView->setRenderHint(QPainter::Antialiasing);
    QPixmap bcg(":/images/background.jpg");
    ui->gameView->setBackgroundBrush(bcg.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,800,600);
    ui->gameView->setScene(scene);

    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/sounds/engine.wav"));
    sound->setLoopCount(QSoundEffect::Infinite);
    sound->setVolume(0.04);

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/intro.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    intro = new QMediaPlayer();
    intro->setPlaylist(playlist);
    intro->setVolume(50);

    explosion = new QSoundEffect();
    explosion->setSource(QUrl::fromLocalFile(":/sounds/explosion.wav"));
    explosion->setVolume(0.3);

    win = new QSoundEffect();
    win->setSource(QUrl::fromLocalFile(":/sounds/win.wav"));
    win->setVolume(0.3);

    lost = new QSoundEffect();
    lost->setSource(QUrl::fromLocalFile(":/sounds/lost.wav"));
    lost->setVolume(0.3);

    startScreen();
}

stds::~stds()
{
    delete ui;
}

void stds::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Space){
        switch(game) {
        case Started:
            newGame();
            break;
        case Playing:
            // ignore
            break;
        case GameOver:
            startScreen();
            break;
        }
    }
}

void stds::playerKilled()
{
    explosion->setLoopCount(1);
    explosion->play();
    scene->clear();
    game = GameOver;
    makeStats();
    playerStats(0);
    scoreStats(0);
    score = 0;
    QGraphicsTextItem *text = new QGraphicsTextItem("Game Over!");
    text->setDefaultTextColor(Qt::darkRed);
    text->setFont(QFont("Helvetica", 50, QFont::Bold));
    text->setPos(200, 250);
    scene->addItem(text);
    sound->stop();
    lost->setLoopCount(1);
    lost->play();
}

void stds::enemyKilled(enemy *e)
{
    delete e;
    count--;
    explosion->setLoopCount(1);
    explosion->play();
    if(count == 0){
        delete ship;
        game = GameOver;
        QGraphicsTextItem *text = new QGraphicsTextItem("You Won!");
        text->setDefaultTextColor(Qt::darkGreen);
        text->setFont(QFont("Helvetica", 50, QFont::Bold));
        text->setPos(200, 250);
        scene->addItem(text);
        sound->stop();
        win->setLoopCount(1);
        win->play();
    }
}

void stds::playerStats(int h)
{
    pstats->setText("Health: "+QString("%1").arg(h, 3, 10, QChar('0')));
}

void stds::scoreStats(int h)
{
    score += h;
    estats->setText("Score: "+QString("%1").arg(score, 5, 10, QChar('0')));
}

void stds::makeStats()
{
    pstats = new QGraphicsSimpleTextItem();
    pstats->setText("Health: 100");
    pstats->setPen(QPen(Qt::white));
    pstats->setFont(QFont("Helvetica", 20, QFont::Bold));
    pstats->setPos(5, 5);
    scene->addItem(pstats);

    estats = new QGraphicsSimpleTextItem();
    estats->setText("Score: "+QString("%1").arg(score, 5, 10, QChar('0')));
    estats->setPen(QPen(Qt::white));
    estats->setFont(QFont("Helvetica", 20, QFont::Bold));
    estats->setPos(620, 5);
    scene->addItem(estats);
}

void stds::startScreen()
{
    scene->clear();
    game = Started;
    intro->play();
    QGraphicsTextItem *text = new QGraphicsTextItem(" Simple 2D Shooter\nTo start pres SPACE!");
    text->setDefaultTextColor(Qt::yellow);
    text->setFont(QFont("Helvetica", 50, QFont::Bold));
    text->setPos(70, 200);
    scene->addItem(text);

    QGraphicsTextItem *cr = new QGraphicsTextItem("Copyright (C) 2020 Prša Igor <akiro.ip@gmail.com>");
    cr->setDefaultTextColor(Qt::blue);
    cr->setFont(QFont("Helvetica", 10, QFont::Bold));
    cr->setPos(20, 20);
    scene->addItem(cr);
}

void stds::newGame()
{
    intro->stop();
    scene->clear();
    game = Playing;
    sound->play();

    ship = new player();
    connect(ship, SIGNAL(dead()), this, SLOT(playerKilled()));
    connect(ship, SIGNAL(healthChanged(int)), this, SLOT(playerStats(int)));
    ship->setPos((scene->width() / 2) - (ship->getWidth() / 2), scene->height() - (ship->getHeight() * 1));

    qsrand(QDateTime::currentMSecsSinceEpoch());
    for(int i=0; i<4; i++){
        alien = new enemy(nullptr, i);
        connect(alien, SIGNAL(dead(enemy*)), this, SLOT(enemyKilled(enemy*)));
        connect(alien, SIGNAL(healthChanged(int)), this, SLOT(scoreStats(int)));
        alien->setPos(20+i*123,20+i*57);
        scene->addItem(alien);
        count++;
    }

    ship->setFlag(QGraphicsItem::ItemIsFocusable);
    ship->setFocus();
    scene->addItem(ship);

    makeStats();
}

