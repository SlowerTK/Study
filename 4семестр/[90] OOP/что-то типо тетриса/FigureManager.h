#pragma once
#include "GameWindow.h"

class Figure {
public:
	Figure(int color, int type);
	bool MoveFigure(int x, int y);
	void RotateFigure();
	void SandCreator();
	int GetColor() { return color; };
	void SandMove();
	std::vector<std::vector<Sand>>& GetGameFild() { return GameFild; };
	Figure& operator=(const Figure&& other)noexcept;
	int LineDestroyer();
	bool GameoverChecker();
	void GameOverAnimation();
private:
	std::vector<std::vector<Sand>> GameFild{ COLUMNS, std::vector<Sand>(ROWS) };
	std::vector<std::vector<int>> tempArr{ COLUMNS, std::vector<int>(ROWS) };
	int color;
	int type;
	int rotation;
	int prevX, prevY;
};