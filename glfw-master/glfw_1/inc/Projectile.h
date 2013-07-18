#ifndef PROJECTILE_H
#define PROJECTILE_H

enum Projectile_Type {
	bullet
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


private:
	double m_X;
	double m_Y;
	double m_Speed;
	int m_Target;

	Projectile_Type m_ProjClass;
};

#endif
