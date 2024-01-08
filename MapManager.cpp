#include "MapManager.h"
MapManager::MapManager(gbl::Map	&map)
	: m_map(map)
	, m_pPlayer(NULL)
{

}

MapManager::~MapManager()
{
}

bool MapManager::initMapManager(Player *player, std::vector<std::unique_ptr<Entity>> &enemies)
{
	m_pPlayer = player;
	if (!m_mapImage.loadFromFile("assets/LevelSketch0.png"))
	{
		std::cout << "Failed to load levelImage!" << std::endl;
		return false;
	}
	if (!m_mapTextures.loadFromFile("assets/MapStuff.png"))
	{
		std::cout << "Failed to load Map Stuff!" << std::endl;
		return false;
	}
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int index = y*4+x;
			std::cout << "m_mapSprites["<<index<<"] = " << x * gbl::MAP::CELL_SIZE << " | "
			<< y * gbl::MAP::CELL_SIZE << " | "
			<< gbl::MAP::CELL_SIZE << std::endl;
			m_mapSprites[index].setTexture(m_mapTextures);
			m_mapSprites[index].setTextureRect(sf::IntRect(
				x * gbl::MAP::CELL_SIZE
				, y * gbl::MAP::CELL_SIZE
				, gbl::MAP::CELL_SIZE
				, gbl::MAP::CELL_SIZE
			));
		}
	}
	// m_mapSprites[0].setTextureRect(sf::IntRect(0,16,16,16));
	for (unsigned short x = 0; x < gbl::MAP::COLUMNS; x++)
	{
		for (unsigned short y = 0; y < gbl::MAP::ROWS; y++)
		{
			sf::Color pixel = m_mapImage.getPixel(x, y);

			// std::cout << "checking x: " << x
			// << ", y: " << y << std::endl;

			if (sf::Color(0, 0, 0) == pixel)
			{
				m_map[x][y] = gbl::Cell::BLOCK;
			}
			else if (sf::Color(255, 120, 0) == pixel)
			{
				m_map[x][y] = gbl::Cell::BRICK;
			}
			else if (sf::Color(255, 0, 0) == pixel)
			{
				m_pPlayer->setPosition(
					static_cast<float>(gbl::MAP::CELL_SIZE * x),
					static_cast<float>( gbl::MAP::CELL_SIZE * (y - gbl::MAP::ROWS/3)));
				m_map[x][y] = gbl::Cell::EMPTY;

				// m_map[x][y] = 'P';
				// i_mario.set_position(CELL_SIZE * a, CELL_SIZE * (b - map_height));
			}
			else if (sf::Color(210, 100, 0) == pixel)
			{
				m_map[x][y] = gbl::Cell::EMPTY;
				enemies.push_back(std::make_unique<Gimmy>(m_map,
					*player,
					static_cast<float>(gbl::MAP::CELL_SIZE * x),
					static_cast<float>( gbl::MAP::CELL_SIZE * (y - gbl::MAP::ROWS/3))));
				// i_enemies.push_back(std::make_shared<Goomba>(sf::Color(0, 0, 85) == i_background_color, CELL_SIZE * a, CELL_SIZE * (b - map_height)));
			}//CLOUDS
			else if (sf::Color(240, 255, 255) == pixel)
				m_map[x][y] = gbl::Cell::CLOUD_TOP_LEFT;
			else if (sf::Color(220, 255, 255) == pixel)
				m_map[x][y] = gbl::Cell::CLOUD_TOP_MID;
			else if (sf::Color(200, 255, 255) == pixel)
				m_map[x][y] = gbl::Cell::CLOUD_TOP_RIGHT;
			else if (sf::Color(180, 255, 255) == pixel)
				m_map[x][y] = gbl::Cell::CLOUD_BOT_LEFT;
			else if (sf::Color(160, 255, 255) == pixel)
				m_map[x][y] = gbl::Cell::CLOUD_BOT_MID;
			else if (sf::Color(140, 255, 255) == pixel)
				m_map[x][y] = gbl::Cell::CLOUD_BOT_RIGHT;
			else
			{
				m_map[x][y] = gbl::Cell::EMPTY;
				// i_map_manager.set_map_cell(a, b, Cell::Empty);
			}
			// if (x == 23)
			// 	return false;
			// std::cout << "is: "  << m_map[x][y]
			// << "color R: " << (int)pixel.r << ", G:" << (int)pixel.g << ", B: " << (int)pixel.b << std::endl;
		}
	}
	return (true);
}

void MapManager::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::Vector2f tileSize(
		static_cast<float>(gbl::MAP::CELL_SIZE),
		static_cast<float>(gbl::MAP::CELL_SIZE));

	int heightOfMap = static_cast<int>(gbl::MAP::ROWS) / 3;

	int startX = static_cast<int>(m_pPlayer->getGridPosition().x) - 10;
	startX = startX > 0 ? startX : 0;
	int endX = static_cast<int>(m_pPlayer->getGridPosition().x) + 10 + 1;
	endX = endX < gbl::MAP::COLUMNS ? endX : gbl::MAP::COLUMNS;

	int startY = static_cast<int>(m_pPlayer->getGridPosition().y) - 10;
	startY = startY > 0 ? startY : 0;
	int endY = static_cast<int>(m_pPlayer->getGridPosition().y) + 10 + 1;
	endY = endY < heightOfMap ? endY : heightOfMap;

	sf::Sprite	spriteStamp = m_mapSprites[1];

	int layerY = 0;

	for (int layer = 2; layer >= 0; layer--)
	{
		if (layer == 1)
			continue;
		for (int x = startX; x < endX; x++)
		{
			for (int y = startY; y < endY; y++)
			{
				layerY = y + layer * heightOfMap;
				switch (m_map[x][layerY])
				{
				case gbl::Cell::BLOCK:
					spriteStamp = m_mapSprites[0];
					break;
				case gbl::Cell::BRICK:
					spriteStamp = m_mapSprites[4];
					break;
				case gbl::Cell::CLOUD_TOP_LEFT:
					spriteStamp = m_mapSprites[1];
					break;
				case gbl::Cell::CLOUD_TOP_MID:
					spriteStamp = m_mapSprites[2];
					break;
				case gbl::Cell::CLOUD_TOP_RIGHT:
					spriteStamp = m_mapSprites[3];
					break;
				case gbl::Cell::CLOUD_BOT_LEFT:
					spriteStamp = m_mapSprites[5];
					break;
				case gbl::Cell::CLOUD_BOT_MID:
					spriteStamp = m_mapSprites[6];
					break;
				case gbl::Cell::CLOUD_BOT_RIGHT:
					spriteStamp = m_mapSprites[7];
					break;
				}
				spriteStamp.setPosition(x * tileSize.x, y * tileSize.y);
				if (m_map[x][layerY] != gbl::Cell::EMPTY)
					target.draw(spriteStamp);
			}
		}
	}
}
