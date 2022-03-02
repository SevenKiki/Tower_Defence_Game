#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QtMath>

static const int Health_Bar_Width = 20;

const QSize Enemy::ms_fixedSize(52,52);

Enemy::Enemy(MainWindow * game,const QPixmap &worrior)
    :QObject(0)
    ,m_worrior(worrior)
    ,position_x(100)
    ,position_y(100)
    ,m_walkingSpeed(1)
    ,m_maxHp(20)
    ,m_currentHp(20)
    ,m_active(false)
    ,m_game(game)
{}

Enemy::~Enemy(){
}

void Enemy::setPosition(int x, int y){
    position_x=x;
    position_y=y;
}

void  Enemy::move(){
    if(!m_active)
        return ;
    if(position_x>=100 && position_y==100 &&position_x<300)
    { int _x=position_x+m_walkingSpeed;
        setPosition(_x,position_y);
    }
    else if(position_x==300 && position_y>=100 && position_y<200)
    {int _y=position_y+m_walkingSpeed;
        setPosition(position_x,_y);
    }
    else if(position_x<=300 && position_x>100 && position_y==200)
    {int _x=position_x-m_walkingSpeed;
        setPosition(_x,position_y);
    }
    else m_game->removedEnemy(this);
}

void Enemy::getAttack(int attack){
    m_currentHp-=attack;
}

void Enemy::countofAttack(){
    if(position_y==100 && position_x>=150 &&position_x<=155)
    {
        if(m_currentHp>0)
        getAttack(1);
        else m_game->removedEnemy(this);
    }
    else getAttack(0);
}

void Enemy::doActivate()
{
    m_active = true;
}

void Enemy::draw(QPainter* painter) {
    if(!m_active)
        return ;

    painter->save();
    countofAttack();
   // QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3);
    QPoint healthBarPoint = QPoint(position_x+2,position_y-4);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    if(m_currentHp>0){
        painter->setBrush(Qt::green);
        QRect healthBarRect(healthBarPoint, QSize(m_currentHp, 2));
        painter->drawRect(healthBarRect);
    }


    painter->drawPixmap(position_x,position_y,20,30,m_worrior);
    painter->restore();
}
