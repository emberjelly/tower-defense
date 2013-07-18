#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <GLFW\glfw3.h>

class MenuButton {
public:
	MenuButton();
	~MenuButton();
	void drawButton();
	void setTitle(char *title);
	char *getTitle();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int getWidth();
	int getHeight();
	void setWidth(int width);
	void setHeight(int height);

private:
	bool isClicked;
	char *m_title;
	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;
};

#endif
