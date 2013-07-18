#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "Projectile.h"

class ProjectileManager {
public:
	ProjectileManager();
	~ProjectileManager();
	int getNumProjectiles();
	Projectile* getProjectile(int projNum);
	Projectile* getProjectileByCoods(int x, int y);
	void addProjectile(double x, double y, Projectile_Type projClass);
	void removeProjectile(int projNum);
private:
	Projectile **m_ppProjectiles;
	int m_numProjectiles;
};

#endif
