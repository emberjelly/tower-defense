#if WINDOWS
#include <Windows.h>
#endif // WINDOWS

#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "EnemyManager.h"
#include "iniFile.h"
#include "TowerManager.h"
#include "SquareManager.h"
#include "ProjectileManager.h"
#include "Game.h"
#include "TowerMenu.h"
#include "Player.h"





//Graphics.cpp Function declarations. May move these later
//Draws all components of the scene
void drawScene (GLFWwindow* window, game *g, int roundX, int roundY, double frameLoadTime);


//Input.cpp function declarations. Also required some global variables, not sure if there is a way to avoid this
//Have not got this working yet
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse (GLFWwindow* window, int button, int action, int mods);
void cursorPosCallback(GLFWwindow* window ,double x , double y );


/* ****THINGS TO DO ****

	* Figure out why towers sometimes shoot at enemies even though they are out of range. I think this has something to do with the way the member of my dynamic arrays are shifted around.
	Meaning that if a tower has a target, and that target is destroyed, it is possible that that position in the array is given to another target, hence the tower would shoot at it regardless of distance.
	
	* Sort out how the headers are implemented. Sometimes I'm not sure whether the managers are doing too much work or not enough work. For example:
	When I add a tower to the tower manager, whose responsibility should it be to set the speed, fire rate etc.. If it is done automatically, the flexibility of thing will generally decrease.
	Should managers ever do any drawing or use any openGL functions?
	Should managers ever take in variables such as the mouseX and mouseY to do calculations with? (i.e. should figuring out fs the mouse button is down and mouse cursor position is on the button be done inside
	or outside the Button manager? And if it is outside, where? atm it is in the main function...

	* Once my headers are sorted, clean up some of the functions (particularly main) maybe sort this into a few more functions.

	* Some of my general inforation such as the size of the screen, and size of the "units" I am using for drawing I am using statically, which will be a major problem if I changed the size of the window
	or something. Will need to pass around a variable that deals with these things to all my functions that do any type of drawing or storing of graphics.

	* Figure out how to add text to the menu

	* Try to figure out a way to not have to use global variables for the input

	* Add a player header of some kind to store things like resources, number of enemies that have made it to the end of the path (or health of something).

	* Add more tower and enemy types

	* Work on giving some structure to the rate, and type that enemies arrive arrive at to make the game playable.

	* Add some more interface graphics to convey how much health the enemies have, maybe what enemies are coming next, available resources, health etc... 

	* Redo graphics (hopefully in 3D eventually)
*/
