#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enemy.h"
#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(30, this, SLOT(makeEnemy()));


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::removedEnemy(Enemy *enemy){
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
}
void MainWindow::paintEvent(QPaintEvent *){
    QPixmap cachePix(":/picture/picture/map.jpg");
    QPainter painter(this);
    painter.drawPixmap(100, 100, cachePix);

     QPainter cachePainter(&cachePix);

     foreach ( Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);
}

void MainWindow::makeEnemy(){
    int spawnTime[4]={1000,1000,1000,1000};
    for (int i = 0; i < 4; i++)
    {
        Enemy *enemy = new Enemy(this);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime[i], enemy, SLOT(doActivate()));
        /*在一个给定时间后调用一个槽只调用一次
         * 在100毫秒后刺激doactivate函数
         */

    }

}

void MainWindow::updateMap(){
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    update();
}
