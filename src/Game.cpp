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
	m_IsRunning = true;
	m_GameOverCounter = 0;
	m_GameWonCounter = 0;

	gluPerspective(45, sWidth/sHeight, 0.1, 10000.0);

	srand(time(NULL));

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

	// For incline of player movement
	m_Player->getTransformation()->m_Rotation = Vec3D(0,1,0);

	// Enemies
	for(int i = 0; i < (m_ScreenWidth-150) / 100; i++){
		for(int j = 0; j < (m_ScreenHeight-200) / 100; j++){

			Enemy *newEnemy = new Enemy(i*80 - (m_ScreenWidth/2) + 200 ,(j*80) + 300,Vec3D(30,20,10));

			// Gun with Animation
			Entity *enemyGun = new Entity(0,-15,Vec3D(8,15,10));
			Animation *enemyShoot = new Animation();
			enemyShoot->addAnimationPart(AnimationPart(Transformation(Vec3D(0,5,0),Vec3D(),Vec3D(),0),12));
			enemyShoot->addAnimationPart(AnimationPart(Transformation(Vec3D(0,-5,0),Vec3D(),Vec3D(),0),20));
			enemyGun->addAnimation("shoot",enemyShoot);
			newEnemy->addPart("laserGun",enemyGun);

			// Cockpits
			newEnemy->addPart("cockpit1",new Entity(5,-4,Vec3D(5,5,5)));
			newEnemy->getPart("cockpit1")->getTransformation()->m_Translation.z = 5;
			newEnemy->getPart("cockpit1")->getTransformation()->m_Rotation.y = 1;
			newEnemy->getPart("cockpit1")->getTransformation()->m_Angle = 90;
			newEnemy->addPart("cockpit2",new Entity(-5,-4,Vec3D(5,5,5)));
			newEnemy->getPart("cockpit2")->getTransformation()->m_Translation.z = 5;
			newEnemy->getPart("cockpit2")->getTransformation()->m_Rotation.y = 1;
			newEnemy->getPart("cockpit2")->getTransformation()->m_Angle = 90;
			// Arms
			newEnemy->addPart(new Entity(18,-5,Vec3D(8,25,10)));
			newEnemy->addPart(new Entity(-18,-5,Vec3D(8,25,10)));

			m_Enemies.push_back(newEnemy);
		}
	}

	int barricadeSize = 30;

	// Create Barriers
	for(int i = 0; i < 3; i++){
		m_Barricades.push_back(new Entity(i*200 - 200,-100,0));
		m_Barricades[i]->setCollisionEnabled(false);  // Damit immer nur kinder-objekte zerstört werden

		m_Barricades[i]->addPart(new Entity(0,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(-barricadeSize,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(barricadeSize,0,barricadeSize));
		m_Barricades[i]->addPart(new Entity(-barricadeSize,-barricadeSize,barricadeSize));
		m_Barricades[i]->addPart(new Entity(barricadeSize,-barricadeSize,barricadeSize));
	}

	//m_LeftBorder = Entity(-320 + 20,0,Vec3D(10,m_ScreenHeight,10));
	//m_RightBorder = Entity( 320,0,Vec3D(10,m_ScreenHeight,10));
	m_LeftBorder = Entity(-320, 0, Vec3D(10, m_ScreenHeight*2, 10));
	m_RightBorder = Entity(320, 0, Vec3D(10, m_ScreenHeight*2, 10));
	//m_RightBorder = Entity((m_ScreenWidth/2)-(m_ScreenWidth*0.2),0,Vec3D(10,m_ScreenHeight,10));

	// Stars in Background
	int rX, rY;
	for(int i = 0; i < 200; i++){
		rX = rand()%(m_ScreenWidth/2+m_ScreenWidth/2)-m_ScreenWidth/2;
		rY = rand()%(m_ScreenHeight/2+m_ScreenHeight/2 + 350)-(m_ScreenHeight/2 + 350) + (350);

		m_Stars.push_back(new Entity(rX,rY,1));
	}

	Assets::initialize();

	Assets::loadSound("pew","./gameMusic/pew.wav");
	Assets::loadSound("explosion","./gameMusic/brauw.wav");
	Assets::loadSound("gameOver","./gameMusic/GameOver.wav");
	Assets::loadSound("win","./gameMusic/win.wav");

	// Light

	// Ambient light 0.5
	GLfloat global_ambient[] = { 0.85, 0.85, 0.85, 0.85 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuseLight[] = { 1, 1, 1, 1.0 };

	GLfloat mat_shininess[] = { 50.0 };
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);

	GLfloat spec[] = { 0, 0.8, 0, 1};
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	return true;
}

void Game::keyDown(char key){
	m_Keys[key] = true;
}

void Game::keyUp(char key){
	m_Keys[key] = false;
}

void Game::event(){
	m_Player->update(m_Keys);

	if(m_Keys['e']){
		if(m_Player->shoot()){
			m_Lasers.push_back(new Laser(m_Player->getTransformation()->m_Translation.x,m_Player->getTransformation()->m_Translation.y + m_Player->getPart("gun")->getTransformation()->m_Translation.y,5));
			m_Lasers.back()->setColor(Vec3D(0,1,0));
			Assets::playSound("pew");
		}
	}
}

/*
 *
 */
void Game::update(){

	if(m_IsRunning == false){
		if(m_GameOverCounter > 0)
			m_GameOverCounter++;
		else
			m_GameWonCounter++;
		return;
	}

	event();

	// Player-Border Collision
	if((m_Player->getVolicty() < 0 && m_Player->collides(m_LeftBorder) == NULL)
		|| (m_Player->getVolicty() > 0&& m_Player->collides(m_RightBorder) == NULL)) {
		m_Player->getTransformation()->m_Translation.x += m_Player->getVolicty();
	}

	// Player Laser
	for(auto& laser : m_Lasers){

		// Laser position update
		laser->update();

		// If to far away
		if(laser->getTransformation()->m_Translation.y > m_ScreenHeight*2){
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
			m_Player->setLives(m_Player->getLives()-1);
			if(m_Player->getLives() < 1){
				Assets::playSound("gameOver");
				m_IsRunning = false;
				m_GameOverCounter = 1;
			}
			break;
		}
	}

	// Enemy -> Wall Collision
	for(auto& enemy: m_Enemies){

		if(enemy->collides(m_LeftBorder)){
			Enemy::Direction = 'r';
			for(auto& enemyInner : m_Enemies){
				enemyInner->getTransformation()->m_Translation.y -= 10;
			}
			break;
		}else if(enemy->collides(m_RightBorder)){
			Enemy::Direction = 'l';
			for(auto& enemyInner : m_Enemies){
				enemyInner->getTransformation()->m_Translation.y -= 10;
			}
			break;
		}
	}

	// Enemy Update
	for(auto& enemy : m_Enemies){

		enemy->update();

		// Shooting 1 to 1000 probability per frame per enemy
		int random = rand() % 2000;
		if(random == 42){
			m_EnemyLasers.push_back(new Laser(enemy->getTransformation()->m_Translation.x + enemy->getTransformation()->m_Scale.x/2,enemy->getTransformation()->m_Translation.y,false));
			m_EnemyLasers.back()->setColor(Vec3D(1,0,0));
			enemy->getPart("laserGun")->playAnimation("shoot",1);
			Assets::playSound("pew");
		}

		// Check collision with lasers
		for(auto& laser : m_Lasers){

			Entity *collidingWith = enemy->collides(*laser);

			if(collidingWith != NULL){
				laser->setActive(false);
				enemy->setActive(false);
				Assets::playSound("explosion");
				break;
			}
		}
	}

	// Enemy Laser -> Barricade Collision
	for(auto& laser : m_EnemyLasers) {
		for (auto &barricade : m_Barricades) {

			Entity *collidingWith = barricade->collides(*laser);

			if (collidingWith != NULL) {
				collidingWith->setActive(false);
				laser->setActive(false);
				break;
			}
		}
	}

	// Deleting of objects if they are inactive

	//TODO: Maybe delete objekt with children
	for(int i = 0; i < m_Lasers.size(); i++){

		m_Lasers[i]->deleteInactiveChildren();

		if(m_Lasers[i]->isActive() == false){
			m_Lasers.erase(m_Lasers.begin() + i);
		}
	}

	for(int i = 0; i < m_EnemyLasers.size(); i++){

		m_EnemyLasers[i]->deleteInactiveChildren();

		if(m_EnemyLasers[i]->isActive() == false){
			m_EnemyLasers.erase(m_EnemyLasers.begin() + i);
		}
	}

	for(int i = 0; i < m_Enemies.size(); i++){

		m_Enemies[i]->deleteInactiveChildren();

		if(m_Enemies[i]->isActive() == false){
			m_Enemies.erase(m_Enemies.begin() + i);
		}
	}

	if(m_Enemies.size() == 0){
		m_IsRunning = false;
		m_GameWonCounter = 1;
		Assets::playSound("win");
	}

	for(int i = 0; i < m_Barricades.size(); i++){

		m_Barricades[i]->deleteInactiveChildren();

		if(m_Barricades[i]->getParts()->size() < 1){
			m_Barricades.erase(m_Barricades.begin() + i);
		}
	}



}

void Game::draw(){

	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	gluLookAt(0,0,m_ScreenWidth,0,0,0,0,1,0);

	glRotatef(m_GameOverCounter*3.6,0,0,1);

	glRotatef(-45,1,0,0);

	if(m_Lasers.size() > 0){
		glEnable(GL_LIGHT0);
		GLfloat lightPos[] = {m_Lasers.back()->getTransformation()->m_Translation.x,
							  m_Lasers.back()->getTransformation()->m_Translation.y,
							  m_Lasers.back()->getTransformation()->m_Translation.z,1};
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	}else{
		glDisable(GL_LIGHT0);
	}

	for (auto& star: m_Stars){
		star->draw();
	}

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

	for (auto& laser : m_EnemyLasers){
		laser->draw();
	}
}
