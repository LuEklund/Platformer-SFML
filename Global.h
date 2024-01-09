#pragma once
#include <array>
#include <string>

namespace gbl
{
	constexpr unsigned short			GIMMY_TURN_WAIT_SECCONDS = 1;
	constexpr float						LASER_GUN_COOLDOWN = 1.f;

	namespace MAP
	{
		constexpr unsigned short		OUTLINE_THICKNESS = 1;
		constexpr unsigned short		CELL_SIZE = 16;
		constexpr unsigned short		COLUMNS = 211;
		constexpr unsigned short		ROWS = 45;
	}

	enum class Cell
	{
		EMPTY,
		BLOCK,
		BRICK,
		CLOUD_TOP_LEFT,
		CLOUD_TOP_MID,
		CLOUD_TOP_RIGHT,
		CLOUD_BOT_LEFT,
		CLOUD_BOT_MID,
		CLOUD_BOT_RIGHT
	};

	using Map = std::array<std::array<Cell, MAP::ROWS>, MAP::COLUMNS>;
}
