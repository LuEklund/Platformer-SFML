#pragma once
#include "Global.h"
#include "SFML/Graphics.hpp"
#include <iostream>

#include "Player.h"
#include "Gimmy.h"

class MapManager : public sf::Drawable
{
private:
	gbl::Map	&m_map;
	Player		*m_pPlayer;
	sf::Image	m_mapImage;
	sf::Texture	m_mapTextures;
	sf::Sprite	m_mapSprites[8];

	void	assignMap();
	void	assignEnemies();
	void	assignBackground();
public:
	MapManager(gbl::Map	&map);
	~MapManager();

	//Inits
	bool	initMapManager(Player *player, std::vector<std::unique_ptr<Entity>> &enemies);

	// void	update
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


