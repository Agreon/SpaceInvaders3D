//
// Created by root on 18.05.16.
//

#include "Player.h"

Player::Player(){
    Entity();
    m_Speed = 0.2;
    m_MaxVel = 3.2;
    m_Velocity = 0;
}

Player::Player(float x, float y, Vec3D scale){
    Player();
    m_Active = true;
    m_Transformation = Transformation(Vec3D(x,y,0),scale);
    m_CollisionEnabled = true;
    m_Speed = 0.2;
    m_MaxVel = 3.6;
    m_Velocity = 0;
    m_LaserCooldown = 30;
    m_LaserStatus = 0;
    m_Lives = 3;
}

/*
 * Checks if player should be moved in one direction or not and uses smooth movement(m_Velocity).
 * Also the Object is rotatet until a maximum of 45 degress.
 */
void Player::update(bool chars[]) {

    if(chars['a']) {
        if(m_Velocity > -m_MaxVel)
            m_Velocity -= m_Speed;

        if(m_Transformation.m_Angle > -45)
            m_Transformation.m_Angle -= 3;
    }else if(chars['d']){
        if(m_Velocity < m_MaxVel)
            m_Velocity += m_Speed;

        if(m_Transformation.m_Angle < 45)
            m_Transformation.m_Angle += 3;
    }else{
        if(m_Velocity > 0) {
            m_Velocity -= m_Speed;
        }else if(m_Velocity < 0){
            m_Velocity += m_Speed;
        }

        if((m_Velocity > 0 && m_Velocity < 0.1) || (m_Velocity < 0 && m_Velocity > -0.1))
            m_Velocity = 0;

        if(m_Transformation.m_Angle > 0){
            m_Transformation.m_Angle -= 3;
        }else if(m_Transformation.m_Angle < 0){
            m_Transformation.m_Angle += 3;
        }
    }
    // Reloading of laser cannon
    if(m_LaserStatus > 0)
        m_LaserStatus--;
}

/*
 * Draws a Entity with optional offset from parent.
 * If an Animation is active, the frames transformation is added as well.
 * TODO: Shooting brings lags
 */
void Player::draw(Transformation transformation){
    glPushMatrix();

    for(auto& anim : m_PlayingAnimations){
        Transformation *animTransformation = anim.second->tick();
        if(animTransformation == NULL){
            map<string,Animation*>::iterator it = m_PlayingAnimations.find(anim.first);
            m_PlayingAnimations.erase(it);
            continue;
        }
        m_Transformation += *animTransformation;
        //cout << "Adding to scalex " << animTransformation->m_Scale.x << endl;
        //m_Transformation.m_Scale += animTransformation->m_Scale;
    }


    transformation += m_Transformation;
    transformation.m_Scale = m_Transformation.m_Scale;

    Vec3D parentScale = Vec3D(1,1,1);
    if(m_Parent != NULL){
        parentScale = m_Parent->getTransformation()->m_Scale;
    }


    glTranslatef(transformation.m_Translation.x, transformation.m_Translation.y , transformation.m_Translation.z );
    glRotatef(transformation.m_Angle, transformation.m_Rotation.x, transformation.m_Rotation.y , transformation.m_Rotation.z);
    glScalef(transformation.m_Scale.x,transformation.m_Scale.y,transformation.m_Scale.z);

    glColor3f(0.2,0.9,0.2);
//        drawBody();
    glutSolidSphere(1,30,30);

    // Cockpit
    //glPushMatrix();
    glTranslatef(0,0,10 / transformation.m_Scale.z);
    //glScalef(transformation.m_Scale.x / 20,transformation.m_Scale.y / 20, transformation.m_Scale.z / 20);
    glScalef(15 / transformation.m_Scale.x, 20 / transformation.m_Scale.y , 10 / transformation.m_Scale.z);
    glColor3f(0.2,0.2,0.9);
    glutSolidSphere(1,30,30);
    // glPopMatrix();

    glPopMatrix();

    for(auto& part : m_Parts){
        part->draw(transformation);
    }
    //glPopMatrix();
}

/*
 * Checks if shooting is allowed and starts animation if so
 */
bool Player::shoot(){

    if(m_LaserStatus > 0)
        return false;

    getPart("gun")->playAnimation("gunRotation",3);

    m_LaserStatus = m_LaserCooldown;

    return true;
}

float Player::getVolicty(){
    return m_Velocity;
}

void Player::setLives(int lives){
    m_Lives = lives;
}

int Player::getLives(){
    return m_Lives;
}