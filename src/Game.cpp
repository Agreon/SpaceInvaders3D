#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}


bool Game::init(int sWidth, int sHeight){

	m_ScreenWidth = sWidth;
	m_ScreenHeight = sHeight;

	for(int i = 0; i < 256; i++){
		m_Keys[i] = false;
	}

	m_Player = new Entity(0,-100, Vec3D(15,18,10));
	Entity* body = new Entity(0,-20,Vec3D(40,20,10));
	m_Player->addPart(body);

	for(int i = 0; i < (m_ScreenWidth-150) / 100; i++){
		for(int j = 0; j < (m_ScreenHeight-200) / 100; j++){
			m_Enemies.push_back(new Entity(i*50 - (m_ScreenWidth/2) + 200 ,(j*50)-(m_ScreenHeight/2) + 300,10));
		}
	}

	//Create Barriers
	for(int i = 0; i < 3; i++){
		m_Barricades.push_back(new Entity(i*200,-30,0));

		Entity* row1 = new Entity(0,-10,Vec3D(10,10,10));
		Entity* row2 = new Entity(0,-20,Vec3D(20,10,10));
		Entity* row3 = new Entity(0,-30,Vec3D(30,10,10));
		m_Barricades[i]->addPart(row1);
		m_Barricades[i]->addPart(row2);
		m_Barricades[i]->addPart(row3);

		m_Barricades[i]->setCollisionEnabled(false);
	}

	Animation *playerAnim = new Animation();
	playerAnim->addAnimationPart(AnimationPart(Transformation(Vec3D(50,0,0),Vec3D(0,0,0)),50));
	playerAnim->addAnimationPart(AnimationPart(Transformation(Vec3D(-50,0,0),Vec3D(0,0,0)),50));
		//playerAnim->addAnimationPart(AnimationPart(Transformation(Vec3D(0,0,0),Vec3D(10,10,10)),50));
	m_Player->addAnimation("moving",playerAnim);
	m_Player->getTransformation()->m_Rotation = Vec3D(0,1,0);
	//m_Player->playAnimation("moving",2);

	return true;
}

void Game::keyDown(char key){
	m_Keys[key] = true;
}

void Game::keyUp(char key){
	m_Keys[key] = false;

	if(key == 'e'){
		m_Lasers.push_back(new Laser(m_Player->getTransformation()->m_Translation.x,m_Player->getTransformation()->m_Translation.y,1));
	}
}

//TODO: Vlt. smoothe bewegungen einbauen
void Game::event(){
	if(m_Keys['a']){
		m_Player->getTransformation()->m_Translation.x -= 2;
		if(m_Player->getTransformation()->m_Angle > -45)
			m_Player->getTransformation()->m_Angle -= 2;

	}
	else if(m_Keys['d']){
		m_Player->getTransformation()->m_Translation.x += 2;
		if(m_Player->getTransformation()->m_Angle < 45)
			m_Player->getTransformation()->m_Angle += 2;
	}else{
		if(m_Player->getTransformation()->m_Angle > 0){
			m_Player->getTransformation()->m_Angle -= 3;
		}else if(m_Player->getTransformation()->m_Angle < 0){
			m_Player->getTransformation()->m_Angle += 3;
		}
	}
}

/*
 * TODO: Dynamically Enemy Movement
 * Barricade stuff
 * Laser-Barricade collision
 */
void Game::update(){
	event();

	for(auto& laser : m_Lasers){
		laser->update();
		if(laser->getTransformation()->m_Translation.y > m_ScreenHeight/2){
			laser->setActive(false);
		}
	}

	for(auto& laser : m_EnemyLasers){
		laser->update();
		if(laser->getTransformation()->m_Translation.y < -(m_ScreenHeight/2)){
			laser->setActive(false);
		}
		Entity *collidingWith = m_Player->collides(*laser);
		if(collidingWith != NULL){
			laser->setActive(false);
			//TODO: Remove one life
			break;
		}
	}

	// TODO: Collision not working
	for(auto& enemy : m_Enemies){
		for(auto& laser : m_Lasers){

			Entity *collidingWith = enemy->collides(*laser);

			if(collidingWith != NULL){
				laser->setActive(false);
				enemy->setActive(false);
				break;
			}
		}
	}

	for(auto& laser : m_EnemyLasers){
		for(auto& barricade : m_Barricades){

			Entity *collidingWith = barricade->collides(*laser);

			if(collidingWith != NULL){
				collidingWith->setActive(false);
				laser->setActive(false);
				break;
			}

		}
	}

	//TODO: Maybe delete objekt with children
	for(int i = 0; i < m_Lasers.size(); i++){

		m_Lasers[i]->deleteInactiveChildren();

		if(m_Lasers[i]->isActive() == false){
			m_Lasers.erase(m_Lasers.begin() + i);
		}
	}

	for(int i = 0; i < m_Enemies.size(); i++){

		m_Enemies[i]->deleteInactiveChildren();

		if(m_Enemies[i]->isActive() == false){
			m_Enemies.erase(m_Enemies.begin() + i);
		}
	}

	for(int i = 0; i < m_Barricades.size(); i++){

		m_Barricades[i]->deleteInactiveChildren();

		if(m_Barricades[i]->isActive() == false || m_Barricades[i]->getParts()->size() < 1){
			cout << "Finally deleting barricade" << endl;
			m_Barricades.erase(m_Barricades.begin() + i);
		}
	}

}

void Game::draw(){

	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	gluLookAt(0,0,m_ScreenWidth/2,0,0,0,0,1,0);

	//glRotatef(-45,1,0,0);

	m_Player->draw();

	for(auto& enemy: m_Enemies){
		enemy->draw();
	}

	for(auto& barricade: m_Barricades){
		barricade->draw();
	}

	for (auto& laser : m_Lasers){
		laser->draw();
	}
}