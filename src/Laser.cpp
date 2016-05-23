//
// Created by root on 18.05.16.
//
#include "Laser.h"

Laser::Laser(float x, float y, bool dir) {
    Entity();
    m_Transformation = Transformation(Vec3D(x, y, 0), Vec3D(10, 20, 10));
    m_Direction = dir;
}

void Laser::update(){
    if(m_Direction){
       m_Transformation.m_Translation.y += 5;
    }else {
        m_Transformation.m_Translation.y -= 5;
    }
}
