#ifndef SQUARE_H
#define SQUARE_H

#define SQUARE_SIZE 8

class Square {
public:
	Square();
	~Square();
	void setX(int x);
	void setY(int y);
	int getX(void);
	int getY(void);
	float getRed(void);
	float getGreen(void);
	float getBlue(void);
	void setColour (float red, float green, float blue);
	void deleteSquare (void);
	int getSize();
private:
	int m_x;
	int m_y;
	int m_size;
	float m_Colour[3];
};

#endif
