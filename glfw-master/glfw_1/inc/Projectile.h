#ifndef PROJECTILE_H
#define PROJECTILE_H

enum Projectile_Type {
	bullet,
	lazer_beam
};

class Projectile {
public:
	Projectile();
	~Projectile();
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	void setSpeed(double speed);
	double getSpeed();
	void setTarget(int enemyNumber);
	int getTarget();
	Projectile_Type getType();
	void setType(Projectile_Type type);
	void setTowerNumber(int num);
	int getTowerNumber();

private:
	double m_X;
	double m_Y;
	double m_Speed;
	int m_Target;
	int m_TowerNumber;
	Projectile_Type m_ProjClass;
};

#endif
