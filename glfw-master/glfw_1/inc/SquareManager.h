#ifndef SQUAREMANAGER_H
#define SQUAREMANAGER_H

#include "Square.h"

class SquareManager {
public:
	SquareManager();
	~SquareManager();
	void addSquare (int x, int y, float red, float green, float blue);
	void removeSquare (int x, int y);
	Square* getSquare (int num);
	Square* getSquareByCoords (int x, int y);
	int getNumberOfSquare();


private:
	Square** m_ppSquares;
	int m_NumSquares;

};

#endif
