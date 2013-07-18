#ifndef TOWER_H
#define TOWER_H

enum Tower_Type {
	empty,
	gun
};

class Tower {
public:
	Tower();
	~Tower();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	Tower_Type getType();
	void setType(Tower_Type type);
	double getCooloffState();
	void setCooloffState(double state);
	bool updateState(double frameRate); //Returns true if the tower is ready to fire
	void setFireRate(double rate);
	double getFireRate();
	void setRange (double range);
	double getRange();

private:
	Tower_Type m_TowerClass;
	int m_X;
	int m_Y;
	double m_CoolDown;
	double m_FireRate;
	double m_Range;
};

#endif
