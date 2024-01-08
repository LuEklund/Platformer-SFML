#include "LaserGun.h"
LaserGun::LaserGun(sf::RenderWindow &window)
	: m_window(window)
{
}

LaserGun::~LaserGun()
{
}

//init
bool LaserGun::initLaserGun(Player *player)
{
	if (!player)
	{
		std::cout << "NO PLAYER passed to LaserGun!" << std::endl;
		return false;
	}
	if (!m_bufferSound.loadFromFile("assets/laser1.mp3"))
	{
		std::cout << "falied to load laser sound" << std::endl;
		return false;
	}
	m_sound.setBuffer(m_bufferSound);
	m_pPlayer = player;
	m_laser.resize(4);
	m_laser.setPrimitiveType(sf::TriangleStrip);
	m_laser[0].color = sf::Color::Red;
	m_laser[1].color = sf::Color::Red;
	m_laser[2].color = sf::Color::Red;
	m_laser[3].color = sf::Color::Red;

	m_laserLength = 100.f;
	m_laserHalfThickness = 2.f;

	m_aim.resize(2);
	m_aim.setPrimitiveType(sf::Lines);
	m_aim[0].color = sf::Color::White;
	m_aim[1].color = sf::Color::White;

	m_cooldown = 0.f;
	return true;
}

//functions
bool LaserGun::upgrade(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Num1:
		m_laserLength += 100.f;
		m_pPlayer->setLevelUp(false);
		return (true);
	}
	return (false);
}

void LaserGun::update(const float &dt, std::vector<std::unique_ptr<Entity>> &enemies)
{
	
	sf::Vector2f mouseWorldPos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	sf::Vector2f direction = mouseWorldPos - m_pPlayer->getPosition();
	sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x + direction.y*direction.y);
	sf::Vector2f extendedMouseWorldPos = m_pPlayer->getPosition() + unitDirection * m_laserLength;
	
	m_aim[0].position = extendedMouseWorldPos;
	m_aim[1].position = m_pPlayer->getPosition();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
	&& m_cooldown >= gbl::LASER_GUN_COOLDOWN)
	{
		m_sound.play();
		sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);
		sf::Vector2f offset = m_laserHalfThickness * unitPerpendicular;

		m_laser[0].position = extendedMouseWorldPos + offset;
		m_laser[1].position = m_pPlayer->getPosition() + offset;
		m_laser[2].position = extendedMouseWorldPos - offset;
		m_laser[3].position = m_pPlayer->getPosition() - offset;

		m_cooldown = 0;
		for (std::unique_ptr<Entity> &e : enemies)
		{
			Gimmy *gimmy = dynamic_cast<Gimmy *>(e.get());
			if (gimmy)
			{
				if (m_laser.getBounds().intersects(gimmy->getGlobalBounds()))
					gimmy->kill();
			}
		}
	}
	m_cooldown += dt;
}

void LaserGun::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (m_cooldown < gbl::LASER_GUN_COOLDOWN)
		target.draw(m_laser);
	target.draw(m_aim);
}
