#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "enemy.h"

namespace Ui {
class MainWindow;
}

class Enemy;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   void removedEnemy(Enemy *enemy);

public slots:
   void updateMap();
   void makeEnemy();


protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    QList<Enemy *>      m_enemyList;


};

#endif // MAINWINDOW_H
