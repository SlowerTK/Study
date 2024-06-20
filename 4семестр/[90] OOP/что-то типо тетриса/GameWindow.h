#pragma once
#include "resources.h"
#define SCREEN_WIDTH  500
#define SCREEN_HEIGHT 600
#define dField		  0
#define dFigure		  1
#define dSand		  2
#define COLUMNS	      80
#define ROWS		  184
#define BLOCK_SIZE	  8
#define PIXEL_SIZE	  4
#define delayMove 5
#define delaySand 5

enum Colors {
	red = 1,
	green = 2,
	blue = 3,
	yellow = 4,
};

enum Types {
	line = 1,
	square = 2,
	triangle = 3,
	zigzag = 4,
	zigzag2 = 5,
	letterL = 6,
	letterL2 = 7,
};

struct Sand {
	Sand() : color(0), isStruct(dField) {};
	int color;
	int isStruct;
};

class Window {
public:
	Window();
	~Window();
	void Renderer(std::vector<std::vector<Sand>>& GameFild, int figure, int score);
	int CreateStartMenu();
	int RanderPauseMenu();
	bool GameEventsChecker(bool &quit, bool& gameover, int& cx, int& dt);
	bool GameoverEventsChecker();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Event e;
	bool Initialize();
	bool CreateGameThings();
	void RanderGameField(std::vector<std::vector<Sand>>& GameFild);
	void RanderMenu();
	void RanderNextFigure(int figure);
	void RanderInscriptions();
	void RanderScoreCount(int score);
	void RanderGameFieldGameOver();
	void RanderStartMenu();
	void CreatePause();
};
