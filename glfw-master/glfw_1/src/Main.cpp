#include "Main.h"
//#define EDIT_MODE

double getDistance(double x1, double y1, double x2, double y2);

// Keyboard buffering
bool key_states[259];

// Stores mouse coordinates
double mouseX;
double mouseY;


static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS) {
		key_states[key] = TRUE;
		//printf ("%c was pressed\n", key);
	}
	if (action == GLFW_RELEASE) {
		key_states[key] = FALSE;
		//printf ("%c was released\n", key);
	}
}

static void mouse (GLFWwindow* window, int button, int action, int mods) {
	if( button== GLFW_MOUSE_BUTTON_LEFT  && action == GLFW_PRESS)
	{
		key_states[256] = TRUE;
	}
	if( button== GLFW_MOUSE_BUTTON_LEFT  && action == GLFW_RELEASE)
	{
		key_states[256] = FALSE;
	}
	if( button== GLFW_MOUSE_BUTTON_RIGHT  && action == GLFW_PRESS)
	{
		key_states[257] = TRUE;
	}
	if( button== GLFW_MOUSE_BUTTON_RIGHT  && action == GLFW_RELEASE)
	{
		key_states[257] = FALSE;
	}
	if( button== GLFW_MOUSE_BUTTON_MIDDLE  && action == GLFW_PRESS)
	{
		key_states[258] = TRUE;
	}
	if( button== GLFW_MOUSE_BUTTON_MIDDLE  && action == GLFW_RELEASE)
	{
		key_states[258] = FALSE;
	}

}

void cursorPosCallback(GLFWwindow* window ,double x , double y ) {
	mouseX = (2*x/4.8 - 100*640/480);
	mouseY = -(2*y/4.8 - 100);
	//printf( "%f   %f\n" , mouseX , mouseY);

}


int main(void)
{
	IniFile *myIni = loadIni("map.ini");
	game *g;
	
	//These are used to draw towers and square so we don't have to use g the whole time
	SquareManager *mySquares;
	TowerManager *myTowers;

//Set up the game according to the mode
#ifndef EDIT_MODE
	//If not in edit mode, load the current game saved to the ini file
	g = loadGame(myIni);
#endif
#ifdef EDIT_MODE
	//If in edit mode, set up an empty game for the user to put things into
	g = new game;
	g->enemies = new EnemyManager;
	g->squares = new SquareManager;
	g->towers = new TowerManager;
	g->projectiles = new ProjectileManager;
	g->menu = new TowerMenu;
	g->player = new Player;

#endif
	
	//Point to g to access the game data
	mySquares = g->squares;
	myTowers = g->towers;

	//Set up the key states
	int i;
	for (i = 0; i < 259; i++) key_states[i] = 0;

	int towerNumberSelected = 0;
	double start_time = 0; //The start time of the next frame
	double end_time = 0; //The finish time of the next frame
	double frameLoadTime = 0.001; //Time the last frame took to draw
	double epsilon = 1;
	double ratio; //The ratio of screen width to height
	double timerTest = 0;
	int width, height; //Width and height of the window

	int roundX; //The X position of the mouse rounded of to the nearest "SQUARE_SIZE" position
	int roundY; //The Y position of the mouse rounded of to the nearest "SQUARE_SIZE" position

	bool waitForStart = FALSE;

	GLFWwindow* window;
	
	glfwSetErrorCallback(error_callback);
	
	//Tests to make sure glfw properly initialises
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Tower Defense", NULL, NULL);
	
	//Make sure window was properly created
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);
	
	//Input functions for mouse and keyboard
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	
	//Set background colour
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// select projection matrix
	glMatrixMode(GL_PROJECTION);

	//Initiate main loop
	while (!glfwWindowShouldClose(window))
	{
		//The time we started the frame
		start_time = (double)glfwGetTime();
		
		roundX = (int)(mouseX/SQUARE_SIZE)*SQUARE_SIZE; //Use integer rounding to set the value of the mouse X to the nearest SQUARE_SIZE position
		roundY = (int)(mouseY/SQUARE_SIZE)*SQUARE_SIZE; //Use integer rounding to set the value of the mouse Y to the nearest SQUARE_SIZE position
		
		//This is for a special case as the mouse position moves  from positive to negative, because at this point, intergers change from allways
		//Rounding down, to rounding up when the value is negative
		if (mouseX < 0) {
			roundX -= SQUARE_SIZE;
		}
		if (mouseY < -0) {
			roundY -= SQUARE_SIZE;
		}

		//printf("%d   %d\n", roundX, roundY);


#ifndef EDIT_MODE
		
		// Some test code, adds enemies with varying speeds when number keys are pressed
		for (int keys = 1; keys < 10; keys ++ ) {
			if (key_states[keys + '0']) {
				g->enemies->addEnemy(drone, keys*20, g->enemies->getMasterPath());
				g->enemies->getEnemy(g->enemies->getNumOfEnemies() - 1)->setX(getFirstX(g->enemies->getMasterPath()));
				g->enemies->getEnemy(g->enemies->getNumOfEnemies() - 1)->setY(getFirstY(g->enemies->getMasterPath()));
				key_states[keys + '0'] = FALSE;
			}
		}

		// Changes the type of a tower square from "empty" to "gun" when it is clicked
		if (key_states[256]) {
			if (g->menu->isActive()) {
				key_states[256] = false;
				//printf("%d    %d     %d     %d\n", roundX, g->menu->getButtonByName("GUN")->getX(), roundY, g->menu->getButtonByName("GUN")->getY());
				//(NOTE) Might add a cost member to the tower class to make this a bit more flexible
				int buttonX = g->menu->getButtonByName("GUN")->getX();
				if ((roundX == buttonX || roundX == buttonX + SQUARE_SIZE || roundX == buttonX + 2*SQUARE_SIZE || roundX == buttonX + 3*SQUARE_SIZE) && roundY == g->menu->getButtonByName("GUN")->getY()) {
					//printf("clicked Button GUN\n");
					if (g->player->getResources() >= 100) {
						g->towers->getTower(towerNumberSelected)->setType(gun);
						g->menu->deactivateMenu();
						g->player->setResources(g->player->getResources() - 100);
						printf("Current resources %d\n", g->player->getResources());
						waitForStart = TRUE;
					} else {
						printf("Not enought resources for this, currently have %d\n",g->player->getResources());
					}
				}
				
				buttonX = g->menu->getButtonByName("MACHINE_GUN")->getX();
				if ((roundX == buttonX || roundX == buttonX + SQUARE_SIZE || roundX == buttonX + 2*SQUARE_SIZE || roundX == buttonX + 3*SQUARE_SIZE) && roundY == g->menu->getButtonByName("MACHINE_GUN")->getY()) {
					//printf("clicked Button GUN\n");
					if (g->player->getResources() >= 200) {
						g->towers->getTower(towerNumberSelected)->setType(machine_gun);
						g->menu->deactivateMenu();
						g->player->setResources(g->player->getResources() - 200);
						printf("Current resources %d\n", g->player->getResources());
						waitForStart = TRUE;
					} else {
						printf("Not enought resources for this, currently have %d\n",g->player->getResources());
					}
				}

				buttonX = g->menu->getButtonByName("CLOSE")->getX();
				if (((roundX == buttonX) || (roundX == buttonX + SQUARE_SIZE) || (roundX == buttonX + 2*SQUARE_SIZE) || (roundX == buttonX + 3*SQUARE_SIZE)) && roundY == g->menu->getButtonByName("CLOSE")->getY()) {
					//printf("clicked Button CLOSE\n");
					g->menu->deactivateMenu();
				}

			} else {
				for (int i = 0; i < g->towers->getNumTowers(); i ++) {
					if (roundX == g->towers->getTower(i)->getX() && roundY == g->towers->getTower(i)->getY()) {
						towerNumberSelected = i;
						if (g->towers->getTower(i)->getType() == empty) {
							g->menu->activateMenu();
						}
						key_states[256] = false;
					}
				}
			}
		}

	if (waitForStart) {
		if (glfwGetTime() - timerTest > epsilon) {
			timerTest = glfwGetTime();
			epsilon = 0.6;
			//printf("%f\n", epsilon);
			if (glfwGetTime() > 60) {
				g->enemies->addEnemy(heavy_drone, rand()%30 + 20, g->enemies->getMasterPath());
				epsilon = 0.8;
			} else {
				g->enemies->addEnemy(drone, rand()%60 + 20, g->enemies->getMasterPath());
			}

			if (glfwGetTime() > 140) {
				epsilon = 0.5;
			}
			g->enemies->getEnemy(g->enemies->getNumOfEnemies() - 1)->setX(getFirstX(g->enemies->getMasterPath()));
			g->enemies->getEnemy(g->enemies->getNumOfEnemies() - 1)->setY(getFirstY(g->enemies->getMasterPath()));
		}
	}
	


#endif

#ifdef EDIT_MODE
			
			
		//Note: The values of key_states at 256 257 and 258 correspond to the mouse button states (left right middle)
		if (key_states[257]) {

		// A bunch of if statements to make sure the user is allowed to draw a path square in the selected location, stops illegal paths being drawn
		if (mySquares->getSquareByCoords(roundX, roundY) == NULL) {
			if (mySquares->getNumberOfSquare() > 0) {
				if ((mySquares->getSquare(mySquares->getNumberOfSquare() - 1)->getX() == roundX + SQUARE_SIZE && mySquares->getSquare(mySquares->getNumberOfSquare() - 1)->getY() == roundY) ||
					(mySquares->getSquare(mySquares->getNumberOfSquare() - 1)->getX() == roundX - SQUARE_SIZE && mySquares->getSquare(mySquares->getNumberOfSquare() - 1)->getY() == roundY) ||
					(mySquares->getSquare(mySquares->getNumberOfSquare() - 1)->getY() == roundY + SQUARE_SIZE && mySquares->getSquare(mySquares->getNumberOfSquare() - 1)->getX() == roundX)||
					(mySquares->getSquare(mySquares->getNumberOfSquare() - 1)->getY() == roundY - SQUARE_SIZE && mySquares->getSquare(mySquares->getNumberOfSquare() - 1)->getX() == roundX)) {
						
					mySquares->addSquare (roundX, roundY, 0, 1, 0);
					} 
				} else {
					mySquares->addSquare (roundX, roundY, 0, 1, 0);
				}
			}
		} else if (key_states[258]) {
			if (myTowers->getTowerByCoods(roundX, roundY) == NULL) {
				myTowers->addTower(roundX, roundY, empty);
			}
		}

		// Saves the current path to the ini file So it can be loaded next time the game starts not in edit mode
		if (key_states['I']) {
			saveGame(g);
			key_states['I'] = FALSE;
		}
#endif

		
		//Setup for drawing
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (double) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		
		//set the coordinate system to the identity matrix	
		glLoadIdentity();
		
		//No particular reason for choosing 100 units accross, may change this later if needed, just for testing
		glOrtho(-ratio*100, ratio*100, -100.f, 100.f, 1.f, -1.f);
		
		glMatrixMode(GL_MODELVIEW);
		
		//Draw graphics
		update(g, 1/frameLoadTime);
		drawScene(window, g, roundX, roundY, frameLoadTime);

		glfwSwapBuffers(window);
		glfwPollEvents();

		//The time we finished the frame
		end_time = glfwGetTime();
		//Calculate the time it took
		frameLoadTime = end_time - start_time;
		
		//printf("fps: %f   ...  NumSquares: %d ... NumTowers: %d\n", 1/frameLoadTime, mySquares->getNumberOfSquare(), myTowers->getNumTowers());
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

