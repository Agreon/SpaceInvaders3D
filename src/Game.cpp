#include "Game.h"
#include "Assets.h"

char Enemy::Direction = 'l';


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

	m_Player = new Player(0,-250, Vec3D(30,40,10));
	Entity *wings = new Entity(0,0, Vec3D(120,60,10));
	//Entity* body = new Entity(0,-40,Vec3D(40,20,10));
	m_Player->addPart(wings);
	//m_Player->addPart(wing2);

	for(int i = 0; i < (m_ScreenWidth-150) / 100; i++){
		for(int j = 0; j < (m_ScreenHeight-200) / 100; j++){
			m_Enemies.push_back(new Enemy(i*50 - (m_ScreenWidth/2) + 200 ,((j*50)-(m_ScreenHeight/2)) + 300,Vec3D(20,20,20)));
		}
	}

	int barricadeSize = 30;

	//Create Barriers
	for(int i = 0; i < 3; i++){
		m_Barricades.push_back(new Entity(i*200,-100,0));
		m_Barricades[i]->setCollisionEnabled(false);  // Damit immer nur kinder-objekte zerstört werden

		m_Barricades[i]->addPart(new Entity(0,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(-barricadeSize,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(barricadeSize,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(-barricadeSize,-barricadeSize,barricadeSize));
		m_Barricades[i]->addPart(new Entity(barricadeSize,-barricadeSize,barricadeSize));

		Entity *testEntity = new Entity(barricadeSize,barricadeSize,barricadeSize);
		Animation *testAnim = new Animation();
		testAnim->addAnimationPart(AnimationPart(Transformation(Vec3D(0,barricadeSize,0),Vec3D(0,0,0)),30));
		testAnim->addAnimationPart(AnimationPart(Transformation(Vec3D(0,-barricadeSize,0),Vec3D(0,0,0)),30));
		testEntity->addAnimation("move",testAnim);
		m_Barricades[i]->addPart(testEntity);
		testEntity->playAnimation("move",-1);

	}

	Animation *playerAnim = new Animation();
	playerAnim->addAnimationPart(AnimationPart(Transformation(Vec3D(50,0,0),Vec3D(0,0,0)),50));
	playerAnim->addAnimationPart(AnimationPart(Transformation(Vec3D(-50,0,0),Vec3D(0,0,0)),50));
		//playerAnim->addAnimationPart(AnimationPart(Transformation(Vec3D(0,0,0),Vec3D(10,10,10)),50));
	m_Player->addAnimation("moving",playerAnim);
	m_Player->getTransformation()->m_Rotation = Vec3D(0,1,0);
	//m_Player->playAnimation("moving",2);

	leftBorder = Entity(-320,0,Vec3D(10,m_ScreenHeight,10));
	rightBorder = Entity(320,0,Vec3D(10,m_ScreenHeight,10));


	Assets::initialize();

	Assets::loadSound("shoot","./assets/shoot.wav");

	return true;
}

void Game::keyDown(char key){
	m_Keys[key] = true;
}

void Game::keyUp(char key){
	m_Keys[key] = false;

	if(key == 'e'){
		m_Lasers.push_back(new Laser(m_Player->getTransformation()->m_Translation.x,m_Player->getTransformation()->m_Translation.y,1));
		Assets::playSound("shoot");
	}
}

void Game::event(){

	m_Player->update(m_Keys);
}

/*
 *
 */
void Game::update(){
	event();

	// Spielerlaser
	for(auto& laser : m_Lasers){
		laser->update();
		if(laser->getTransformation()->m_Translation.y > m_ScreenHeight/2){
			laser->setActive(false);
		}
	}

	// Gegnerlaser
	for(auto& laser : m_EnemyLasers){
		laser->update();
		if(laser->getTransformation()->m_Translation.y < -(m_ScreenHeight/2)){
			laser->setActive(false);
		}
		Entity *collidingWith = m_Player->collides(*laser);
		if(collidingWith != NULL){
			laser->setActive(false);
			//TODO: Game Over
			break;
		}
	}

	// Enemy -> Wall Collision
	for(auto& enemy: m_Enemies){
		if(enemy->collides(rightBorder)){
			Enemy::Direction = 'l';
			break;
		}else if(enemy->collides(leftBorder)){
			Enemy::Direction = 'r';
			break;
		}
	}

	// Enemy Update
	for(auto& enemy : m_Enemies){

		enemy->update();

		// Check collision with lasers
		for(auto& laser : m_Lasers){

			Entity *collidingWith = enemy->collides(*laser);

			if(collidingWith != NULL){
				laser->setActive(false);
				enemy->setActive(false);
				break;
			}
		}
	}

	// Enemy Laser -> Barricade Collision
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

		if(m_Barricades[i]->getParts()->size() < 1){
			cout << "Finally deleting barricade" << endl;
			m_Barricades.erase(m_Barricades.begin() + i);
		}
	}

}

void Game::draw(){

	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	gluLookAt(0,0,m_ScreenWidth,0,0,0,0,1,0);

	//glRotatef(-45,1,0,0);

	glPushMatrix();
	m_Player->draw();
	glPopMatrix();

	leftBorder.draw();
	rightBorder.draw();

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