#include "Tower.h"
#include <stdio.h>

Tower::Tower() {
	m_X = 0;
	m_Y = 0;
	m_TowerClass = empty;
	m_FireRate = -1;
	m_CoolDown = 0;
	m_Range = 0;
}

Tower::~Tower() {

}

void Tower::setX(int x) {
	m_X = x;
}

void Tower::setY(int y) {
	m_Y = y;
}

int Tower::getX() {
	return m_X;
}
int Tower::getY() {
	return m_Y;
}

Tower_Type Tower::getType() {
	return m_TowerClass;
}

void Tower::setType(Tower_Type type){
	m_TowerClass = type;
	if (type == empty) {
		m_FireRate = 0;
		m_Range = 0;
		m_CoolDown = 0;
	}
	if (type == gun) {
		m_FireRate = 2;
		m_Range = 40;
		m_CoolDown = 1;
	}
	if (type == machine_gun) {
		m_FireRate = 6;
		m_Range = 40;
		m_CoolDown = 1;
	}
	
	if (type == lazer) {
		m_FireRate = 16;
		m_Range = 50;
		m_CoolDown = 1;
	}

}

double Tower::getCooloffState() {
	return m_CoolDown;
}

void Tower::setCooloffState(double state) {
	m_CoolDown = state;
}

bool Tower::updateState(double frameRate) {

	bool coolDownComplete = 0;
	m_CoolDown -= m_FireRate/frameRate;
	if (m_CoolDown <= 0) {
		coolDownComplete = 1;
		m_CoolDown = 1;
	}
	return coolDownComplete;
}

void Tower::setFireRate(double rate) {
	m_FireRate = rate;
}

double Tower::getFireRate() {
	return m_FireRate;
}

void Tower::setRange (double range) {
	m_Range = range;
}

double Tower::getRange() {
	return m_Range;
}
