#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Square.hpp"
#include "RenderWindow.hpp"

Square::Square(int p_x, int p_y) : pos_x(p_x), pos_y(p_y) {

	direction_x = LEFT;
	direction_y = uP;
	update_x = 2.0f;
	update_y = 0.5f;
}

bool Square::checkCollision(int player_x, int player_y1, int player_y2, int player){

	float delta = player_y2 - pos_y;

	if(player == 1){

		if(pos_x == player_x && pos_y + 10 >= player_y1
			&& pos_y <= player_y2){

			MODIFY_ANGLE: if((delta <= 70 && delta > 65) || (pos_y < player_y1))
				update_y = 2.8f;

			else if(delta <= 65 && delta > 60)
				update_y = 2.5f;

			else if(delta <= 60 && delta > 55)
				update_y = 2.1f;

			else if(delta <= 55 && delta > 50)
				update_y = 1.8f;

			else if(delta <= 50 && delta > 45)
				update_y = 1.4f;

			else if(delta <= 45 && delta > 40)
				update_y = 1.1f;

			else if(delta <= 40 && delta > 35)
				update_y = 0.8f;

			else if(delta <= 35 && delta > 30)
				update_y = 0.5f;

			else if(delta <= 30 && delta > 25)
				update_y = 0.9f;

			else if(delta <= 25 && delta > 20)
				update_y = 1.3f;

			else if(delta <= 20 && delta > 15)
				update_y = 1.6f;

			else if(delta <= 15 && delta > 10)
				update_y = 2.0f;

			else if(delta <= 10 && delta > 5)
				update_y = 2.5f;

			else if(delta <= 5 && delta >= 0)
				update_y = 2.8f;

			if(player == 2)
				goto BACK_TO_PLAYER2;

			direction_x = RIGHT;
			if(direction_y == uP) 
				direction_y = dOWN;
			else direction_y = uP;
			return true;
		}
	}

	else{
		if(pos_x + 10 == player_x && pos_y + 10 >= player_y1
			&& pos_y <= player_y2){	
			goto MODIFY_ANGLE;

			BACK_TO_PLAYER2:
			direction_x = LEFT;
			if(direction_y == uP) 
				direction_y = dOWN;
			else direction_y = uP;
			return true;
		}
	}

	if(pos_y <= 0){
		direction_y = dOWN;
	}
	if(pos_y + 10 >= 500){;
		direction_y = uP;
	}
	return false;
}

void Square::moveSquare(){

	if(direction_x == RIGHT)
		pos_x += update_x;
	if(direction_x == LEFT)
		pos_x -= update_x;
	if(direction_y == uP)
		pos_y -= update_y;
	if(direction_y == dOWN)
		pos_y += update_y;
}


void Square::drawSquare(RenderWindow * window){
	window->drawLine(pos_x, pos_y, pos_x, pos_y + 10, 1);
}

bool Square::checkIfIsOut(){
	if(pos_x <= 0 || pos_x >= 990){
		pos_x = 500.0f;
		pos_y = 250.0f;
		return true;
	}

	return false;
}