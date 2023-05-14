#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow{

public:
	RenderWindow(const char * p_title, int p_w, int p_h);
	void drawLine(int p_x1, int p_y1, int p_x2, int p_y2, 
				  int loaping);
	void drawNumber(int player, int score);
	void clear();
	void render(SDL_Texture* tex, SDL_Rect pos);
	void setRender(int set);
	void display();
	void cleanUp();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Surface * screenSurface;
	void setLines(int score);
	bool left_l1;
	bool left_l2;
	bool up_l;
	bool down_l;
	bool right_l1;
	bool right_l2;
	bool middle_l;
};