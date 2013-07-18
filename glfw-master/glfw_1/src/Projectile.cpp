#include "Projectile.h"

Projectile::Projectile() {
	m_X = 0;
	m_Y = 0;
	m_Speed = 0;
	m_Target = 0;
}

Projectile::~Projectile() {
}

double Projectile::getX() {
	return m_X;
}

double Projectile::getY() {
	return m_Y;
}

void Projectile::setX(double x) {
	m_X = x;
}

void Projectile::setY(double y) {
	m_Y = y;
}

void Projectile::setSpeed(double speed) {
	m_Speed = speed;
}

double Projectile::getSpeed() {
	return m_Speed;
}

void Projectile::setTarget(int enemyNumber) {
	m_Target = enemyNumber;
}

int Projectile::getTarget() {
	return m_Target;
}

Projectile_Type Projectile::getType() {
	return m_ProjClass;
}

void Projectile::setType(Projectile_Type type) {
	m_ProjClass = type;
}

