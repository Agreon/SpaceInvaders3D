#pragma once


#include <iostream>
#include <map>
#include <GL/freeglut.h>
#include "util.h"
#include "Animation.h"

/*
 * An Entity is the basic object of the game world.
 * Every Game Object can consist of multiple entities, defined as children/parts.
 */
class Entity {
public:
	Entity();
	Entity(float x, float y);
	Entity(float x, float y, float size);
	Entity(float x, float y, Vec3D scale);
	~Entity();

	Entity* collides(Entity entity);

	void addPart(Entity *part);

	void addPart(string name, Entity *part);

	Entity* getPart(string name);

	vector<Entity*> *getParts();

	void draw(Transformation transformation = Transformation());

	void setTransformation(Transformation transformation);
	Transformation* getTransformation();

	void addAnimation(string name, Animation *animation);
	Animation *getAnimation(string name);

	void playAnimation(string name, int loops);
	void stopAnimation(string name);

	void deleteInactiveChildren();

	void setColor(Vec3D color);
	void setCollisionEnabled(bool b);
	void setActive(bool a);
	bool isActive();
	void setParent(Entity *parent);
	Entity* getParent();
protected:
	Vec3D getAbsoluteTranslation(Entity *entity, Vec3D translation);
	void drawBody();

	Transformation m_Transformation;
	Vec3D m_Color;

	Entity* m_Parent;
	vector<Entity*> m_Parts;
	map<string,Entity*> m_NamedParts;
	map<string,Animation*> m_Animations;
	map<string,Animation*> m_PlayingAnimations;
	bool m_Active;
	bool m_CollisionEnabled;
};