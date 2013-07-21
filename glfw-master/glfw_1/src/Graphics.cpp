#include "Main.h"

void drawScene (GLFWwindow* window, game *g, int roundX, int roundY, double frameLoadTime) {
	SquareManager *mySquares = g->squares;
	TowerManager *myTowers = g->towers;
	int x;
	int y;
	int i;

	GLfloat red1 = 0;
	GLfloat red2 = 0;
	GLfloat blue1 = 0;
	GLfloat blue2 = 0;
	GLfloat green1 = 0;
	GLfloat green2 = 0;


	// First, draw a little texture into the background, this will be covered up as things are added on top
	for (i = -96*640/480 - SQUARE_SIZE; i < 32*SQUARE_SIZE; i += SQUARE_SIZE) {
		
		glBegin(GL_QUADS);
		glColor3f(0.2f, 0.2f, 0.2f);
		glVertex2i(i + SQUARE_SIZE - 1, -100);
		glVertex2i(i + SQUARE_SIZE, -100);
		glVertex2i(i + SQUARE_SIZE, 100);
		glVertex2i(i + SQUARE_SIZE - 1, 100);

		glColor3f(0.4f, 0.4f, 0.4f);
		glVertex2i(i, -100);
		glVertex2i(i + 1, -100);
		glVertex2i(i + 1, 100);
		glVertex2i(i, 100);

		glEnd();
	}

		for (i = -96  - SQUARE_SIZE; i < 24*SQUARE_SIZE; i += SQUARE_SIZE) {
		
		glBegin(GL_QUADS);
		
		glColor3f(0.2f, 0.2f, 0.2f);
		glVertex2i(-100*640/480, i);
		glVertex2i(100*640/480, i);
		glVertex2i(100*640/480, i + 1);
		glVertex2i(-100*640/480, i + 1);

		glColor3f(0.4f, 0.4f, 0.4f);
		glVertex2i(-100*640/480, i + SQUARE_SIZE - 1);
		glVertex2i(100*640/480, i + SQUARE_SIZE - 1);
		glVertex2i(100*640/480, i + SQUARE_SIZE);
		glVertex2i(-100*640/480, i + SQUARE_SIZE);

		glEnd();
	}



	// Cycle through every class contained in g, and draw some graphic for each member
	for (i = 0; i < myTowers->getNumTowers(); i ++) {
		glBegin(GL_QUADS);
		


		if (myTowers->getTower(i)->getType() == empty) {
			glColor3f(0.0f, 0.0f, 0.8f);
			red1 = 0;
			red2 = 0;
			blue1 = 0.6;
			blue2 = 1;
			green1 = 0;
			green2 = 0;
		} else if ( myTowers->getTower(i)->getType() == gun) {
			glColor3f(0.8f, 0.0f, 0.0f);
			red1 = 0.6;
			red2 = 1;
			blue1 = 0;
			blue2 = 0;
			green1 = 0;
			green2 = 0;
		} else if ( myTowers->getTower(i)->getType() == machine_gun) {
			glColor3f(0.8f, 0.0f, 0.6f);
			red1 = 0.6;
			red2 = 2.0;
			blue1 = 0.4;
			blue2 = 0.8;
			green1 = 0;
			green2 = 0;
		} else if ( myTowers->getTower(i)->getType() == lazer) {
			glColor3f(0.0f, 0.6f, 0.0f);
			red1 = 0;
			red2 = 0;
			blue1 = 0;
			blue2 = 0;
			green1 = 0.4;
			green2 = 0.8;
		}

		x = myTowers->getTower(i)->getX();
		y = myTowers->getTower(i)->getY();
		
		glVertex2f(x, y);
		glVertex2f(x + SQUARE_SIZE, y);
		glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE);
		glVertex2f(x, y + SQUARE_SIZE);
				
		glColor3f(red1, green1, blue1);
		glVertex2f(x + SQUARE_SIZE - 1, y);
		glVertex2f(x + SQUARE_SIZE, y);
		glVertex2f(x + SQUARE_SIZE, y + SQUARE_SIZE);
		glVertex2f(x + SQUARE_SIZE - 1, y + SQUARE_SIZE);

		glVertex2f(x, y);
		glVertex2f(x + SQUARE_SIZE, y);
		glVertex2f(x + SQUARE_SIZE, y + 1);
		glVertex2f(x, y + 1);
		
		glColor3f(red2, green2, blue2);
		
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

		if (g->enemies->getEnemy(i)->getClass() == drone) {
			glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex2f(SQUARE_SIZE/2 - 2 + g->enemies->getEnemy(i)->getX(), g->enemies->getEnemy(i)->getY() + SQUARE_SIZE/2 - 2); 
				glVertex2f(SQUARE_SIZE/2 - 2 + g->enemies->getEnemy(i)->getX() + 4, g->enemies->getEnemy(i)->getY() + SQUARE_SIZE/2 - 2);
				glVertex2f(SQUARE_SIZE/2 - 2 + g->enemies->getEnemy(i)->getX() + 4, g->enemies->getEnemy(i)->getY() + 4 + SQUARE_SIZE/2 - 2);
				glVertex2f(SQUARE_SIZE/2 - 2 + g->enemies->getEnemy(i)->getX(), g->enemies->getEnemy(i)->getY() + 4 + SQUARE_SIZE/2 - 2);
			glEnd();
		}
		
		if (g->enemies->getEnemy(i)->getClass() == heavy_drone) {
			glBegin(GL_QUADS);
				glColor3f(0.5, 0, 0);
				glVertex2f(SQUARE_SIZE/2 - 3 + g->enemies->getEnemy(i)->getX(), g->enemies->getEnemy(i)->getY() + SQUARE_SIZE/2 - 3); 
				glVertex2f(SQUARE_SIZE/2 - 3 + g->enemies->getEnemy(i)->getX() + 6, g->enemies->getEnemy(i)->getY() + SQUARE_SIZE/2 - 3);
				glVertex2f(SQUARE_SIZE/2 - 3 + g->enemies->getEnemy(i)->getX() + 6, g->enemies->getEnemy(i)->getY() + 6 + SQUARE_SIZE/2 - 3);
				glVertex2f(SQUARE_SIZE/2 - 3 + g->enemies->getEnemy(i)->getX(), g->enemies->getEnemy(i)->getY() + 6 + SQUARE_SIZE/2 - 3);
			glEnd();
		}

		int hasMoved = g->enemies->getEnemy(i)->moveEnemy(g->enemies->getEnemy(i), 1/frameLoadTime);
		if (!hasMoved) {
			g->player->setHp(g->player->getHp() - 1);
			printf("An enemy got through. HP is now %d\n", g->player->getHp());
			g->enemies->removeEnemy(i);
			if (g->player->getHp() <= 0 ) {
				printf("The game was lost\n");
			}
		}
	}
#endif


	for (i = 0; i < g->projectiles->getNumProjectiles(); i ++) {
		if (g->projectiles->getProjectile(i)->getType() == bullet) {
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glVertex2f (g->projectiles->getProjectile(i)->getX(), g->projectiles->getProjectile(i)->getY());
			glVertex2f (g->projectiles->getProjectile(i)->getX() + 2, g->projectiles->getProjectile(i)->getY());
			glVertex2f (g->projectiles->getProjectile(i)->getX() + 2, g->projectiles->getProjectile(i)->getY() + 2);
			glVertex2f (g->projectiles->getProjectile(i)->getX(), g->projectiles->getProjectile(i)->getY() + 2);
			glEnd();
		} else if ( g->projectiles->getProjectile(i)->getType() == lazer_beam) {
			glBegin(GL_LINES);
			glColor3f(1, 1, 1);
			int towerNum = g->projectiles->getProjectile(i)->getTowerNumber();
			int enemyNum = g->projectiles->getProjectile(i)->getTarget();
			glVertex2f ((float)(g->towers->getTower(towerNum)->getX()) + SQUARE_SIZE/2, (float)(g->towers->getTower(towerNum)->getY()) + SQUARE_SIZE/2);
			glVertex2f (g->enemies->getEnemy(enemyNum)->getX() + SQUARE_SIZE/2,g->enemies->getEnemy(enemyNum)->getY() + SQUARE_SIZE/2);

			glEnd();

		}

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
