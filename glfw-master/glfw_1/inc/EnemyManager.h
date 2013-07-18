#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Enemy.h"

class EnemyManager {
public:
	EnemyManager();
	~EnemyManager();
	void addEnemy(enemyType enemyClass, double speed, EnemyMoveList path);
	void removeEnemy(int enemyNum);
	Enemy* getEnemy(int enemyNum);
	int getNumOfEnemies();
	void setMasterPath(EnemyMoveList path);
	EnemyMoveList getMasterPath();
private:
	Enemy **m_ppEnemies;
	int m_numEnemies;
	EnemyMoveList m_pMasterPath;
};

#endif
