#ifndef STDS_H
#define STDS_H

#include <QDialog>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QVector>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "player.h"
#include "enemy.h"
#include "bullet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class stds; }
QT_END_NAMESPACE

class stds : public QDialog
{
    Q_OBJECT

public:
    stds(QWidget *parent = nullptr);
    ~stds();
    void keyPressEvent(QKeyEvent *);

private slots:
    void playerKilled();
    void enemyKilled(enemy *e);
    void playerStats(int h);
    void scoreStats(int h);
    void makeStats();
    void startScreen();
    void newGame();

private:
    enum state { Started, Playing, GameOver };
    Ui::stds *ui;
    QSoundEffect *sound, *explosion, *win, *lost;
    QMediaPlayer *intro;
    QGraphicsScene *scene;
    QGraphicsSimpleTextItem *pstats, *estats;
    player *ship;
    enemy *alien,*alien2;
    QSet<int> pressedKeys;
    int count = 0,score = 0;
    state game = Started;
};
#endif // STDS_H
