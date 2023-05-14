#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player{
public:
	Player(int p_x, int p_y);
	int getPos_x();
	int getPos_y();
	void drawPlayer(RenderWindow * window);
	void movePlayer(const Uint8* keyState);
private:
	int pos_x;
	int pos_y;
};