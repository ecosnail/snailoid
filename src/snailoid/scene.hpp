#pragma once

#include "game_objects.hpp"
#include "levels.hpp"

#include <vector>
#include <cstdlib>
#include <ctime>

struct Scene {
	void loadLevel(const Level &level)
	{
		srand(static_cast<unsigned>(time(nullptr)));
		for (size_t i = 0; i < level.map.size(); i++) {
			int x = i % 16;
			int y = i / 16;

			size_t idx = level.map[i];

			if (level.blocks[idx].content != BlockContent::EMPTY) {
				blocks.push_back(level.blocks[idx]);
				blocks.back().x = x * 15;
				blocks.back().y = y * 12;
			}
		}

		pad.position = 0.5f;
	}

	std::vector<Block> blocks;
	Pad pad;
};
