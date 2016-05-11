#pragma once

#include <vector>
#include "Enemy.h"
#include "Laser.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	bool init(int sWidth, int sHeight);
	void event();
	void keyDown(char key);
	void keyUp(char key);
	void update();
	void draw();
private:
	int m_ScreenWidth, m_ScreenHeight;

	bool m_Keys[256];

	Player *m_Player;
	vector<Laser*> m_Lasers;
	vector<Laser*> m_EnemyLasers;
	vector<Enemy*> m_Enemies;
	vector<Entity*> m_Barricades;

	Entity leftBorder, rightBorder;

};

