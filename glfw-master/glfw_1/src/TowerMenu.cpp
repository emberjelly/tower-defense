#include <stdio.h>
#include "TowerMenu.h"
#include <string.h>
//#include <gl\GLU.h>

TowerMenu::TowerMenu() {
	m_ppButtons = NULL;
	m_numButtons = 0;
	m_isActive = false;
}

TowerMenu::~TowerMenu() {
	if (m_ppButtons != NULL) {
		delete m_ppButtons;
	}
}

void TowerMenu::drawMenu(int screenWidth, int screenHeight) {
	//Select a Size to draw the menu
	glBegin ( GL_QUADS );
		glColor3f(0.8, 0.8, 0.8);
		glVertex2f(-screenWidth/2, -screenHeight/2);
		glVertex2f(-screenWidth/2 + screenWidth/6, -screenHeight/2);
		glVertex2f(-screenWidth/2 + screenWidth/6, screenHeight/2);
		glVertex2f(-screenWidth/2, screenHeight/2);
	glEnd();

	for (int i = 0; i < m_numButtons; i ++) {
		m_ppButtons[i]->drawButton();
	}
	
	//Need to figure out how to draw text


}

void TowerMenu::addButton(char *title) {
	m_numButtons ++;
	MenuButton **m_ppTemp = m_ppButtons;
	m_ppButtons = new MenuButton*[m_numButtons];
	for (int i = 0; i < m_numButtons - 1; i ++) {
		m_ppButtons[i] = new MenuButton;
		*m_ppButtons[i] = *m_ppTemp[i];
	}
	m_ppButtons[m_numButtons -1] = new MenuButton;
	m_ppButtons[m_numButtons -1]->setHeight(8);
	m_ppButtons[m_numButtons -1]->setWidth(32);

	m_ppButtons[m_numButtons -1]->setTitle(title);
	m_ppButtons[m_numButtons -1]->setX(-96*640/480);
	m_ppButtons[m_numButtons -1]->setY(m_numButtons*16 - 88);

	if (m_ppTemp != NULL) {
		delete[] m_ppTemp;
	}
}

void TowerMenu::activateMenu() {
	m_isActive = 1;
}

void TowerMenu::deactivateMenu() {
	m_isActive = 0;
}

bool TowerMenu::isActive() {
	return m_isActive;
}


MenuButton *TowerMenu::getButton(int buttonNum) {
	return m_ppButtons[buttonNum];
}

int TowerMenu::getNumButtons() {
	return m_numButtons;
}


MenuButton *TowerMenu::getButtonByName(char *buttonName) {
	MenuButton *returnButton = NULL;
	for (int i = 0; i < m_numButtons; i ++) {
		if (strcmp(buttonName, m_ppButtons[i]->getTitle()) == 0) {
			returnButton = m_ppButtons[i];
		}
	}
	return returnButton;
}