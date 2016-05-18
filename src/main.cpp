#include "Game.h"

Game game;

void Init()	
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glClearColor(0, 0, 0, 1);

}

void RenderScene() //Zeichenfunktion
{
	game.update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game.draw();

	glutSwapBuffers();

	if(game.getGameOverCounter() > 100){
		exit(EXIT_SUCCESS);
	}

}

void Reshape(int width,int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);

	gluPerspective(45, width/height, 0.1, 10000.0);
	//gluPerspective(45, 1, 0.1, 10000.0);

	glMatrixMode(GL_MODELVIEW);
}

void keyboardUp(unsigned char key, int x, int y){
	game.keyUp(key);
}

void keyboard(unsigned char key, int x, int y)
{
	game.keyDown(key);

	switch (key)
	{
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	}
}


void Animate (int value)    
{
   glutPostRedisplay();
   glutTimerFunc(16, Animate, ++value);
}

int main(int argc, char **argv)
{
   glutInit( &argc, argv );                
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize( 800, 600 );
	//1280x1024
   glutCreateWindow( "Tim und Daniel" );
   glutDisplayFunc( RenderScene );        
   glutReshapeFunc( Reshape );

   glutTimerFunc( 16, Animate, 0);
   glutKeyboardFunc(&keyboard);
	glutKeyboardUpFunc(&keyboardUp);
   
   if (game.init(800, 600) == false){
	   cout << "Error" << endl;
	   return 1;
   }
   
   Init();
   glutMainLoop();


   return 0;
}
