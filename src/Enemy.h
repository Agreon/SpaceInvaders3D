//
// Created by root on 09.05.16.
//

#ifndef SPACEINVADERS3D_ENEMY_H
#define SPACEINVADERS3D_ENEMY_H

#include "Entity.h"

class Enemy : public Entity{
public:
    Enemy(float x, float y, Vec3D scale);

    void update();

    /*
     * All Enemies behave depending on that static variable
     */
    static char Direction;

private:
    float m_Velocity;
};


#endif //SPACEINVADERS3D_ENEMY_H
