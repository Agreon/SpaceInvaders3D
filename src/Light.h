//
// Created by root on 14.05.16.
//

#ifndef SPACEINVADERS3D_LIGHT_H
#define SPACEINVADERS3D_LIGHT_H

#include "Entity.h"

class Light : public Entity{
public:
    Light(){
        m_Transformation = Transformation(Vec3D(),Vec3D(1,1,1));
        m_Active = true;
        m_Parent = NULL;
        m_CollisionEnabled = true;
    }

    Light(float x, float y){
        m_Active = true;
        m_Parent = NULL;
        m_Transformation = Transformation(Vec3D(x,y,0),Vec3D(1,1,1));
        m_CollisionEnabled = false;
    }

    void draw(Transformation transformation = Transformation()){
        GLfloat pos[] = {m_Transformation.m_Translation.x, m_Transformation.m_Translation.y, m_Transformation.m_Translation.z, 0};

        glLightfv(GL_LIGHT0, GL_POSITION, pos);
    }
private:

};

#endif //SPACEINVADERS3D_LIGHT_H
