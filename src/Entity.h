#pragma once


#include <iostream>
#include <map>
#include <GL/freeglut.h>
#include "util.h"
#include "Animation.h"


class Entity {
public:
	Entity(){
		m_Transformation = Transformation(Vec3D(),Vec3D(1,1,1));
		m_Active = true;
		m_Parent = NULL;
		m_CollisionEnabled = true;
	}

	Entity(float x, float y){
		m_Active = true;
		m_Transformation = Transformation(Vec3D(x,y,0),Vec3D(1,1,1));
		m_CollisionEnabled = true;
	}

	Entity(float x, float y, float size){
		Entity();
		m_Active = true;
		m_Transformation = Transformation(Vec3D(x,y,0),Vec3D(size,size,size));
		m_CollisionEnabled = true;
	}

	Entity(float x, float y, Vec3D scale){
		m_Parent = NULL;
		m_Active = true;
		m_Transformation = Transformation(Vec3D(x,y,0),scale);
		m_CollisionEnabled = true;
	}

	~Entity(){
	}

	Vec3D getAbsoluteTranslation(Entity *entity, Vec3D translation){

		translation += entity->getTransformation()->m_Translation;

		Entity* parent = entity->getParent();

		if(parent == NULL){
			return translation;
		}else{
			return getAbsoluteTranslation(parent,translation);
		}
	}

	//TODO: Think of Rotation later
	Entity* collides(Entity entity){

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

	void addPart(Entity *part){
		part->setParent(this);
		m_Parts.push_back(part);
	}

	void addPart(string name, Entity *part){
		part->setParent(this);
		m_Parts.push_back(part);
		m_NamedParts[name] = part;
	}

	Entity* getPart(string name){
		return m_NamedParts[name];
	}

	vector<Entity*> *getParts(){
		return &m_Parts;
	}

	// Draw with parent pos + offset of part
	void draw(Transformation transformation = Transformation()){
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


		//transformation = m_Transformation;
		transformation += m_Transformation;
		transformation.m_Scale = m_Transformation.m_Scale;

		glTranslatef(transformation.m_Translation.x, transformation.m_Translation.y , transformation.m_Translation.z );
		glRotatef(transformation.m_Angle, transformation.m_Rotation.x , transformation.m_Rotation.y , transformation.m_Rotation.z);
		//glTranslatef(transformation.m_Translation.x, transformation.m_Translation.y , transformation.m_Translation.z );
		glScalef(transformation.m_Scale.x,transformation.m_Scale.y,transformation.m_Scale.z);

		glColor3f(1,1,1);
		drawBody();
		//glutSolidCube(1);
		glPopMatrix();

		for(auto& part : m_Parts){
			part->draw(transformation);
		}
		//glPopMatrix();
	}

	void drawBody(){

		float fSeitenL = 1;

		/*glBegin(GL_POLYGON);   //Vorderseite
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glEnd();


		glBegin(GL_POLYGON);   //Rechte Seite
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glEnd();


		glBegin(GL_POLYGON);   //Rueckseite
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		glEnd();


		glBegin(GL_POLYGON);   //Linke Seite
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glEnd();

		glBegin(GL_POLYGON);   //Deckflaeche
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		glEnd();

		glBegin(GL_POLYGON);   //Bodenflaeche
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		glEnd();*/

		glBegin(GL_POLYGON);   //Vorderseite
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

	void setActive(bool a){
		m_Active = a;
	}

	bool isActive(){
		return m_Active;
	}

	void setParent(Entity *parent){
		m_Parent = parent;
	}

	Entity* getParent(){
		return m_Parent;
	}

	void setTransformation(Transformation transformation){
		m_Transformation = transformation;
	}

	Transformation* getTransformation(){
		return &m_Transformation;
	}

	void addAnimation(string name, Animation *animation){
		m_Animations[name] = animation;
	}

	Animation *getAnimation(string name){
		return m_Animations[name];
	}

	void playAnimation(string name, int loops){
		m_PlayingAnimations[name] = m_Animations[name];
		m_PlayingAnimations[name]->reload();
		m_PlayingAnimations[name]->setMaxLoops(loops);
	}

	void stopAnimation(string name){
		map<string,Animation*>::iterator it = m_PlayingAnimations.find(name);
		m_PlayingAnimations.erase(it);
	}

	void setCollisionEnabled(bool b){
		m_CollisionEnabled = b;
	}

	//TODO: Vlt. löschen
	void deleteInactiveChildren(){
		for(int i = 0; i < m_Parts.size(); i++){

			m_Parts[i]->deleteInactiveChildren();

			if(m_Parts[i]->isActive() == false){
				m_Parts.erase(m_Parts.begin() + i);
			}
		}
	}

protected:
	Transformation m_Transformation;

	Entity* m_Parent;
	vector<Entity*> m_Parts;
	map<string,Entity*> m_NamedParts;
	map<string,Animation*> m_Animations;
	map<string,Animation*> m_PlayingAnimations;
	bool m_Active;
	bool m_CollisionEnabled;
};