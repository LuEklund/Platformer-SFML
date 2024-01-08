#include "Player.h"

void Player::levelUp()
{
	std::cout << "LevelUp! " << m_Level << " -> ";
	m_Level++;
	std::cout << m_Level << std::endl;;
	m_xp -= m_xpToLevelUp;
	m_xpToLevelUp *= 2;
	std::cout << "xp to next lvl: " << m_xpToLevelUp
	<< "curxp: " << m_xp << std::endl;;
	m_levelUp = true;
	
}

Player::Player(gbl::Map &map)
	: Entity(map)
{
	m_maxVelocity = 300.f;
	m_acceleration = 1500.f;
	m_deceleration = 150.f;
	m_alive = true;
	m_xp = 0.f;
	m_xpToLevelUp = 1.f;
	m_Level = 0;
	m_levelUp = false;

}

Player::~Player()
{

}


//inits
bool Player::initPlayer()
{
	if (!m_texture.loadFromFile("assets/MarioWalk.png"))
	{
		std::cout << "FAILED to load player texture" << std::endl;
		return false;
	}
	// m_sprite.setTexture(m_texture);
	m_pAnimationComponent = std::make_unique<AnimationComponent>(m_sprite, m_texture);
	m_pAnimationComponent->addAniamtion("Walk", 1.f, 0, 0, 2, 0, 16, 16);
	return true;
}


// modifiers
void Player::setLevelUp(bool state)
{
	m_levelUp = state;
}

void Player::increaseXp(float xp)
{
	m_xp += xp;
}

//accessors
const bool &Player::LeveledUp() const
{
	return(m_levelUp);
}

const int &Player::getLevel() const
{
	return (m_Level);
}

const float &Player::getXp() const
{
	return (m_xp);
}

const float &Player::getXpToLevelUp() const
{
	return (m_xpToLevelUp);
}

// functions
void Player::update(const float &dt)
{
	if (m_xp > m_xpToLevelUp)
		levelUp();
	//this allows us to move in the x-axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
	|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		changeDirectionX(dt, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
	|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		changeDirectionX(dt, -1.f);
	//Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
	&& m_canJump)
	{
		changeDirectionY(1.f, -10.f);
		m_canJump = false;
	}
	//this makes sure we fall by gravity
	changeDirectionY(dt, .2f);
	if (m_velocity.x)
		m_pAnimationComponent->play("Walk", dt, m_velocity.x, 30.f);
	move(dt);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// std::cout << "PlayerX: " << m_shape.getPosition().x << ", PlayerY: " << m_shape.getPosition().y << std::endl;
	target.draw(m_sprite);
}
