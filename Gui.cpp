#include "GUI.h"

Gui::Gui(sf::View &gameView)
	: m_gameView(gameView)
{
}

Gui::~Gui()
{
}

//inits
bool Gui::initGui(sf::Font &font)
{
	m_textLevel.setString("Level: 0");
	m_textLevel.setFont(font);
	m_textLevel.setCharacterSize(10);
	m_textLevel.setFillColor(sf::Color::Cyan);
	m_textLevel.setPosition(
		m_gameView.getCenter() - (m_gameView.getSize() / 2.f));

	m_textXpStatus.setString("0xp / 1xp => levelUp");
	m_textXpStatus.setFont(font);
	m_textXpStatus.setCharacterSize(10);
	m_textXpStatus.setFillColor(sf::Color::Cyan);
	// m_textXpStatus.setPosition(
	// 	m_gameView.getCenter() - (m_gameView.getSize() / 2.f));
	m_textXpStatus.setPosition(
		m_gameView.getCenter().x - (m_gameView.getSize().x / 2.f)
		, m_gameView.getCenter().y - (m_gameView.getSize().x / 2.f) + 10.f);
	return (true);
}


//modifier
void Gui::setLevel(const int level)
{
	std::stringstream ss;
	ss << "Level: " << level;
	m_textLevel.setString(ss.str());
}

//functions
void Gui::update(float playerXp, float playerXpToLevelUp)
{
	std::stringstream ss;
	ss << playerXp << "xp / " << playerXpToLevelUp << "xp => levelUp";
	m_textXpStatus.setString(ss.str());
	m_textLevel.setPosition(
		m_gameView.getCenter() - (m_gameView.getSize() / 2.f));
	m_textXpStatus.setPosition(
		m_gameView.getCenter().x - (m_gameView.getSize().x / 2.f)
		, m_gameView.getCenter().y - (m_gameView.getSize().x / 2.f) + 10.f);
}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_textLevel);
	target.draw(m_textXpStatus);
}
