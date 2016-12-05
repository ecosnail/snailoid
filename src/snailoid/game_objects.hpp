#pragma once

enum class Color : int {
	BLACK,
	WHITE,
	RED,
	GREEN,
	BLUE,
	CYAN,
	MAGENTA,
	YELLOW,

	MAX,
};

enum class BlockContent {
	EMPTY,
	FULL,
};

struct Block {
	Color color;
	BlockContent content;
	int x;
	int y;
};

struct Pad {
	float position;
};

