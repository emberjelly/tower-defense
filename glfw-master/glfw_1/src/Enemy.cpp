#include <stdio.h>
#include "Enemy.h"


Enemy::Enemy() {
	m_X = 0;
	m_Y = 0;
	m_Class = drone;
	m_Speed = 0;
}

Enemy::~Enemy() {
}

double Enemy::getX() {
	return m_X;
}

double Enemy::getY() {
	return m_Y;
}

void Enemy::setX(double x) {
	m_X = x;
}

void Enemy::setY(double y) {
	m_Y = y;
}

void Enemy::setClass(enemyType e) {
	m_Class = e;
}

void Enemy::setSpeed(double speed) {
	m_Speed = speed;
}

void Enemy::setPath (EnemyMoveList path) {
	m_Path = path;
	//m_X = getFirstX(path);
	//m_Y = getFirstY(path);
}

EnemyMoveList Enemy::getPath () {
	return m_Path;
}

double Enemy::getSpeed() {
	return m_Speed;
}


void Enemy::setHp(int hp) {
	m_Health = hp;
}

int Enemy::GetHp() {
	return m_Health;
}

enemyType Enemy::getClass() {
	return m_Class;
}

EnemyMoveList newList(int x, int y, int direction) {
	EnemyMoveList list = new struct _enemyMoveList;
	list->next = NULL;
	list->coord[0] = x;
	list->coord[1] = y;
	list->direction = direction;
	return list;
}

void addNode(EnemyMoveList l, int x, int y, int direction) {
	EnemyMoveList newNode = newList(x, y, direction);
	EnemyMoveList nextNode = l;
	while (nextNode->next != NULL) {
		nextNode = nextNode->next;
	}
	nextNode->next = newNode;
}

EnemyMoveList removeFirstNode(EnemyMoveList l) {
	EnemyMoveList returnList = l->next;
	delete l;
	l = NULL;
	return returnList;
}

int Enemy::moveEnemy(Enemy *e, double FrameRate) {
	EnemyMoveList path = e->getPath();
	int success = 0;
	if (path->next != NULL) {
		success = 1;
		int direction = getFirstDirection(path);
		if (direction == 0) { //North
			if (e->getY() < getFirstY(path->next)) {
				e->setY(e->getY() + e->getSpeed()/FrameRate);
			} else {
				e->setPath(path->next);
			}
		}
		if (direction == 1) { //South
			if (e->getY() > getFirstY(path->next)) {
				e->setY(e->getY() - e->getSpeed()/FrameRate);
			} else {
				e->setPath(path->next);
			}
		}
		if (direction == 2) { //East
			if (e->getX() < getFirstX(path->next)) {
				e->setX(e->getX() + e->getSpeed()/FrameRate);
			} else {
				e->setPath(path->next);
			}
		}
		if (direction == 3) { //West
			if (e->getX() > getFirstX(path->next)) {
				e->setX(e->getX() - e->getSpeed()/FrameRate);
			} else {
				e->setPath(path->next);
			}
		}
	}
	return success;
}


int getFirstDirection(EnemyMoveList l) {
	if (l != NULL) {
		return l->direction;
	} else {
		printf ("Asking for the direction of a null list\n");
	}
}

int getFirstX(EnemyMoveList l) {
	if (l == NULL) {
		printf("getFirstX was given an empty list\n");
	} else {
		return l->coord[0];
	}
}

int getFirstY(EnemyMoveList l) {
	if (l == NULL) {
		printf("getFirstY was given an empty list\n");
	} else {
		return l->coord[1];
	}
}

int getEnemyListLength (EnemyMoveList l) {
	int length = 0;
	EnemyMoveList nextNode = l;
	if (l != NULL) {
		while (nextNode->next != NULL) {
			length ++;
			nextNode = nextNode->next;
		}
	}
	return length;
}
