#include <stdlib.h>
#include "TowerManager.h"


TowerManager::TowerManager() {
	m_NumTowers = 0;
	m_ppTowers = NULL;
}

TowerManager::~TowerManager() {
	if (m_ppTowers != NULL) {
		delete m_ppTowers;
	}
}

int TowerManager::getNumTowers() {
	return m_NumTowers;
}

Tower* TowerManager::getTower(int towerNum) {
	return m_ppTowers[towerNum];
}

Tower* TowerManager::getTowerByCoods(int x, int y) {
	Tower *returnTower = NULL;
	for (int i = 0; i < m_NumTowers; i ++) {
		if (getTower(i)->getX() == x && getTower(i)->getY() == y) {
			returnTower = m_ppTowers[i];
		}
	}
	return returnTower;
	
}

void TowerManager::addTower(int x, int y, Tower_Type towerClass) {
	m_NumTowers ++;
	Tower **m_ppTemp = m_ppTowers;
	m_ppTowers = new Tower*[m_NumTowers];
	for (int i = 0; i < (m_NumTowers - 1); i ++ ) {
		m_ppTowers[i] = new Tower;
		*m_ppTowers[i] = *m_ppTemp[i];
	}

	m_ppTowers[m_NumTowers - 1] = new Tower;
	m_ppTowers[m_NumTowers - 1]->setX(x);
	m_ppTowers[m_NumTowers - 1]->setY(y);
	m_ppTowers[m_NumTowers - 1]->setType(towerClass);

	if (towerClass == gun) {
		m_ppTowers[m_NumTowers - 1]->setFireRate(1);
		m_ppTowers[m_NumTowers - 1]->setRange(50);
	}
}

void TowerManager::removeTower(int towerNum) {

}
