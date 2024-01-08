#pragma once
#include "Player.h"
class Gimmy : public Entity
{
private:
	Player	&m_player;
	bool	m_direction;
	float	m_turWait;

public:
	Gimmy(gbl::Map &map, Player &m_player, float x, float y);
	~Gimmy();

	//inits
	bool	initGimmy(sf::Texture &Texture);

	//Modifiers
	void	kill();

	//Functions
	void	update(const float &dt);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


