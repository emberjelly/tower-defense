#ifndef TOWERMENU_H
#define TOWERMENU_H

#include "MenuButton.h"

class TowerMenu {
public:
	TowerMenu();
	~TowerMenu();
	
	//This function should be called during drawing time
	void drawMenu(int screenWidth, int screenHeight);
	
	void addButton(char *title);
	void activateMenu();
	void deactivateMenu();

	bool isActive();
	int getNumButtons();
	MenuButton *getButton(int buttonNum);
	MenuButton *getButtonByName(char *buttonName);
private:
	bool m_isActive;
	int m_numButtons;
	MenuButton **m_ppButtons;
};

#endif



