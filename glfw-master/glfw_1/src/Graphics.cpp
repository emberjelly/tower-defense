#include "Main.h"

void drawScene (GLFWwindow* window, game *g, int roundX, int roundY, double frameLoadTime) {
	SquareManager *mySquares = g->squares;
	TowerManager *myTowers = g->towers;
	int x;
	int y;
	int i;

	double red1;
	double red2;
	double blue1;
	double blue2;

	// First, draw a little texture into the background, this will be covered up as things are added on top
	for (i = -96*640/480 - SQUARE_SIZE; i < 32*SQUARE_SIZE; i += SQUARE_SIZE) {
		
		glBegin(GL_QUADS);
		glColor3f(0.2,0.2,0.2);
		glVertex2f(i + SQUARE_SIZE - 1, -100);
		glVertex2f(i + SQUARE_SIZE, -100);
		glVertex2f(i + SQUARE_SIZE, 100);
		glVertex2f(i + SQUARE_SIZE - 1, 100);

		glColor3f(0.4,0.4,0.4);
		glVertex2f(i, -100);
		glVertex2f(i + 1, -100);
		glVertex2f(i + 1, 100);
		glVertex2f(i, 100);

		glEnd();
	}

		for (i = -96  - SQUARE_SIZE; i < 24*SQUARE_SIZE; i += SQUARE_SIZE) {
		
		glBegin(GL_QUADS);
		
		glColor3f(0.2,0.2,0.2);
		glVertex2f(-100*640/480, i);
		glVertex2f(100*640/480, i);
		glVertex2f(100*640/480, i + 1);
		glVertex2f(-100*640/480, i + 1);

		glColor3f(0.4,0.4,0.4);
		glVertex2f(-100*640/480, i + SQUARE_SIZE - 1);
		glVertex2f(100*640/480, i + SQUARE_SIZE - 1);
		glVertex2f(100*640/480, i + SQUARE_SIZE);
		glVertex2f(-100*640/480, i + SQUARE_SIZE);

		glEnd();
	}



	// Cycle through every class contained in g, and draw some graphic for each member
	for (i = 0; i < myTowers->getNumTowers(); i ++) {
		glBegin(GL_QUADS);
		


		if (myTowers->getTower(i)->getType() == empty) {
			glColor3f(0, 0, 0.8);
			red1 = 0;
			red2 = 0;
			blue1 = 0.6;
			blue2 = 1;
		} else if ( myTowers->getTower(i)->getType() == gun) {
			glColor3f(0.8, 0, 0);
			red1 = 0.6;
			red2 = 1;
			blue1 = 0;
			blue2 = 0;
		}

		x = myTowers->getTower(i)->getX();
		y = myTowers->getTower(i)->getY();
		
		glVertex2f(x, y);
		glVertex2f(x + SQUARE_SIZE, y);
		glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE);
		glVertex2f(x, y + SQUARE_SIZE);
				
		glColor3f(red1, 0, blue1);
		glVertex2f(x + SQUARE_SIZE - 1, y);
		glVertex2f(x + SQUARE_SIZE, y);
		glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE);
		glVertex2f(x + SQUARE_SIZE - 1, y + SQUARE_SIZE);

		glVertex2f(x, y);
		glVertex2f(x + SQUARE_SIZE, y);
		glVertex2f(x + SQUARE_SIZE, y + 1);
		glVertex2f(x, y + 1);
		
		glColor3f(red2, 0, blue2);
		
		glVertex2f(x, y);
		glVertex2f(x + 1, y);
		glVertex2f(x + 1, y + SQUARE_SIZE);
		glVertex2f(x, y + SQUARE_SIZE);
		
		glVertex2f(x, y + SQUARE_SIZE - 1);
		glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE - 1);
		glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE);
		glVertex2f(x, y + SQUARE_SIZE);
		
		glEnd();
	}

	for (i = 0; i < mySquares->getNumberOfSquare(); i ++) {
		
		x = mySquares->getSquare(i)->getX();
		y = mySquares->getSquare(i)->getY();
		
		glBegin(GL_QUADS);
		glColor3f(mySquares->getSquare(i)->getRed(), mySquares->getSquare(i)->getGreen(), mySquares->getSquare(i)->getBlue());
		glVertex2f(x, y);
		glVertex2f(x + SQUARE_SIZE, y);
		glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE);
		glVertex2f(x, y + SQUARE_SIZE);
		
		glEnd();
	}

#ifndef EDIT_MODE
	//Only draw enemies if not in edit mode
	for (int i = 0; i < g->enemies->getNumOfEnemies(); i ++) {
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex2f(SQUARE_SIZE/2 - 2 + g->enemies->getEnemy(i)->getX(), g->enemies->getEnemy(i)->getY() + SQUARE_SIZE/2 - 2); 
		glVertex2f(SQUARE_SIZE/2 - 2 + g->enemies->getEnemy(i)->getX() + 4, g->enemies->getEnemy(i)->getY() + SQUARE_SIZE/2 - 2);
		glVertex2f(SQUARE_SIZE/2 - 2 + g->enemies->getEnemy(i)->getX() + 4, g->enemies->getEnemy(i)->getY() + 4 + SQUARE_SIZE/2 - 2);
		glVertex2f(SQUARE_SIZE/2 - 2 + g->enemies->getEnemy(i)->getX(), g->enemies->getEnemy(i)->getY() + 4 + SQUARE_SIZE/2 - 2);
		glEnd();
		int hasMoved = g->enemies->getEnemy(i)->moveEnemy(g->enemies->getEnemy(i), 1/frameLoadTime);
		if (!hasMoved) {
			g->enemies->removeEnemy(i);
		}
	}
#endif


	for (i = 0; i < g->projectiles->getNumProjectiles(); i ++) {
	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glVertex2i (g->projectiles->getProjectile(i)->getX(), g->projectiles->getProjectile(i)->getY());
		glVertex2i (g->projectiles->getProjectile(i)->getX() + 2, g->projectiles->getProjectile(i)->getY());
		glVertex2i (g->projectiles->getProjectile(i)->getX() + 2, g->projectiles->getProjectile(i)->getY() + 2);
		glVertex2i (g->projectiles->getProjectile(i)->getX(), g->projectiles->getProjectile(i)->getY() + 2);
	glEnd();
	}

	if (g->menu->isActive()) {
		g->menu->drawMenu(200*640/480, 200);
	}
	
	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glVertex2i (roundX, roundY);
		glVertex2i (roundX + SQUARE_SIZE, roundY);
		glVertex2i (roundX + SQUARE_SIZE, roundY + SQUARE_SIZE);
		glVertex2i (roundX, roundY + SQUARE_SIZE);
	glEnd();


}