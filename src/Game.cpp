#include "Game.h"
#include "Assets.h"
#include "Light.h"

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

	// Player
	m_Player = new Player(0,-250, Vec3D(30,40,10));
	// Gun + Animation
	Entity *gun = new Entity(0,50, Vec3D(10,30,10));
	Animation *shootAnimation = new Animation();
	shootAnimation->addAnimationPart(AnimationPart(Transformation(Vec3D(),Vec3D(),Vec3D(0,1,0),90),10));
	gun->addAnimation("gunRotation",shootAnimation);
	m_Player->addPart("gun",gun);

	// Wings
	Entity *wings = new Entity(0,0, Vec3D(120,40,10));
	m_Player->addPart(wings);

	// Light
	Light *light = new Light(0,0);
	m_Player->addPart(light);

	// For incline of player movement
	m_Player->getTransformation()->m_Rotation = Vec3D(0,1,0);

	// Enemies
	for(int i = 0; i < (m_ScreenWidth-150) / 100; i++){
		for(int j = 0; j < (m_ScreenHeight-200) / 100; j++){
			m_Enemies.push_back(new Enemy(i*50 - (m_ScreenWidth/2) + 200 ,((j*50)-(m_ScreenHeight/2)) + 300,Vec3D(20,20,20)));
		}
	}

	int barricadeSize = 30;

	// Create Barriers
	for(int i = 0; i < 3; i++){
		m_Barricades.push_back(new Entity(i*200,-100,0));
		m_Barricades[i]->setCollisionEnabled(false);  // Damit immer nur kinder-objekte zerstört werden

		m_Barricades[i]->addPart(new Entity(0,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(-barricadeSize,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(barricadeSize,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(-barricadeSize,-barricadeSize,barricadeSize));
		m_Barricades[i]->addPart(new Entity(barricadeSize,-barricadeSize,barricadeSize));
	}

	leftBorder = Entity(-320,0,Vec3D(10,m_ScreenHeight,10));
	rightBorder = Entity(320,0,Vec3D(10,m_ScreenHeight,10));

	Assets::initialize();

	Assets::loadSound("shoot","./assets/shoot.wav");

	// Light

	float fv[] = {1,1,1};

	/*glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT,GL_SPECULAR,fv);
	glMaterialf(GL_FRONT,GL_SHININESS,50);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
	//glEnable(GL_DEPTH_TEST);




	return true;
}

void Game::keyDown(char key){
	m_Keys[key] = true;
}

void Game::keyUp(char key){
	m_Keys[key] = false;

	if(key == 'e'){
		m_Player->getPart("gun")->playAnimation("gunRotation",2);
		m_Lasers.push_back(new Laser(m_Player->getTransformation()->m_Translation.x,m_Player->getTransformation()->m_Translation.y + m_Player->getPart("gun")->getTransformation()->m_Translation.y,1));
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

	// Player-Border Collision
	if((m_Player->getVolicty() < 0 && m_Player->collides(leftBorder) == NULL)
		|| (m_Player->getVolicty() > 0&& m_Player->collides(rightBorder) == NULL)) {
		m_Player->getTransformation()->m_Translation.x += m_Player->getVolicty();
	}

	// Player Laser
	for(auto& laser : m_Lasers){

		// Laser position update
		laser->update();

		// If to far away
		if(laser->getTransformation()->m_Translation.y > m_ScreenHeight/2){
			laser->setActive(false);
		}

		// Barricade Collision
		for(auto& barricade : m_Barricades) {

			Entity *collidingWith = barricade->collides(*laser);

			if (collidingWith != NULL) {
				collidingWith->setActive(false);
				laser->setActive(false);
				break;
			}
		}
	}

	// Gegnerlaser
	for(auto& laser : m_EnemyLasers){
		laser->update();

		if(laser->getTransformation()->m_Translation.y < -(m_ScreenHeight/2)){
			laser->setActive(false);
		}

		// Player collision
		if(m_Player->collides(*laser) != NULL){
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
	glColor3f(1,1,0);
	glutSolidCube(10);
}