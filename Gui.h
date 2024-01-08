#pragma once
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"

class Gui : public sf::Drawable
{
private:
	//the displayable elements
	sf::Text			m_textLevel;
	sf::Text			m_textXpStatus;
	sf::View			&m_gameView;

	

public:
	Gui(sf::View &gameView);
	~Gui();

	//inits
	bool	initGui(sf::Font &font);

	//modifier
	void	setLevel(const int level);

	//functions
	void	update(float playerXp, float playerXpToLevelUp);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


