#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	sf::Texture		m_texture;

	float			m_xp;
	float			m_xpToLevelUp;
	int				m_Level;
	bool			m_levelUp;

	//private fuctions
	void	levelUp();
public:
	Player(gbl::Map &map);
	~Player();

	//inits
	bool	initPlayer();

	//modifiers
	void	setLevelUp(bool state);
	void	increaseXp(float xp);

	//accessors
	const bool	&LeveledUp() const;
	const int	&getLevel() const;
	const float	&getXp() const;
	const float	&getXpToLevelUp() const;

	//functions
	void	update(const float &dt);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


