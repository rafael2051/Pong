#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Player.hpp"
enum KEYS{
	W = 1,
	S,
	UP,
	DOWN
};

Player::Player(int p_x, int p_y) : pos_x(p_x), pos_y(p_y){}

int Player::getPos_x(){
	return pos_x;
}

int Player::getPos_y(){
	return pos_y;
}

void Player::drawPlayer(RenderWindow * window){
	window->drawLine(pos_x, pos_y, pos_x, pos_y + 70, 1);
}

void Player::movePlayer(const Uint8* keyState){
	if( (keyState[SDL_SCANCODE_W] ||	
		keyState[SDL_SCANCODE_UP]) 
		&& pos_y >= 0) pos_y -= 5;
	else if( (keyState[SDL_SCANCODE_S] ||
			keyState[SDL_SCANCODE_DOWN]) 
			&& pos_y <= 430) pos_y += 5;
}