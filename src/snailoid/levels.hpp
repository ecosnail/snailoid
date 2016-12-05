#pragma once

#include "game_objects.hpp"

#include <vector>
#include <utility>
#include <cstddef>
#include <cstdlib>
#include <ctime>

struct Level {
	Level(std::vector<BlockContent> content, std::vector<size_t> map)
		: map(std::move(map))
	{
		srand(static_cast<unsigned>(time(nullptr)));
		for (BlockContent &cont : content) {
			blocks.push_back(Block{ Color(rand() % (int)Color::MAX), cont });
		}
	}

	std::vector<Block> blocks;
	std::vector<size_t> map;
};

Level level0 = {
	// blocks
	{
		BlockContent::EMPTY,	// 0
		BlockContent::FULL	// 1
	},

	// level
	{
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	}
};
