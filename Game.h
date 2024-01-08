#pragma once
#include "SFML/Graphics.hpp"
#include "RandomGenerator.h"
#include "Player.h"
#include "MapManager.h"
#include <iostream>
#include "Gimmy.h"
#include "LaserGun.h"
#include "Menu.h"
#include "GUI.h"


class Game : public sf::Drawable
{
private:
	enum class State
	{
		PLAYING,
		PAUSED,
		LEVELUP,
		GAMEOVER
	};
	//Essentials
	sf::RenderWindow	&m_Window;
	sf::View			m_gameView;
	State				m_state;
	sf::Font			m_font;
	sf::Texture			m_gimmyTexture;
	sf::Clock			m_clock;
	float				m_dt;

	//random number generator engine
	RandomGenerator				&m_RNG;
	
	//Menu
	std::unique_ptr<Menu>		m_pMenu;

	//Gui
	std::unique_ptr<Gui>		m_pGui;

	//Game map
	std::unique_ptr<MapManager>	m_pMapManager;
	gbl::Map					m_map;

	//Enemies
	std::vector<std::unique_ptr<Entity>>	m_Enemies;

	//Player
	std::unique_ptr<Player>		m_pPlayer;
	std::unique_ptr<LaserGun>	m_pLaserGun;

public:
	Game(sf::RenderWindow &window);
	~Game();

	//inits
	bool	initGame();

	//Functions
	void	isKeyPressed(sf::Keyboard::Key key);
	void	isMouseButtonReleased(sf::Mouse::Button button);

	void	update();
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};

