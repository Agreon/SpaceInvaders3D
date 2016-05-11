//
// Created by root on 09.05.16.
//

#ifndef SPACEINVADERS3D_ENEMY_H
#define SPACEINVADERS3D_ENEMY_H

#include "Entity.h"

class Enemy : public Entity{
public:

    Enemy();
    Enemy(float x, float y, Vec3D scale){
        m_Parent = NULL;
        m_Active = true;
        m_Transformation = Transformation(Vec3D(x,y,0),scale);
        m_CollisionEnabled = true;
        m_Velocity = 0;
    }

    void update(){
        if(Direction == 'l'){
            m_Transformation.m_Translation.x -= m_Velocity;
        }else{
            m_Transformation.m_Translation.x += m_Velocity;
        }
        m_Velocity += 0.005;
    }
    static char Direction;

private:
    float m_Velocity;
};


#endif //SPACEINVADERS3D_ENEMY_H
