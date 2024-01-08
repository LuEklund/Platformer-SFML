#include "Game.h"

//Constructor
Game::Game(sf::RenderWindow &window)
	: m_Window(window)
	, m_state(State::PAUSED)
	, m_dt(0.f)
	, m_RNG(RandomGenerator::getInstance())
	, m_pMenu(std::make_unique<Menu>(window))
	, m_pPlayer(std::make_unique<Player>(m_map))
	, m_pMapManager(std::make_unique<MapManager>(m_map))
	, m_pLaserGun(std::make_unique<LaserGun>(window))
	, m_pGui(std::make_unique<Gui>(m_gameView))
{
}

Game::~Game()
{
}

bool Game::initGame()
{
	if (!m_font.loadFromFile("assets/Sports World-Regular.ttf"))
	{
		std::cout << "Failed to load FONT!" << std::endl;
		return false;
	}
	if (!m_gimmyTexture.loadFromFile("assets/Gimmy.png"))
	{
		std::cout << "Failed to load Gimmys texture! Very sad D:" << std::endl;
		return false;
	}
	if (!m_pMenu->initMenu(m_font))
		return(false);
	if (!m_pGui->initGui(m_font))
		return(false);
	if (!m_pPlayer->initPlayer())
		return (false);
	if (!m_pMapManager->initMapManager(m_pPlayer.get(), m_Enemies))
		return (false);
	for (std::unique_ptr<Entity> &e : m_Enemies)
	{
		Gimmy *gimmy = dynamic_cast<Gimmy *>(e.get());
		if (gimmy)
		{
			if (!gimmy->initGimmy(m_gimmyTexture))
				return false;
		}
		else
			std::cout << "this is no Gimmy" << std::endl;
	}
	if (!m_pLaserGun->initLaserGun(m_pPlayer.get()))
		return (false);
	m_gameView.setSize(sf::Vector2f(300.f,300.f));
	return (true);
}



void Game::isKeyPressed(sf::Keyboard::Key key)
{
	switch (m_state)
	{
	case  State::LEVELUP:
		if (m_pLaserGun->upgrade(key))
			m_state = State::PLAYING;
		break;
	case  State::PLAYING:
		if (key == sf::Keyboard::Escape)
			m_state = State::PAUSED;
	break;
		case  State::PAUSED:
		if (key == sf::Keyboard::Escape)
			m_state = State::PLAYING;
		break;
	}
}

void Game::isMouseButtonReleased(sf::Mouse::Button button)
{
	switch (m_state)
	{
	case  State::PAUSED:
		if (m_pMenu->isButtonPlay(sf::Mouse::getPosition(m_Window)))
			m_state = State::PLAYING;
		if (m_pMenu->isButtonQuit(sf::Mouse::getPosition(m_Window)))
			m_Window.close();
		break;
	}
}

void Game::update()
{
	m_dt = m_clock.restart().asSeconds();
	switch (m_state)
	{
	case State::PLAYING:
		for (std::unique_ptr<Entity> &e : m_Enemies)
		{
			Gimmy *gimmy = dynamic_cast<Gimmy *>(e.get());
			if (gimmy)
				gimmy->update(m_dt);
		}
		m_pPlayer->update(m_dt);
		if(m_pPlayer->LeveledUp())
		{
			m_pGui->setLevel(m_pPlayer->getLevel());
			m_state = State::LEVELUP;
		}
		m_pLaserGun->update(m_dt, m_Enemies);
		m_pGui->update(m_pPlayer->getXp(), m_pPlayer->getXpToLevelUp());
		m_gameView.setCenter(m_pPlayer->getPosition());
		break;
	case State::PAUSED:
		m_pMenu->update(sf::Mouse::getPosition(m_Window));
	break;
	}
}


void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	m_Window.setView(m_gameView);
	target.draw(*m_pMapManager.get());
	for (const std::unique_ptr<Entity> &e : m_Enemies)
	{
		Gimmy *gimmy = dynamic_cast<Gimmy *>(e.get());
		if (gimmy)
			target.draw(*gimmy);
	}
	target.draw(*m_pPlayer.get());	
	target.draw(*m_pLaserGun.get());
	target.draw(*m_pGui.get());
	switch (m_state)
	{
	case State::PAUSED:
		m_Window.setView(m_Window.getDefaultView());
		target.draw(*m_pMenu.get());
		m_Window.setView(m_gameView);
	break;
	}
}
