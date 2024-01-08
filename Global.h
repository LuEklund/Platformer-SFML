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

	struct Particle
	{
		float horizontal_speed;
		float vertical_speed;
		float x;
		float y;

		Particle(const float i_x, const float i_y, const float i_horizontal_speed = 0, const float i_vertical_speed = 0) :
			horizontal_speed(i_horizontal_speed),
			vertical_speed(i_vertical_speed),
			x(i_x),
			y(i_y)
		{

		}
	};

	using Map = std::array<std::array<Cell, MAP::ROWS>, MAP::COLUMNS>;
}
