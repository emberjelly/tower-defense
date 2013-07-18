#include "ProjectileManager.h"
#include <stdlib.h>

ProjectileManager::ProjectileManager() {
	m_numProjectiles = 0;
	m_ppProjectiles = NULL;
}

ProjectileManager::~ProjectileManager() {
	if (m_ppProjectiles != NULL) {
		delete m_ppProjectiles;
	}
}

int ProjectileManager::getNumProjectiles() {
	return m_numProjectiles;
}

Projectile* ProjectileManager::getProjectile(int projNum) {
	return m_ppProjectiles[projNum];
}

Projectile* ProjectileManager::getProjectileByCoods(int x, int y) {
	Projectile *returnProjectile = NULL;
	for (int i = 0; i < m_numProjectiles; i ++) {
		if (getProjectile(i)->getX() == x && getProjectile(i)->getY() == y) {
			returnProjectile = m_ppProjectiles[i];
		}
	}
	return returnProjectile;
}

void ProjectileManager::addProjectile(double x, double y, Projectile_Type projClass) {
	m_numProjectiles ++;
	Projectile **m_ppTemp = m_ppProjectiles;
	m_ppProjectiles = new Projectile*[m_numProjectiles];
	for (int i = 0; i < (m_numProjectiles - 1); i ++ ) {
		m_ppProjectiles[i] = new Projectile;
		*m_ppProjectiles[i] = *m_ppTemp[i];
	}
	m_ppProjectiles[m_numProjectiles - 1] = new Projectile;
	m_ppProjectiles[m_numProjectiles - 1]->setX(x);
	m_ppProjectiles[m_numProjectiles - 1]->setY(y);
	m_ppProjectiles[m_numProjectiles - 1]->setType(projClass);
}

void ProjectileManager::removeProjectile(int projNum) {
	m_numProjectiles --;
	delete m_ppProjectiles[projNum];
	for(int i = projNum; i < m_numProjectiles; i ++)
	{
		m_ppProjectiles[i] = m_ppProjectiles[i + 1];
	}
}
