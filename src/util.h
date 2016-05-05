//
// Created by root on 05.05.16.
//

#ifndef SPACEINVADERS3D_UTIL_H
#define SPACEINVADERS3D_UTIL_H

using namespace std;

class Vec3D {
public:
    Vec3D(){
        x = 0;
        y = 0;
        z = 0;
    }

    Vec3D(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3D & operator+=(const Vec3D & vec2){
        this->x += vec2.x;
        this->y += vec2.y;
        this->z += vec2.z;
        return *this;
    }

    Vec3D & operator-=(const Vec3D & vec2){
        this->x -= vec2.x;
        this->y -= vec2.y;
        this->z -= vec2.z;
        return *this;
    }

    Vec3D & operator/(const float val){
        Vec3D vec3D = Vec3D(x/val,y/val,z/val);
        return vec3D;
    }

    float x;
    float y;
    float z;
};

class Transformation{
public:
    Transformation(Vec3D translation = Vec3D(), Vec3D scale = Vec3D(), Vec3D rotation = Vec3D(), float angle = 0){
        m_Translation = translation;
        m_Scale = scale;
        m_Rotation = rotation;
        m_Angle = angle;
    }

    ~Transformation(){}

    Transformation & operator+=(const Transformation & transformation){
        this->m_Translation += transformation.m_Translation;
        this->m_Scale += transformation.m_Scale;
        this->m_Rotation += transformation.m_Rotation;
        this->m_Angle += transformation.m_Angle;
        return *this;
    }

    Transformation & operator-=(const Transformation & transformation){
        this->m_Translation -= transformation.m_Translation;
        this->m_Scale -= transformation.m_Scale;
        this->m_Rotation -= transformation.m_Rotation;
        this->m_Angle -= transformation.m_Angle;
        return *this;
    }

    Transformation &operator/(const float val){
        Transformation transformation(m_Translation/val,m_Scale/val,m_Rotation,m_Angle/val);

        return transformation;
    }

    Vec3D m_Translation;
    Vec3D m_Scale;
    Vec3D m_Rotation;
    float m_Angle;
};


#endif //SPACEINVADERS3D_UTIL_H
