//
// Created by root on 05.05.16.
//

#ifndef SPACEINVADERS3D_LASER_H
#define SPACEINVADERS3D_LASER_H

#include "Entity.h"

class Laser : public Entity{
public:

    //TODO: Speed
    Laser(float x, float y, bool dir){
        Entity();
        m_Transformation = Transformation(Vec3D(x,y,0),Vec3D(10,20,5));
        m_Direction = dir;
    }

    void update(){
        if(m_Direction){
            m_Transformation.m_Translation.y += 5;
        }else{
            m_Transformation. m_Translation.y -= 5;
        }
    }

private:
    bool m_Direction;
};

#endif //SPACEINVADERS3D_LASER_H
