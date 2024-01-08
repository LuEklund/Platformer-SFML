#include "Gimmy.h"

Gimmy::Gimmy(gbl::Map &map, Player &player, float x, float y)
	: Entity(map), m_player(player)
{
	m_sprite.setPosition(x,y);
	m_direction = false;
	m_maxVelocity = 30.f;
	m_acceleration = 500.f;
	m_deceleration = 2.f;
	m_turWait = 0.f;
}

Gimmy::~Gimmy()
{
}

//inits
bool Gimmy::initGimmy(sf::Texture &Texture)
{
	m_pAnimationComponent = std::make_unique<AnimationComponent>(m_sprite, Texture);
	m_pAnimationComponent->addAniamtion("Walk", 1.f, 0, 0, 1, 0, 16, 16);
	return true;
}

void Gimmy::kill()
{
	m_sprite.setColor(sf::Color::Red);
	m_player.increaseXp(1.f);
	std::cout << "Gimmy killed" << std::endl;
	m_alive = false;
}

//Functions
void Gimmy::update(const float &dt)
{
	m_pAnimationComponent->play("Walk", dt);
	if (this->m_alive
	&& m_sprite.getGlobalBounds().intersects(m_player.getGlobalBounds()))
	{
		if (m_player.getVelocity().y > 0)
		{
			this->kill();
			m_player.changeDirectionY(1.f, -5.f);
		}
		else
		{
			std::cout << "Player killed" << std::endl;
			m_player.kill();
		}
	}
	if (m_direction)
		changeDirectionX(dt, 1.f);
	else
		changeDirectionX(dt, -1.f);
	changeDirectionY(dt, 1.f);
	move(dt);
	if (m_turWait >= gbl::GIMMY_TURN_WAIT_SECCONDS
	&& (this->m_HorizontalColision
	|| this->m_onEdge))
	{
		m_turWait = 0.f;
		m_direction = !m_direction;
	}
	else
		m_turWait += dt;

}

void Gimmy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}
