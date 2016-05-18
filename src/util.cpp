//
// Created by root on 18.05.16.
//
#include "util.h"

Vec3D::Vec3D(){
    x = 0;
    y = 0;
    z = 0;
}

Vec3D::Vec3D(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3D& Vec3D::operator+=(const Vec3D & vec2){
    this->x += vec2.x;
    this->y += vec2.y;
    this->z += vec2.z;
    return *this;
}

Vec3D& Vec3D::operator-=(const Vec3D & vec2){
    this->x -= vec2.x;
    this->y -= vec2.y;
    this->z -= vec2.z;
    return *this;
}

Vec3D& Vec3D::operator/(const float val){
    Vec3D vec3D = Vec3D(x/val,y/val,z/val);
    return vec3D;
}

Transformation::Transformation(Vec3D translation, Vec3D scale, Vec3D rotation, float angle){
    m_Translation = translation;
    m_Scale = scale;
    m_Rotation = rotation;
    m_Angle = angle;
}

Transformation::~Transformation(){}

Transformation& Transformation::operator+=(const Transformation & transformation){
    this->m_Translation += transformation.m_Translation;
    this->m_Scale += transformation.m_Scale;
    this->m_Rotation += transformation.m_Rotation;
    this->m_Angle += transformation.m_Angle;
    return *this;
}

Transformation& Transformation::operator-=(const Transformation & transformation){
    this->m_Translation -= transformation.m_Translation;
    this->m_Scale -= transformation.m_Scale;
    this->m_Rotation -= transformation.m_Rotation;
    this->m_Angle -= transformation.m_Angle;
    return *this;
}

Transformation& Transformation::operator/(const float val){
    Transformation transformation(m_Translation/val,m_Scale/val,m_Rotation,m_Angle/val);

    return transformation;
}
