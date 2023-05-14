#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RenderWindow.hpp"

enum direction {
	LEFT = 1,
	RIGHT,
	uP,
	dOWN
};

class Square {

public:
	Square(int p_x, int p_y);
	bool checkCollision(int player_x, int player_y1, int player_y2, 
						int player);
	void moveSquare();
	void drawSquare(RenderWindow * window);
	bool checkIfIsOut();
private:
	float direction_x;
	float direction_y;
	float update_x;
	float update_y;
	float pos_x;
	float pos_y;
};