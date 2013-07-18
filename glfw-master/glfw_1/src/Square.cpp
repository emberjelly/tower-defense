#include "Square.h"

Square::Square() {
	m_x = 0;
	m_y = 0;
	m_size = SQUARE_SIZE;
	m_Colour[0] = 0;
	m_Colour[1] = 0;
	m_Colour[2] = 0;
}

Square::~Square() {

}

int Square::getX(void) {
	return m_x;
}

int Square::getY(void) {
	return m_y;
}

void Square::setX(int x) {
	m_x = x;
}

void Square::setY(int y) {
	m_y = y;
}

float Square::getRed(void) {
	return m_Colour[0];
}

float Square::getGreen(void) {
	return m_Colour[1];
}

float Square::getBlue(void) {
	return m_Colour[2];
}

void Square::setColour (float red, float green, float blue) {
	m_Colour[0] = red;
	m_Colour[1] = green;
	m_Colour[2] = red;
}

int Square::getSize() {
	return SQUARE_SIZE;
}
