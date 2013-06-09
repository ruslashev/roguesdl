#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity
{
public:
	unsigned int health;
	unsigned int level;
	char icon;

	int x;
	int y;

	Entity() {
		health = 10;
		level = 1;
		icon = 'U';
		x = 0;
		y = 0;
	}
};

class Player : public Entity
{
public:
	Player();
};

#endif
