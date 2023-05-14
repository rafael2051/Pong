#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Player.hpp"
#include "Square.hpp"

enum KEYS{
	W = 1,
	S,
	UP,
	DOWN
};

int main(int argc, char * argv[]){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	RenderWindow window("Pong", 1000, 500);
	Mix_Chunk* pong_sound = Mix_LoadWAV("res\\Sound effect\\PingPong.mp3");
	if(!pong_sound) std::cout << "ERROR" << std::endl;
	SDL_Event event;

	//instances of players, info of which player the ball is going to,
	//and score of each player
	Player player1(100, 100);
	Player player2(900, 100);
	int player_active = 1;
	int p1_score = 0;
	int p2_score = 0;
	Square square(500, 250);

	//variables to control the amount of frames being updated per second
	float frameTime = 0;
	float frameTimeSquare = 0;
	float limitFrameTimeSquare = 0.005f;
	int previousTime = 0;
	int currentTime = 0;
	float deltaTime = 0;
	bool gameRunning = true;

	const Uint8* keyState;

	while(gameRunning){

		//calculates the difference of time in ms between the current
		//loap and the last loap
		previousTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) / 1000.0f;
		frameTime += deltaTime;
		frameTimeSquare += deltaTime;

		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
				gameRunning = false;
		}
		//get the last event of the keyboard
		keyState = SDL_GetKeyboardState(NULL);

		//check if s or w was pressed
		if((keyState[SDL_SCANCODE_S] || 
			keyState[SDL_SCANCODE_W]) && frameTime >= 0.01f){
			frameTime = 0;
			player1.movePlayer(keyState);
		}
		//check if the arrow up or down was pressed
		else if((keyState[SDL_SCANCODE_UP] ||
				keyState[SDL_SCANCODE_DOWN]) && frameTime >= 0.01f){
			frameTime = 0;
			player2.movePlayer(keyState);
		}

		//clean the window to draw new positions of each player and the ball
		window.setRender(0);
		window.clear();
		window.setRender(1);

		//draw the square the players are trying to hit 
		square.drawSquare(&window);

		//check if there it is a collision. The function checkCollision changes the direction 
		//of the square if he hits a player or a wall, returns true if he hits a player,
		//and returns false if he does not hit a player
		if(square.checkCollision(player1.getPos_x(), player1.getPos_y(), player1.getPos_y() + 70, 
							  player_active)){ player_active = 2;
			limitFrameTimeSquare -= 0.0002f;
			Mix_PlayChannel(1, pong_sound, 0);
		}

		if(square.checkCollision(player2.getPos_x(), player2.getPos_y(), player2.getPos_y() + 70, 
		 					  player_active)){ player_active = 1;
			limitFrameTimeSquare -= 0.0002f;
			Mix_PlayChannel(1, pong_sound, 0);
		}

		//check if the square has gone out of the screen, and in this case update the position of
		//the square to the center of the screen and update the score
		if(square.checkIfIsOut()){
			limitFrameTimeSquare = 0.005f;
			if(player_active == 1)
				p2_score++;
			if(player_active == 2)
				p1_score++;
		}

		if(p1_score > 9 || p2_score > 9){
			p1_score = 0;
			p2_score = 0;
		}


		if(frameTimeSquare >= limitFrameTimeSquare){
			frameTimeSquare = 0;
			square.moveSquare();
		}

		//draw the pattern in the middle and the players in the renderer
		window.drawLine(500, 18, 500, 28, 16);
		window.drawNumber(0, p1_score);
		window.drawNumber(1, p2_score);
		player1.drawPlayer(&window);
		player2.drawPlayer(&window);
		//display in the screen what was drawed in the renderer
		window.display();

	}

	window.cleanUp();

	Mix_Quit();
	SDL_Quit();
	return 0;
}