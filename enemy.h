#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;
class MainWindow;

class Enemy :public QObject
{
    Q_OBJECT
public:
    Enemy(MainWindow * game,const QPixmap &worrior = QPixmap (":/picture/picture/worrior.jpg"));
    ~Enemy();

    void draw(QPainter *painter) ;
    void move();
    void setPosition(int x,int y);
    void getAttack(int attack);
    void countofAttack();//判断是否在受攻击的范围并受到攻击
public slots:
    void doActivate();

private:
    const           QPixmap m_worrior;
    static const    QSize ms_fixedSize;
    int             position_x;
    int             position_y;
    int				m_maxHp;
    int				m_currentHp;
    int             m_walkingSpeed;
    MainWindow *	m_game;
    bool            m_active;


    
};

#endif // ENEMY_H
