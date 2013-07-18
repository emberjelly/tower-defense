#include "EnemyManager.h"
#include<stdlib.h>

EnemyManager::EnemyManager() {
	m_ppEnemies = NULL;
	m_pMasterPath = NULL;
	m_numEnemies = 0;
}
EnemyManager::~EnemyManager() {
	if (m_ppEnemies != NULL) {
		delete m_ppEnemies;
	}
	while (m_pMasterPath != NULL) {
		removeFirstNode(m_pMasterPath);
	}
}
void EnemyManager::addEnemy(enemyType enemyClass, double speed, EnemyMoveList path) {
	m_numEnemies ++;
	Enemy** m_ppTemp = m_ppEnemies;
	m_ppEnemies = new Enemy*[m_numEnemies];
	for (int i = 0; i < (m_numEnemies - 1); i ++ ) {
		m_ppEnemies[i] = new Enemy;
		*m_ppEnemies[i]  = *m_ppTemp[i];
	}
	m_ppEnemies[m_numEnemies - 1] = new Enemy;
	m_ppEnemies[m_numEnemies - 1]->setPath(path);
	m_ppEnemies[m_numEnemies - 1]->setClass(enemyClass);
	m_ppEnemies[m_numEnemies - 1]->setSpeed(speed);
	if (enemyClass == drone) {
		m_ppEnemies[m_numEnemies - 1]->setHp(10);
	}
	if (enemyClass == heavy_drone) {
		m_ppEnemies[m_numEnemies - 1]->setHp(50);
	}

	if (m_ppTemp !=NULL) {
			delete[] m_ppTemp;
	}
}
void EnemyManager::removeEnemy(int enemyNum) {
	m_numEnemies --;
	delete m_ppEnemies[enemyNum];
	for(int i = enemyNum; i < m_numEnemies; i ++)
	{
		m_ppEnemies[i] = m_ppEnemies[i + 1];
	}
}

Enemy* EnemyManager::getEnemy(int enemyNum) {
	return m_ppEnemies[enemyNum];
}
int EnemyManager::getNumOfEnemies() {
	return m_numEnemies;
}

void EnemyManager::setMasterPath(EnemyMoveList path) {
	m_pMasterPath = path;
}

EnemyMoveList EnemyManager::getMasterPath() {
	return m_pMasterPath;
}


