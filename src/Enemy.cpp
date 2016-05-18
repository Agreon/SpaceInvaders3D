//
// Created by root on 18.05.16.
//
#include "Enemy.h"

Enemy::Enemy(float x, float y, Vec3D scale){
        m_Parent = NULL;
        m_Active = true;
        m_Transformation = Transformation(Vec3D(x,y,0),scale);
        m_CollisionEnabled = true;
        m_Velocity = 1;
}

void Enemy::update(){
        if(Direction == 'l'){
            m_Transformation.m_Translation.x -= m_Velocity;
        }else{
            m_Transformation.m_Translation.x += m_Velocity;
        }
        if(m_Velocity < 2.6)
            m_Velocity += 0.005;
}