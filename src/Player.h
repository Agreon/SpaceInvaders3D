//
// Created by root on 08.05.16.
//

#ifndef SPACEINVADERS3D_PLAYER_H
#define SPACEINVADERS3D_PLAYER_H

#include "Entity.h"
#include "util.h"

class Player : public Entity{
public:
    Player(){
        Entity();
        m_Speed = 0.2;
        m_MaxVel = 3.2;
        m_Velocity = 0;
    }

    Player(float x, float y, Vec3D scale){
        Player();
        m_Active = true;
        m_Transformation = Transformation(Vec3D(x,y,0),scale);
        m_CollisionEnabled = true;
        m_Speed = 0.2;
        m_MaxVel = 3.2;
        m_Velocity = 0;
    }

    void update(bool chars[]) {
        if(chars['a']) {
            if(m_Velocity > -m_MaxVel)
                m_Velocity -= m_Speed;

            if(m_Transformation.m_Angle > -45)
                m_Transformation.m_Angle -= 3;
        }else if(chars['d']){
            if(m_Velocity < m_MaxVel)
                m_Velocity += m_Speed;

            if(m_Transformation.m_Angle < 45)
                m_Transformation.m_Angle += 3;
        }else{
            if(m_Velocity > 0) {
                m_Velocity -= m_Speed;
            }else if(m_Velocity < 0){
                m_Velocity += m_Speed;
            }

            if((m_Velocity > 0 && m_Velocity < 0.1) || (m_Velocity < 0 && m_Velocity > -0.1))
                m_Velocity = 0;

            if(m_Transformation.m_Angle > 0){
                m_Transformation.m_Angle -= 3;
            }else if(m_Transformation.m_Angle < 0){
                m_Transformation.m_Angle += 3;
            }
        }
        m_Transformation.m_Translation.x += m_Velocity;

    }
private:
    float m_Velocity, m_MaxVel, m_Speed;

};

#endif //SPACEINVADERS3D_PLAYER_H
