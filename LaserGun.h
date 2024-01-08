#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "Global.h"
#include "Player.h"
#include "Gimmy.h"


class LaserGun : public sf::Drawable
{
private:
	//other realted stuff
	sf::RenderWindow		&m_window;
	Player					*m_pPlayer;

	//core
	sf::VertexArray			m_laser;
	sf::VertexArray			m_aim;
	float					m_laserHalfThickness;
	float					m_laserLength;
	float					m_cooldown;
	sf::SoundBuffer			m_bufferSound;
	sf::Sound				m_sound;

public:
	LaserGun(sf::RenderWindow &m_window);
	~LaserGun();

	//init
	bool	initLaserGun(Player *m_pPlayer);

	//functions
	bool	upgrade(sf::Keyboard::Key key);

	void	update(const float &dt, std::vector<std::unique_ptr<Entity>> &enemies);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;

};

