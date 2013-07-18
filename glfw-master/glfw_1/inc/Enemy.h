#ifndef ENEMY_H
#define ENEMY_H

enum enemyType {
	drone
};

typedef struct _enemyMoveList *EnemyMoveList;

class Enemy {
public:
	Enemy();
	~Enemy();
	double getX();
	double getY();
	void setX(double x);
	void setY(double y);
	void setClass(enemyType e);
	void setSpeed(double speed);
	double getSpeed();
	
	void setHp(int hp);
	int GetHp();
	
	//gives the enemy a new path
	void setPath (EnemyMoveList path);
	
	//Returns the next node the enemy is moving towards on the path
	EnemyMoveList getPath ();

	// A move Enemy function, moves an enemy along its path according to the frame rate, the return value indicates whether the
	// function call was successful. If it returns FALSE, the enemy has reached the end of the path
	int moveEnemy(Enemy *e, double FrameRate);

private:
	double m_X;
	double m_Y;
	enemyType m_Class;
	double m_Speed;
	EnemyMoveList m_Path;
	int m_Health;
};

// A linked list for the enemy path
struct _enemyMoveList {
	int coord[2];
	int direction;
	EnemyMoveList next;
};

//----------Functions for the Enemy path linked list

//Creates a new list
EnemyMoveList newList(int x, int y, int direction);

//Adds a node to the end of the list
void addNode(EnemyMoveList l, int x, int y, int direction);

//Removes the first node of the list
EnemyMoveList removeFirstNode(EnemyMoveList l);

//Returns the direction of the first node, North = 0, South = 1, East = 2, West = 3
int getFirstDirection(EnemyMoveList l);

//Returns the X coordinate of the first node
int getFirstX(EnemyMoveList l);

//Returns the Y coordinate of the first node
int getFirstY(EnemyMoveList l);

//Returns the length of the path
int getEnemyListLength (EnemyMoveList l);

//------------------

#endif
