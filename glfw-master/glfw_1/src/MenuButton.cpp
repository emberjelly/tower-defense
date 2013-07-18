#include "MenuButton.h"
#include <string.h>
MenuButton::MenuButton() {
	m_title = NULL;
}

MenuButton::~MenuButton() {
	if (m_title != NULL) {
		delete m_title;
	}
}

void MenuButton::drawButton() {
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(m_X, m_Y);
	glVertex2f(m_X + m_Width, m_Y);
	glVertex2f(m_X + m_Width, m_Y + m_Height);
	glVertex2f(m_X, m_Y + m_Height);
	glEnd();
	//Need to draw the text
}

void MenuButton::setTitle(char *title) {
	m_title = new char[strlen(title) + 1];
	for (int i = 0; i < strlen(title) + 1; i ++) {
		m_title[i] = title[i];
	}
}

char* MenuButton::getTitle() {
	return m_title;
}

int MenuButton::getX() {
	return m_X;
}

int MenuButton::getY() {
	return m_Y;
}

void MenuButton::setX(int x) {
	m_X = x;
}

void MenuButton::setY(int y) {
	m_Y = y;
}

int MenuButton::getWidth() {
	return m_Width;
}

int MenuButton::getHeight() {
	return m_Height;
}

void MenuButton::setWidth(int width) {
	m_Width = width;
}

void MenuButton::setHeight(int height) {
	m_Height = height;
}
