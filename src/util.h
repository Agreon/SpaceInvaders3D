//
// Created by root on 05.05.16.
//

#ifndef SPACEINVADERS3D_UTIL_H
#define SPACEINVADERS3D_UTIL_H

using namespace std;

class Vec3D{
public:
    Vec3D();
    Vec3D(float x, float y, float z);
    Vec3D& operator+=(const Vec3D &vec2);
    Vec3D& operator-=(const Vec3D &vec2);
    Vec3D& operator/(const float val);

    float x, y, z;
};



class Transformation{
public:
    Transformation(Vec3D translation = Vec3D(), Vec3D scale = Vec3D(), Vec3D rotation = Vec3D(), float angle = 0);

    ~Transformation();

    Transformation &operator+=(const Transformation & transformation);

    Transformation &operator-=(const Transformation & transformation);

    Transformation &operator/(const float val);

    Vec3D m_Translation;
    Vec3D m_Scale;
    Vec3D m_Rotation;
    float m_Angle;
};


#endif //SPACEINVADERS3D_UTIL_H
