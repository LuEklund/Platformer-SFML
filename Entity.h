#pragma once
#include "SFML/Graphics.hpp"
#include "Global.h"
#include <cmath>
#include <iostream>
#include "AnimationComponent.h"

class Entity : public sf::Drawable
{
protected:
	//Core
	gbl::Map			&m_map;
	sf::RectangleShape	m_hitbox;
	sf::Sprite			m_sprite;
	bool				m_canJump;
	bool				m_alive;


	//movevemnt
	sf::Vector2f	m_velocity;
	float			m_maxVelocity;
	float			m_acceleration;
	float			m_deceleration;
	bool			m_HorizontalColision;
	bool			m_onEdge;

	//Aniamtion
	std::unique_ptr<AnimationComponent> m_pAnimationComponent;

	//protected functions
	void	checkEdge(int x, int y);
	void	checkSurroundingTiles(const float &dt);
	bool	mapColision(float desiredXPosition, float desiredYPositiony);
public:
	Entity(gbl::Map &map);
	virtual ~Entity();

	//modifier
	void			setPosition(float x, float y);
	virtual void	kill();

	//accessors
	const bool			getAlive() const;
	const bool			getHorizontalCollision() const;
	const sf::Vector2f	getPosition() const;
	const sf::Vector2f	getVelocity() const;
	const sf::Vector2f	getGridPosition() const;
	const sf::FloatRect	getGlobalBounds() const;

	//functions
	virtual void	changeDirectionX(const float &dt, const float dir_x);
	virtual void	changeDirectionY(const float &dt, const float dir_x);
	virtual void	move(const float &dt);

	virtual	void	update(const float &dt) = 0;
	virtual void	draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};


