#include "SquareManager.h"
#include "EnemyManager.h"
#include "TowerManager.h"
#include "ProjectileManager.h"
#include "iniFile.h"
#include "TowerMenu.h"
#include "Player.h"

struct game {
	SquareManager *squares;
	EnemyManager *enemies;
	TowerManager *towers;
	ProjectileManager *projectiles;
	TowerMenu *menu;
	Player *player;
};

typedef struct game *Game; // An ADT for using the game struct

void loadGame(game *newGame, IniFile *ini);
void saveGame (Game g);
void update(Game g, double frameRate);
