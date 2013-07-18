#include "SquareManager.h"
#include "EnemyManager.h"
#include "TowerManager.h"
#include "ProjectileManager.h"
#include "iniFile.h"
#include "TowerMenu.h"

struct game {
	SquareManager *squares;
	EnemyManager *enemies;
	TowerManager *towers;
	ProjectileManager *projectiles;
	TowerMenu *menu;
};

typedef struct game *Game; // An ADT for using the game struct

Game loadGame(IniFile *ini);
void saveGame (Game g);
void update(Game g, double frameRate);