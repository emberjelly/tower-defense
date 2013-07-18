#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:

	Player();
	~Player();
	int getHp();
	int getResources();
	void setHp(int health);
	void setResources(int resources);

private:
	int m_Health;
	int m_Resources;
};


#endif
