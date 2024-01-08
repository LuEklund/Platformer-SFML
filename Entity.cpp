#include "Entity.h"


// protected functions
void Entity::checkEdge(int x, int y)
{
	if (m_onEdge || x < 0 || x > gbl::MAP::COLUMNS - 1 || y < 0 || y > gbl::MAP::ROWS - 1)
		return ;
	if (m_map[x][y] == gbl::Cell::EMPTY && m_canJump)
	{
		m_onEdge = true;
		// m_map[x][y] = '2';
	}
}

bool Entity::mapColision(float desiredXPosition, float desiredYPosition)
{
	m_onEdge = false;

	float cellX = desiredXPosition / static_cast<float>(gbl::MAP::CELL_SIZE);
	float cellY = desiredYPosition / static_cast<float>(gbl::MAP::CELL_SIZE);

	int x = 0;
	int y = 0;

	bool collision = false;

	for (size_t i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0://top left
			x = static_cast<int>(floor(cellX));
			y = static_cast<int>(floor(cellY));
			break;
		case 1://top right
			x = static_cast<int>(ceil(cellX));
			y = static_cast<int>(floor(cellY));
			break;
		case 2://bottom left
			x = static_cast<int>(floor(cellX));
			y = static_cast<int>(ceil(cellY));
			checkEdge(x,y+1);
			break;
		case 3://bottom right
			x = static_cast<int>(ceil(cellX));
			y = static_cast<int>(ceil(cellY));
			checkEdge(x,y+1);
			break;
		}
		if (x < 0 || x > gbl::MAP::COLUMNS - 1 || y < 0 || y > gbl::MAP::ROWS - 1)
			collision = true;
		else if (m_map[x][y] == gbl::Cell::BLOCK)
			collision = true;
	}
	return (collision);
}


void Entity::checkSurroundingTiles(const float &dt)
{
	m_HorizontalColision = false;
	m_onEdge = false;
	bool	horizontalColission = mapColision(
			m_sprite.getPosition().x + m_velocity.x * dt,
			m_sprite.getPosition().y);
	bool	verticalColission = mapColision(
			m_sprite.getPosition().x,
			m_sprite.getPosition().y + m_velocity.y * dt);

	if (horizontalColission)
	{
		m_velocity.x = 0;
		m_HorizontalColision = true;
	}
	if (verticalColission)
	{
		if (m_velocity.y > 0)
			m_canJump = true;
		m_velocity.y = 0;
	}
}

//constructor
Entity::Entity(gbl::Map &map)
	: m_map(map)
	, m_maxVelocity(40.f)
	, m_acceleration(40.f)
	, m_deceleration(2.f)
	, m_canJump(false)
	, m_HorizontalColision(false)
	, m_alive(true)
	, m_onEdge(false)
{
}

Entity::~Entity()
{
}

//Modifier
void Entity::setPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void Entity::kill()
{
	m_sprite.setColor(sf::Color::Red);
	m_alive = false;
}

//accessors
const bool Entity::getAlive() const
{
	return (m_alive);
}

const bool Entity::getHorizontalCollision() const
{
	return false;
}

const sf::Vector2f Entity::getPosition() const
{
	return(m_sprite.getPosition());
}

const sf::Vector2f Entity::getVelocity() const
{
	return (m_velocity);
}

const sf::Vector2f Entity::getGridPosition() const
{
	return(sf::Vector2f(
		m_sprite.getPosition().x / static_cast<float>(gbl::MAP::CELL_SIZE),
		m_sprite.getPosition().y / static_cast<float>(gbl::MAP::CELL_SIZE)));
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	return (m_sprite.getGlobalBounds());
}

// function
void Entity::changeDirectionX(const float &dt, const float dir_x)
{
	m_velocity.x += m_acceleration * dir_x * dt;
}

void Entity::changeDirectionY(const float &dt, const float dir_y)
{
	m_velocity.y += m_acceleration * dir_y * dt;
}

void Entity::move(const float &dt)
{
	/*
	These functions check which direction our velocity is.
	Then based on that adds or subtracts with the deceleration.
	Finally checks that we are not going above or below our Max/Min velocity.
	*/
	if (m_velocity.x > 0.f) 
	{
		m_velocity.x -= m_deceleration * dt;
		if (m_velocity.x > m_maxVelocity)
			m_velocity.x = m_maxVelocity;
		else if (m_velocity.x < 0.f)
			m_velocity.x = 0.f;
	}
	else if (m_velocity.x < 0.f)
	{
		m_velocity.x += m_deceleration * dt;
		if (m_velocity.x < -1 * m_maxVelocity)
			m_velocity.x = -1 * m_maxVelocity;
		if (m_velocity.x > 0.f)
			m_velocity.x = 0.f;
	}
	if (m_velocity.y > 0.f)
	{
		m_velocity.y -= m_deceleration * dt;
		if (m_velocity.y > m_maxVelocity)
			m_velocity.y = m_maxVelocity;
		else if (m_velocity.y < 0.f)
			m_velocity.y = 0.f;
	}
	else if (m_velocity.y < 0.f)
	{
		m_velocity.y += m_deceleration * dt;
		if (m_velocity.y < -1 * m_maxVelocity)
			m_velocity.y = -1 * m_maxVelocity;
		if (m_velocity.y > 0.f)
			m_velocity.y = 0.f;
	}

	
	/*check that we are no colliding with something in the map*/
	checkSurroundingTiles(dt);

	//Finally we move after going trough all the safe guards
	m_sprite.move(m_velocity * dt); 
}

