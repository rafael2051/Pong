#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RenderWindow.hpp"
#include "Player.hpp"

RenderWindow::RenderWindow(const char * p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL){

		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
		screenSurface = SDL_GetWindowSurface(window);
}

void RenderWindow::drawLine(int p_x1, int p_y1, int p_x2, int p_y2, 
							int loaping){

	for(int j = 0;j < loaping; j++, p_y1 += 30, p_y2 += 30){
		for(int i = 0;i < 10;i++){
			SDL_RenderDrawLine(renderer, p_x1 + i, p_y1, p_x2 + i, p_y2);
		}
	}
}

void RenderWindow::setLines(int score){
	switch(score){
		
		case 0 : left_l1 = true; up_l = true; down_l = true; 
				 right_l1 = true; middle_l = false; left_l2 = true;
				 right_l2 = true; break;
		case 1 : left_l1 = false; up_l = false; down_l = false; 
				 right_l1 = true; middle_l = false; left_l2 = false;
				 right_l2 = true; break;
		case 2 : left_l1 = false; up_l = true; down_l = true; 
				 right_l1 = true; middle_l = true; left_l2 = true;
				 right_l2 = false; break;
		case 3 : left_l1 = false; up_l = true; down_l = true; 
				 right_l1 = true; middle_l = true; left_l2 = false;
				 right_l2 = true; break;
		case 4 : left_l1 = true; up_l = false; down_l = false; 
				 right_l1 = true; middle_l = true; left_l2 = false;
				 right_l2 = true; break;
		case 5 : left_l1 = true; up_l = true; down_l = true; 
				 right_l1 = false; middle_l = true; left_l2 = false;
				 right_l2 = true; break;
		case 6 : left_l1 = true; up_l = true; down_l = true; 
				 right_l1 = false; middle_l = true; left_l2 = true;
				 right_l2 = true; break;
		case 7 : left_l1 = false; up_l = true; down_l = false; 
				 right_l1 = true; middle_l = false; left_l2 = false;
				 right_l2 = true; break;
		case 8 : left_l1 = true; up_l = true; down_l = true; 
				 right_l1 = true; middle_l = true; left_l2 = true;
				 right_l2 = true; break;
		case 9 : left_l1 = true; up_l = true; down_l = false; 
				 right_l1 = true; middle_l = true; left_l2 = false;
				 right_l2 = true; break;

	}
}

void RenderWindow::drawNumber(int player, int score){
	int x = 40 + (900 * player);
	int y1 = 20;
	int y2 = 40;
	setLines(score);
	if(left_l1)
		for(int i = 0; i < 5; i++)
			SDL_RenderDrawLine(renderer, x + i, y1, x + i, y2);
	if(up_l)
		for(int i = 0; i < 5; i++)
			SDL_RenderDrawLine(renderer, x, y1 + i, x + 24, y1 + i);
	if(down_l)
		for(int i = 0; i < 5; i++)
			SDL_RenderDrawLine(renderer, x, y2 + 20 + i, x + 24, y2 + 20 + i);
	if(right_l1)
		for(int i = 0; i < 5; i++)
			SDL_RenderDrawLine(renderer, x + 20 + i, y1, x + 20 + i, y2 + 4);
	if(middle_l)
		for(int i = 0; i < 5; i++)
			SDL_RenderDrawLine(renderer, x, 1.36 *((y1 + y2)/2) + i, x + 24, 1.36 * ((y1 + y2)/2) + i);
	if(left_l2)
		for(int i = 0; i < 5; i++)
			SDL_RenderDrawLine(renderer, x + i, y1 +20, x + i, y2 + 20);
	if(right_l2)
		for(int i = 0; i < 5; i++)
			SDL_RenderDrawLine(renderer, x + 20 + i, y1 + 20, x + 20 + i, y2 + 20 + 4);
}	

void RenderWindow::clear(){
	SDL_RenderClear(renderer);}
	
void RenderWindow::render(SDL_Texture* tex, SDL_Rect pos){}

void RenderWindow::setRender(int set){
	
	if(set == 1)
		SDL_SetRenderDrawColor(renderer, 100, 200, 150, SDL_ALPHA_OPAQUE);
	else if(set == 0)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void RenderWindow::display(){
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp(){
	SDL_DestroyWindow(window);
}