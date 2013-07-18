#include <stdlib.h>
#include "SquareManager.h"


SquareManager::SquareManager() {
		m_ppSquares = NULL;
		m_NumSquares = 0;
	}
	SquareManager::~SquareManager() {
		if (m_ppSquares != NULL) {
			delete m_ppSquares;
		}
	}

	
void SquareManager::removeSquare (int x, int y) {
	m_NumSquares --;
	Square** m_ppTemp = m_ppSquares;
	m_ppSquares = new Square*[m_NumSquares];
	for (int i; i < m_NumSquares; i ++) {
		if (m_ppSquares[i]->getX() == x && m_ppSquares[i]->getY() == y) {
			delete (m_ppSquares[i]);
		} else {
			m_ppSquares[i] = new Square;
			*m_ppSquares[i]  = *m_ppTemp[i];
		}
	}
}
	
Square* SquareManager::getSquare (int num) {
	return m_ppSquares[num];
}

Square* SquareManager::getSquareByCoords (int x, int y) {
	Square *returnSquare = NULL;
	for (int i = 0; i < m_NumSquares; i ++) {
		if (m_ppSquares[i]->getX() == x && m_ppSquares[i]->getY() == y) {
			returnSquare = m_ppSquares[i];
		}
	}
	return returnSquare;
}

int SquareManager::getNumberOfSquare(void) {
	return m_NumSquares;
}


void SquareManager::addSquare (int x, int y, float red, float green, float blue) {
	m_NumSquares ++;
	Square *newSquare = new Square;
	Square** m_ppTemp = m_ppSquares;
	m_ppSquares = new Square*[m_NumSquares];
	for (int i = 0; i < (m_NumSquares - 1); i ++ ) {
		m_ppSquares[i] = new Square;
		*m_ppSquares[i]  = *m_ppTemp[i];
	}
	m_ppSquares[m_NumSquares - 1] = new Square;
	m_ppSquares[m_NumSquares - 1]->setX(x);
	m_ppSquares[m_NumSquares - 1]->setY(y);
	m_ppSquares[m_NumSquares - 1]->setColour(red, green, blue);

	if (m_ppTemp !=NULL) {
			delete[] m_ppTemp;
	}
}
