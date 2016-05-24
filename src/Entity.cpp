//
// Created by root on 18.05.16.
//
#include "Entity.h"

Entity::Entity(){
    m_Transformation = Transformation(Vec3D(),Vec3D(1,1,1));
    m_Active = true;
    m_Parent = NULL;
    m_CollisionEnabled = true;
    m_Color = Vec3D(-1,-1,-1);
}

Entity::Entity(float x, float y) : Entity(){
    m_Transformation = Transformation(Vec3D(x,y,0),Vec3D(1,1,1));
}

Entity::Entity(float x, float y, float size) : Entity(x,y){
    m_Transformation.m_Scale = Vec3D(size,size,size);
}

Entity::Entity(float x, float y, Vec3D scale) : Entity(x,y){
    m_Transformation.m_Scale = scale;
}

Entity::~Entity(){
}

Vec3D Entity::getAbsoluteTranslation(Entity *entity, Vec3D translation){

    translation += entity->getTransformation()->m_Translation;

    Entity* parent = entity->getParent();

    if(parent == NULL){
        return translation;
    }else{
        return getAbsoluteTranslation(parent,translation);
    }
}

//TODO: Think of Rotation later
//TODO: If the other object is a multi-part objekt collision does not work
Entity* Entity::collides(Entity entity){

    for(auto& part: m_Parts){
        if(part->collides(entity) != NULL){
            return part;
        }
    }

    if(m_CollisionEnabled == false)
        return NULL;

    Vec3D translation = getAbsoluteTranslation(this,Vec3D());
    Vec3D scale = m_Transformation.m_Scale;

    //Check for non-collision on every site
    if((translation.x + scale.x / 2 < entity.m_Transformation.m_Translation.x - entity.m_Transformation.m_Scale.x / 2)
       || (translation.x - scale.x/2 > entity.m_Transformation.m_Translation.x + entity.m_Transformation.m_Scale.x / 2)
       || (translation.y + scale.y / 2 < entity.m_Transformation.m_Translation.y - entity.m_Transformation.m_Scale.y /2 )
       || (translation.y - scale.y / 2 > entity.m_Transformation.m_Translation.y + entity.m_Transformation.m_Scale.y / 2))
        return NULL;																					//TODO: Maybe Front and back

    return this;
}

void Entity::addPart(Entity *part){
    part->setParent(this);
    m_Parts.push_back(part);
}

void Entity::addPart(string name, Entity *part){
    part->setParent(this);
    m_Parts.push_back(part);
    m_NamedParts[name] = part;
}

Entity* Entity::getPart(string name){
    return m_NamedParts[name];
}

vector<Entity*>* Entity::getParts(){
    return &m_Parts;
}

// Draw with parent pos + offset of part
// TODO: Shooting brings lags
void Entity::draw(Transformation transformation){
    glPushMatrix();

    for(auto& anim : m_PlayingAnimations){
        Transformation *animTransformation = anim.second->tick();
        if(animTransformation == NULL){
            //map<string,Animation*>::iterator it = m_PlayingAnimations.find(anim.first);
           // m_PlayingAnimations.erase(it);
            continue;
        }
        m_Transformation += *animTransformation;
        //cout << "Adding to scalex " << animTransformation->m_Scale.x << endl;
        //m_Transformation.m_Scale += animTransformation->m_Scale;
    }


    //transformation = m_Transformation;
    transformation += m_Transformation;
    transformation.m_Scale = m_Transformation.m_Scale;

    glTranslatef(transformation.m_Translation.x, transformation.m_Translation.y , transformation.m_Translation.z );
    glRotatef(transformation.m_Angle, transformation.m_Rotation.x , transformation.m_Rotation.y , transformation.m_Rotation.z);
    //glTranslatef(transformation.m_Translation.x, transformation.m_Translation.y , transformation.m_Translation.z );
    glScalef(transformation.m_Scale.x,transformation.m_Scale.y,transformation.m_Scale.z);

    if(m_Color.x == -1){
        drawBody();
    }else{
        glColor3f(m_Color.x,m_Color.y,m_Color.z);
        glutSolidCube(1);
    }
   // glColor3f(1,0,0);
   // glutSolidCube(1);
    glPopMatrix();

    for(auto& part : m_Parts){
        part->draw(transformation);
    }
    //glPopMatrix();
}

void Entity::drawBody(){

    float fSeitenL = 1;

    glBegin(GL_POLYGON);   //Vorderseite
    glNormal3f(0,0,1);
    glColor4f(1.0f,0.0f,0.0f,1.0f);	//ROT
    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
    glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
    glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
    glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
    glEnd();


    glBegin(GL_POLYGON);   //Rechte Seite
    glNormal3f(1,0,0);
    glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
    glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
    glColor4f(0.0f,1.0f,1.0f,1.0f);	//CYAN
    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
    glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
    glEnd();


    glBegin(GL_POLYGON);   //Rueckseite
    glNormal3f(0,0,-1);
    glColor4f(0.0f,1.0f,1.0f,1.0f); //CYAN
    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
    glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
    glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
    glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
    glEnd();


    glBegin(GL_POLYGON);   //Linke Seite
    glNormal3f(-1,0,0);
    glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
    glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
    glColor4f(1.0f,0.0f,0.0f,1.0f); //ROT
    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
    glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
    glEnd();

    glBegin(GL_POLYGON);   //Deckflaeche
    glNormal3f(0,1,0);
    glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
    glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
    glColor4f(0.0f,1.0f,1.0f,1.0f); //CYAN
    glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
    glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
    glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
    glEnd();

    glBegin(GL_POLYGON);   //Bodenflaeche
    glNormal3f(0,-1,0);
    glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);

    glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);

    glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
    glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);

    glColor4f(1.0f,0.0f,0.0f,1.0f); //ROT
    glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
    glEnd();

}

void Entity::setColor(Vec3D color){
    m_Color = color;
}

void Entity::setActive(bool a){
    m_Active = a;
}

bool Entity::isActive(){
    return m_Active;
}

void Entity::setParent(Entity *parent){
    m_Parent = parent;
}

Entity* Entity::getParent(){
    return m_Parent;
}

void Entity::setTransformation(Transformation transformation){
    m_Transformation = transformation;
}

Transformation* Entity::getTransformation(){
    return &m_Transformation;
}

void Entity::addAnimation(string name, Animation *animation){
    m_Animations[name] = animation;
}

Animation* Entity::getAnimation(string name){
    return m_Animations[name];
}

void Entity::playAnimation(string name, int loops){
    m_PlayingAnimations[name] = m_Animations[name];
    m_PlayingAnimations[name]->reload();
    m_PlayingAnimations[name]->setMaxLoops(loops);
}

void Entity::stopAnimation(string name){
    map<string,Animation*>::iterator it = m_PlayingAnimations.find(name);
    m_PlayingAnimations.erase(it);
}

void Entity::setCollisionEnabled(bool b){
    m_CollisionEnabled = b;
}

//TODO: Vlt. löschen
void Entity::deleteInactiveChildren(){
    for(int i = 0; i < m_Parts.size(); i++){

        m_Parts[i]->deleteInactiveChildren();

        if(m_Parts[i]->isActive() == false){
            m_Parts.erase(m_Parts.begin() + i);
        }
    }
}
