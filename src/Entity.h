#pragma once


#include <iostream> 
#include <GL/freeglut.h>       

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

	float x;
	float y;
	float z;
};


class Entity {
public:
	Entity(){
		m_Translation = Vec3D();
		m_Rotation = Vec3D();
		m_Scale = Vec3D(1,1,1);
		m_Angle = 0;
		m_Active = true;
		m_Parent = NULL;
	}

	Entity(float x, float y){
		m_Active = true;
		m_Translation = Vec3D(x,y,0);
	}

	Entity(float x, float y, float size){
		Entity();
		m_Active = true;
		m_Translation = Vec3D(x,y,0);
		m_Scale = Vec3D(size,size,size);
	}

	Entity(float x, float y, Vec3D scale){
		Entity();
		m_Active = true;
		m_Translation = Vec3D(x,y,0);
		m_Scale = scale;
	}

	~Entity(){

	}
	//TODO: Test Achtung: Ght nach oben und addiert parent vec drauf
	Vec3D getAbsoluteTranslation(Entity *entity, Vec3D translation){
		Entity* parent = entity->getParent();

		if(parent == NULL){
			translation += entity->m_Translation;
			return translation;
		}else{
			translation += parent->m_Translation;
			return getAbsoluteTranslation(parent,translation);
		}
	}

	//TODO: Think of maybe centered coordinates :/
	Entity* collides(Entity entity){

		for(auto& part: m_Parts){
			if(part->collides(entity) != NULL){
				return part;
			}
		}

		Vec3D translation = getAbsoluteTranslation(this,Vec3D());
		Vec3D scale = m_Scale;

		//Check for non-collision on every site
		if((translation.x > entity.getPos()->x + entity.getScale()->x)		//Left Side
		   	|| (translation.x + scale.x < entity.getPos()->x )				//Right Side
		 	|| (translation.y > entity.getPos()->y + entity.getScale()->y)	//Up Side
			||(translation.y + scale.y < entity.getPos()->y)	)			//Down Side
			return NULL;

		return this;
	}

	void addPart(Entity *part){
		part->setParent(this);
		m_Parts.push_back(part);
	}

	vector<Entity*> *getParts(){
		return &m_Parts;
	}

	// Draw with parent pos + offset of part
	void draw(Vec3D translation = Vec3D(), Vec3D rotation = Vec3D(), float angle = 0){
		glPushMatrix();

		translation += m_Translation;
		rotation += m_Rotation;
		angle += m_Angle;

		glTranslatef(translation.x, translation.y , translation.z );
		glRotatef(angle, rotation.x , rotation.y , rotation.z);
		glScalef(m_Scale.x,m_Scale.y,m_Scale.z);

		glColor3f(1,1,1);
		drawBody();
		glPopMatrix();

		for(auto& part : m_Parts){
			part->draw(translation, rotation, angle);
		}
	}

	void drawBody(){

		float fSeitenL = 1;

		glBegin(GL_POLYGON);   //Vorderseite
		//glColor4f(1.0f,0.0f,0.0f,1.0f);	//ROT
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		//glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		//glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		//glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glEnd();


		glBegin(GL_POLYGON);   //Rechte Seite
		//glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		//glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(0.0f,1.0f,1.0f,1.0f);	//CYAN
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glEnd();


		glBegin(GL_POLYGON);   //Rueckseite
		//glColor4f(0.0f,1.0f,1.0f,1.0f); //CYAN
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		glEnd();


		glBegin(GL_POLYGON);   //Linke Seite
		//glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(1.0f,0.0f,0.0f,1.0f); //ROT
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		//glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		glEnd();

		glBegin(GL_POLYGON);   //Deckflaeche
		//glColor4f(1.0f,0.0f,1.0f,1.0f); //MAGENTA
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		//glColor4f(1.0f,1.0f,1.0f,1.0f); //WEISS
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,+fSeitenL/2.0f);
		//glColor4f(0.0f,1.0f,1.0f,1.0f); //CYAN
		glVertex3f(+fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(0.0f,0.0f,1.0f,1.0f); //BLAU
		glVertex3f(-fSeitenL/2.0f,+fSeitenL/2.0f,-fSeitenL/2.0f);
		glEnd();

		glBegin(GL_POLYGON);   //Bodenflaeche
		//glColor4f(0.0f,0.0f,0.0f,1.0f); //SCHWARZ
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(0.0f,1.0f,0.0f,1.0f); //GRUEN
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,-fSeitenL/2.0f);
		//glColor4f(1.0f,1.0f,0.0f,1.0f); //GELB
		glVertex3f(+fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		//glColor4f(1.0f,0.0f,0.0f,1.0f); //ROT
		glVertex3f(-fSeitenL/2.0f,-fSeitenL/2.0f,+fSeitenL/2.0f);
		glEnd();
	}

	void setTranslation(float x, float y, float z){
		m_Translation = Vec3D(x,y,z);
	}

	Vec3D* getTranslation(){
		return &m_Translation;
	}

	void setRotation(float angle, float x, float y, float z){
		m_Angle = angle;
		m_Rotation = Vec3D(x,y,z);
	}

	Vec3D* getRotation(){
		return &m_Rotation;
	}

	float getAngle(){
		return m_Angle;
	}

	void setScale(float x, float y, float z){
		m_Scale = Vec3D(x,y,z);
	}

	Vec3D* getScale(){
		return &m_Scale;
	}

	void setPos(Vec3D v){
		m_Translation = v;
	}

	void setActive(bool a){
		m_Active = a;
	}

	Vec3D * getPos(){
		return &m_Translation;
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

protected:
	Vec3D m_Translation;
	float m_Angle;
	Vec3D m_Rotation;
	Vec3D m_Scale;

	vector<Entity*> m_Parts;
	bool m_Active;

	Vec3D absPos = Vec3D();

	Entity* m_Parent;
};