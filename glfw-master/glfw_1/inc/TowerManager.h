#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

#include "Tower.h"

class TowerManager{
public:
	TowerManager();
	~TowerManager();
	int getNumTowers();
	Tower* getTower(int towerNum);
	Tower* getTowerByCoods(int x, int y);
	void addTower(int x, int y, Tower_Type towerClass);
	void removeTower(int towerNum);

private:
	int m_NumTowers;
	Tower **m_ppTowers;
};


#endif
