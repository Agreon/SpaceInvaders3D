//
// Created by root on 05.05.16.
//

#ifndef SPACEINVADERS3D_LASER_H
#define SPACEINVADERS3D_LASER_H

#include "Entity.h"

class Laser : public Entity{
public:
    Laser(float x, float y, bool dir);
    void update();

private:
    bool m_Direction;
};

#endif //SPACEINVADERS3D_LASER_H
