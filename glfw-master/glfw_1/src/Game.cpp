#include <stdlib.h>
#include <math.h>
#include "Game.h"


//This file is involved with creating new games, saving games in edit mode, loading existing game, updating the game state etc...


game *loadGame(IniFile *ini) {
	game *newGame = new game;
	int i;
	int count;
	EnemyMoveList myList;

	newGame->enemies = new EnemyManager;
	newGame->squares = new SquareManager;
	newGame->towers = new TowerManager;
	newGame->projectiles = new ProjectileManager;
	newGame->menu = new TowerMenu;
	newGame->player = new Player;
	newGame->menu->addButton("CLOSE");
	newGame->menu->addButton("GUN");

	int direction = 0;
	if ((ini->getSection("Path")->getkeyCount()) > 1) { 
		if (atoi(ini->getSection("Path")->getKey(1)->getName()) > atoi(ini->getSection("Path")->getKey(0)->getName())) {
			direction = 2; //East
		}

		if (atoi(ini->getSection("Path")->getKey(1)->getValue()) > atoi(ini->getSection("Path")->getKey(0)->getValue())) {
			direction = 0; //North
		}

		if (atoi(ini->getSection("Path")->getKey(1)->getName()) < atoi(ini->getSection("Path")->getKey(0)->getName())) {
			direction = 3; //West
		}

		if (atoi(ini->getSection("Path")->getKey(1)->getValue()) < atoi(ini->getSection("Path")->getKey(0)->getValue())) {
			direction = 1; //South
		}

		myList = newList(atoi(ini->getSection("Path")->getKey(0)->getName()), atoi(ini->getSection("Path")->getKey(0)->getValue()), direction);
		newGame->squares->addSquare(atoi(ini->getSection("Path")->getKey(0)->getName()), atoi(ini->getSection("Path")->getKey(0)->getValue()), 0, 0, 0);
		count = ini->getSection("Path")->getkeyCount();

		for (i = 1; i < count - 2; i ++) {
			if (atoi(ini->getSection("Path")->getKey(i + 1)->getName()) > atoi(ini->getSection("Path")->getKey(i)->getName())) {
				direction = 2; //East
			}

			if (atoi(ini->getSection("Path")->getKey(i + 1)->getValue()) > atoi(ini->getSection("Path")->getKey(i)->getValue())) {
				direction = 0; //North
			}
			
			if (atoi(ini->getSection("Path")->getKey(i + 1)->getName()) < atoi(ini->getSection("Path")->getKey(i)->getName())) {
				direction = 3; //West
			}

			if (atoi(ini->getSection("Path")->getKey(i + 1)->getValue()) < atoi(ini->getSection("Path")->getKey(i)->getValue())) {
				direction = 1; //South
			}
			
			addNode(myList, atoi(ini->getSection("Path")->getKey(i)->getName()), atoi(ini->getSection("Path")->getKey(i)->getValue()), direction);
			newGame->squares->addSquare(atoi(ini->getSection("Path")->getKey(i)->getName()), atoi(ini->getSection("Path")->getKey(i)->getValue()), 0, 0, 0);
		}
		addNode(myList, atoi(ini->getSection("Path")->getKey(i+1)->getName()), atoi(ini->getSection("Path")->getKey(i+1)->getValue()), direction);
		newGame->squares->addSquare(atoi(ini->getSection("Path")->getKey(i)->getName()), atoi(ini->getSection("Path")->getKey(i)->getValue()), 0, 0, 0);
		newGame->squares->addSquare(atoi(ini->getSection("Path")->getKey(i+1)->getName()), atoi(ini->getSection("Path")->getKey(i+1)->getValue()), 0, 0, 0);
	} else {
		myList = newList(atoi(ini->getSection("Path")->getKey(0)->getName()), atoi(ini->getSection("Path")->getKey(0)->getValue()), direction);
	}
	

	newGame->enemies->setMasterPath(myList);
	count = ini->getSection("Squares")->getkeyCount();
	for (i = 0; i < count; i ++) {
		newGame->squares->addSquare(atoi(ini->getSection("Squares")->getKey(i)->getName()), atoi(ini->getSection("Squares")->getKey(i)->getValue()), 0.5, 0.5, 0.5);
	}


	count = ini->getSection("Towers")->getkeyCount();
	for (i = 0; i < count; i ++) {
		newGame->towers->addTower(atoi(ini->getSection("Towers")->getKey(i)->getName()), atoi(ini->getSection("Towers")->getKey(i)->getValue()), empty);
	}

	return newGame;
}


void saveGame (Game g) {
	
	//Create a new ini file to store the data in
	IniFile *map = new IniFile;

	//Add the relevant sections
	map->addSection("Squares");
	map->addSection("Path");
	map->addSection("Towers");

	//Strings to store the values in
	char xBuf[8];
	char yBuf[8];
	
	int count;
	//For each square, if it is green, it is a path, if not it is not a path
	for (count = 0; count < g->squares->getNumberOfSquare(); count ++) {
		if ((int)g->squares->getSquare(count)->getGreen() == 1) {
			itoa(g->squares->getSquare(count)->getX(), xBuf, 10);
			itoa(g->squares->getSquare(count)->getY(), yBuf, 10);
			
			//Add a key where the x value is the key name and the y value is the key value.
			map->getSection("Path")->addKey(xBuf, yBuf);
		}
		
		if ((int)g->squares->getSquare(count)->getGreen() != 1) {
			itoa(g->squares->getSquare(count)->getX(), xBuf, 10);
			itoa(g->squares->getSquare(count)->getY(), yBuf, 10);
			map->getSection("Squares")->addKey(xBuf, yBuf);
		}
	}

	//Do the same with the tower positions.
	for (count = 0; count < g->towers->getNumTowers(); count ++) {
		itoa(g->towers->getTower(count)->getX(), xBuf, 10);
		itoa(g->towers->getTower(count)->getY(), yBuf, 10);
		map->getSection("Towers")->addKey(xBuf, yBuf);
	}
	saveIni(map, "test.ini");
}


double getDistance(double x1, double y1, double x2, double y2) {
	double result;
	result = sqrt((x1- x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return result;
}



void update(Game g, double frameRate) {

	int i;
	bool coolDownComplete;
	double distance = -1;

	double towerX;
	double towerY;
	double enemyX;
	double enemyY;


	
	int targetNum = -1; //-1 is an invalid enemy number

	//Cycle through towers and update their cooldown
	for ( i = 0; i < g->towers->getNumTowers(); i ++ ) {
		coolDownComplete = g->towers->getTower(i)->updateState(frameRate);

		//If a tower has completed its cooldown, see if it has an available target
		if (coolDownComplete) {
			
			//First, make sure the tower square has something built on it
			if (g->towers->getTower(i)->getType() != empty) {

				for (int j = 0; j < g->enemies->getNumOfEnemies(); j ++) {
					
					//Get the distance between the tower and the enemy
					towerX = g->towers->getTower(i)->getX();
					towerY = g->towers->getTower(i)->getY();
					enemyX = g->enemies->getEnemy(j)->getX();
					enemyY = g->enemies->getEnemy(j)->getY();
					distance = getDistance(towerX, towerY, enemyX, enemyY);
					
					//Check to see if it is range
					if (distance < (g->towers->getTower(i)->getRange())) {
						
						//If it is, make sure there is a valid target that has previously been set to compare to
						if (targetNum >= 0) {
							
							//If there has, compare the length of each enemies path, the shortest path is the enemy that has the highest priority as it is closest to the end
							if (getEnemyListLength(g->enemies->getEnemy(j)->getPath()) < getEnemyListLength(g->enemies->getEnemy(targetNum)->getPath())) {
							
								//If the path is shorter, we have found a better target for the tower, otherwise just leave it as it was
								targetNum = j;
							}
						} else {

							//If not, we have found a new target for the tower
							targetNum = j;
						}
					}
				}
			}
			//Now we have a target, we can create a bullet that will move from the tower to the target

			//First, check That a target was found
			if (targetNum >= 0) {

				//Now, find out what type of tower it is, and add a bullet that corresponds to the tower type
				if (g->towers->getTower(i)->getType() == gun) {
					g->projectiles->addProjectile((double)(g->towers->getTower(i)->getX() + SQUARE_SIZE/2), (double)(g->towers->getTower(i)->getY() + SQUARE_SIZE/2), bullet);
					g->projectiles->getProjectile((g->projectiles->getNumProjectiles() - 1))->setSpeed(400);
					g->projectiles->getProjectile((g->projectiles->getNumProjectiles() - 1))->setTarget(targetNum);
					//printf("%d\n", g->projectiles->getNumProjectiles());
				}

				// Add more if statements when I add more types of towers1
			}
		}
	}

	//Now update the position of each bullet by moving it towards its target
	int projTarget;
	double targetDistance;
	double bulletX;
	double bulletY;
	double bulletMoveDistance;
	double newY;
	double newX;

	for (i = 0; i < g->projectiles->getNumProjectiles(); i ++) {
		//Calculate the new X and Y coordinates of the projectile
		bulletMoveDistance = g->projectiles->getProjectile(i)->getSpeed()/frameRate;
		projTarget = g->projectiles->getProjectile(i)->getTarget();
		bulletX = g->projectiles->getProjectile(i)->getX();
		bulletY = g->projectiles->getProjectile(i)->getY();
		enemyX = g->enemies->getEnemy(projTarget)->getX();
		enemyY = g->enemies->getEnemy(projTarget)->getY();
		targetDistance = getDistance(bulletX, bulletY, enemyX, enemyY);
		newY = (bulletMoveDistance * (enemyY - bulletY))/ targetDistance;
		newX = (bulletMoveDistance * (enemyX - bulletX))/ targetDistance;
		
		//Only move it if the target still exists, if not, destroy the projectile
		if (g->enemies->getNumOfEnemies() <= g->projectiles->getProjectile(i)->getTarget()) {
			g->projectiles->removeProjectile(i);
		} else if (targetDistance < 0.5) {
			// If the target is close enough for a collision, subtract from the enemy hp
			g->projectiles->removeProjectile(i);
			g->enemies->getEnemy(projTarget)->setHp(g->enemies->getEnemy(projTarget)->GetHp() - 1);
			if (g->enemies->getEnemy(projTarget)->GetHp() <= 0) {
				if (g->enemies->getEnemy(projTarget)->getClass() == drone) {
					g->player->setResources(g->player->getResources() + 10);
				} else if (g->enemies->getEnemy(projTarget)->getClass() == heavy_drone) {
					g->player->setResources(g->player->getResources() + 25);
				}
				g->enemies->removeEnemy(projTarget);
				printf ("Killed an enemy, resources available: %d\n", g->player->getResources());
			}
		} else {
			//(NOTE)This is not an ideal solution but I will think of something better later
			if (getDistance (bulletX, bulletY, enemyX, enemyY) > 50 ) {
				g->projectiles->removeProjectile(i);
				//printf("Bullet is in a position it shouldn't be in\n");
			} else {
				g->projectiles->getProjectile(i)->setX(bulletX + newX);
				g->projectiles->getProjectile(i)->setY(bulletY + newY);
			}
		}

	}
	//Move each bullet towards its target

}
