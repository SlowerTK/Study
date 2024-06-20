#include "FigureManager.h"

int main(int argc, char* argv[]) {
	srand((unsigned)time(0));
	int newColor = rand() % 4 + 1, newType = rand() % 7 + 1;
	Window window;
	Figure FallingFigure(newColor, newType);
	newColor = rand() % 4 + 1;
	newType = rand() % 7 + 1;
	bool quit = true, gameover = false;
	int cx = 0, score = 0;
	int time = 1;
	int deltaTime = delayMove;
	if(window.CreateStartMenu() == 1) {
		quit = false;
	}
	bool IsFalling = true;
	while(!quit) {
		if(window.GameEventsChecker(quit, gameover, cx, deltaTime))
			FallingFigure.RotateFigure();
		if(!IsFalling) {
			FallingFigure = Figure(newColor, newType);
			IsFalling = true;
			newType = rand() % 7 + 1;
			newColor = rand() % 4 + 1;
		}
		FallingFigure.MoveFigure(cx, 0);
		if(time % deltaTime == 0)
			if(!FallingFigure.MoveFigure(0, 1)) {
				IsFalling = false;
				FallingFigure.SandCreator();
			}
		if(time % delaySand == 0)
			FallingFigure.SandMove();
		score += FallingFigure.LineDestroyer();
		window.Renderer(FallingFigure.GetGameFild(), newType, score / 10);
		if(FallingFigure.GameoverChecker()) {
			quit = true;
			gameover = true;
		}
		SDL_Delay(1);
		if(time++ > 1000)
			time = 1;
	}
	quit = false;
	if(gameover) {
		SDL_Log("GameOver");
		while(!quit) {
			quit = window.GameoverEventsChecker();
			FallingFigure.GameOverAnimation();
			window.Renderer(FallingFigure.GetGameFild(), 0, score / 10);
			SDL_Delay(5);
		}
	}
	return 0;
}