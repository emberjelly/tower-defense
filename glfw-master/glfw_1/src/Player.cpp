#include "Player.h"


Player::Player() {
	m_Health = 10;
	m_Resources = 1000;
}


Player::~Player() {

}

int Player::getHp() {
	return m_Health;
}

int Player::getResources() {
	return m_Resources;
}

void Player::setHp(int health) {
	m_Health = health;
}

void Player::setResources(int resources) {
	m_Resources = resources;
}
