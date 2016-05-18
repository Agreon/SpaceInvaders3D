//
// Created by root on 08.05.16.
//

#ifndef SPACEINVADERS3D_PLAYER_H
#define SPACEINVADERS3D_PLAYER_H

#include "Entity.h"
#include "util.h"

class Player : public Entity{
public:
    Player();
    Player(float x, float y, Vec3D scale);

    void update(bool chars[]);
    void draw(Transformation transformation = Transformation());

    bool shoot();

    float getVolicty();
    void setLives(int lives);
    int getLives();

private:
    float m_Velocity, m_MaxVel, m_Speed;
    int m_LaserCooldown, m_LaserStatus, m_Lives;

};

#endif //SPACEINVADERS3D_PLAYER_H
