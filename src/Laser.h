//
// Created by root on 05.05.16.
//

#ifndef SPACEINVADERS3D_LASER_H
#define SPACEINVADERS3D_LASER_H

#include "Entity.h"

class Laser : public Entity{
public:

    Laser(float x, float y, bool dir){
        Entity();
        m_Translation = Vec3D(x, y, 0);
        m_Scale = Vec3D(10,20,5);
        m_Direction = dir;
    }

    void update(){
        if(m_Direction){
            m_Translation.y += 5;
        }else{
            m_Translation.y -= 5;
        }
    }

private:
    bool m_Direction;
};

#endif //SPACEINVADERS3D_LASER_H
