#include "GameWindow.h"

Window::Window() {
	if(!this->Initialize())
		quick_exit(1);
	if(!this->CreateGameThings()) {
		SDL_Log("Failed to create game things!");
		quick_exit(1);
	}
}
void Window::Renderer(std::vector<std::vector<Sand>>& GameFild, int figure, int score) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	RanderGameField(GameFild);
	RanderMenu();
	RanderInscriptions();
	RanderScoreCount(score);
	RanderNextFigure(figure);
	if(!figure)
		RanderGameFieldGameOver();
	SDL_RenderPresent(renderer);
}
int Window::CreateStartMenu() {
	RanderStartMenu();
	SDL_Event e;
	int menu = 0;
	while(true) {
		while(SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT) {
				menu = -1;
			}
			if(e.type == SDL_MOUSEBUTTONDOWN) {
				if(e.button.x > SCREEN_WIDTH / 6 && e.button.x < SCREEN_WIDTH / 2 && e.button.y > SCREEN_HEIGHT / 2 && e.button.y < SCREEN_HEIGHT / 2 + 70) {
					SDL_Log("Start");
					menu = 1;
				}
				if(e.button.x > SCREEN_WIDTH / 6 && e.button.x < SCREEN_WIDTH / 2 && e.button.y > SCREEN_HEIGHT / 2 + 100 && e.button.y < SCREEN_HEIGHT / 2 + 170) {
					SDL_Log("Exit");
					menu = -1;
				}
			}
		}
		if(menu)
			break;
	}
	return menu;
}
int Window::RanderPauseMenu() {
	CreatePause();
	SDL_Log("Pause");
	while(true) {
		if(SDL_PollEvent(&e) != 0) {
			if(this->e.type == SDL_KEYDOWN && this->e.key.keysym.sym == SDLK_ESCAPE && this->e.key.repeat == 0) {
				SDL_Log("Unpause");
				return 0;
			}
		}
		if(this->e.type == SDL_QUIT) {
			SDL_Log("Quit");
			return 1;
		}
		SDL_Delay(10);
	}
}
bool Window::GameEventsChecker(bool& quit, bool& gameover, int& cx, int& dt) {
	while(SDL_PollEvent(&e) != 0) {
		if(e.type == SDL_QUIT) {
			SDL_Log("Quit");
			quit = true;
		}
		if(e.type == SDL_KEYUP) {
			if(e.key.keysym.sym == SDLK_DOWN)
				dt = delayMove;
			if(e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT)
				cx = 0;
		}
		if(e.type == SDL_KEYDOWN) {
			if(e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat == 0) {
				if(RanderPauseMenu() == 1) {
					quit = true;
					gameover = false;
				}
			}
			if(e.key.keysym.sym == SDLK_DOWN) {
				dt = 1;
			}
			if(e.key.keysym.sym == SDLK_LEFT) {
				cx = -1;
			}
			if(e.key.keysym.sym == SDLK_RIGHT) {
				cx = 1;
			}
			if(e.key.keysym.sym == SDLK_UP && e.key.repeat == 0) {
				return true;
			}
		}
	}
	return false;
}
bool Window::GameoverEventsChecker() {
	bool quit = false;
	while(SDL_PollEvent(&e) != 0) {
		if(e.type == SDL_QUIT) {
			quit = true;
		}
		if(e.type == SDL_MOUSEBUTTONDOWN) {
			if(e.button.x > SCREEN_WIDTH / 6 && e.button.x < SCREEN_WIDTH / 2 && e.button.y > SCREEN_HEIGHT / 2 + 100 && e.button.y < SCREEN_HEIGHT / 2 + 170) {
				SDL_Log("Exit");
				quit = true;
			}
		}
	}
	return quit;
}
bool Window::Initialize() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
		return false;
	}
	if(TTF_Init() == -1) {
		SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError());
		return false;
	}
	return true;
}
bool Window::CreateGameThings() {
	this->window = SDL_CreateWindow("Sandtrix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(this->window == NULL) {
		SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
		return false;
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if(this->renderer == NULL) {
		SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
		return false;
	}
	this->font = TTF_OpenFont("./Softie Cyr.ttf", 24);
	if(this->font == NULL) {
		SDL_Log("Failed to load font! SDL_ttf Error: %s", TTF_GetError());
		return false;
	}
	return true;
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

void Window::RanderGameField(std::vector<std::vector<Sand>>& GameFild) {
	SDL_Rect rect;
	for(int i = 0; i < COLUMNS; i++) {
		for(int j = 0; j < ROWS; j++) {
			if(GameFild[i][j].color != 0) {
				rect = { i * PIXEL_SIZE + (SCREEN_WIDTH / 3 - COLUMNS * 2) , j * PIXEL_SIZE - 35 * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
				switch(GameFild[i][j].color) {
				case red:
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
					break;
				case green:
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
					break;
				case blue:
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					break;
				case yellow:
					SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
					break;
				default:
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					break;
				}
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
}

void Window::RanderMenu() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH * 2 / 3, 0, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT);
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 11 / 24, SCREEN_WIDTH, SCREEN_HEIGHT * 11 / 24);
	SDL_Rect nextFigure{ ((SCREEN_WIDTH * 2 / 3) + ((SCREEN_WIDTH / 3) / 5)), (SCREEN_HEIGHT / 4), (SCREEN_HEIGHT / 6), (SCREEN_HEIGHT / 6) };
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
	SDL_RenderFillRect(renderer, &nextFigure);
	SDL_Color textColor = { 255, 255, 255 };
}

void Window::RanderNextFigure(int figure) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect rect{ (SCREEN_WIDTH * 2 / 3) + ((SCREEN_WIDTH / 3) / 5), SCREEN_HEIGHT / 4, (SCREEN_WIDTH / 3) - 10, SCREEN_HEIGHT / 6 };
	switch(figure) {
	case line:
		for(int i = 0; i < 4; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 16 + i * 16, SCREEN_HEIGHT / 3 - 8 , 16, 16 };
			SDL_RenderFillRect(renderer, &rect);
		}
		break;
	case square:
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++) {
				rect = { (SCREEN_WIDTH * 11 / 15) + 32 + i * 16, SCREEN_HEIGHT / 3 - 16 + j * 16, 16, 16 };
				SDL_RenderFillRect(renderer, &rect);
			}
		}
		break;
	case triangle:
		for(int i = 0; i < 3; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 24 + i * 16, SCREEN_HEIGHT / 3, 16, 16 };
			SDL_RenderFillRect(renderer, &rect);
		}
		rect = { (SCREEN_WIDTH * 11 / 15) + 24 + 16, SCREEN_HEIGHT / 3 - 16, 16, 16 };
		SDL_RenderFillRect(renderer, &rect);
		break;
	case zigzag:
		for(int i = 0; i < 2; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 24 + i * 16, SCREEN_HEIGHT / 3 - 16, 16, 16 };
			SDL_RenderFillRect(renderer, &rect);
		}
		for(int i = 0; i < 2; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 40 + i * 16, SCREEN_HEIGHT / 3, 16, 16 };
			SDL_RenderFillRect(renderer, &rect);
		}
		break;
	case zigzag2:
		for(int i = 0; i < 2; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 40 + i * 16, SCREEN_HEIGHT / 3 - 16, 16, 16 };
			SDL_RenderFillRect(renderer, &rect);
		}
		for(int i = 0; i < 2; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 24 + i * 16, SCREEN_HEIGHT / 3, 16, 16 };
			SDL_RenderFillRect(renderer, &rect);
		}
		break;
	case letterL:
		for(int i = 0; i < 3; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 32, SCREEN_HEIGHT / 3 - 24 + i * 16, 16, 16 };
			SDL_RenderFillRect(renderer, &rect);
		}
		rect = { (SCREEN_WIDTH * 11 / 15) + 16 + 32, SCREEN_HEIGHT / 3 + 8, 16, 16 };
		SDL_RenderFillRect(renderer, &rect);
		break;
	case letterL2:
		for(int i = 0; i < 3; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 32 + 16, SCREEN_HEIGHT / 3 - 24 + i * 16, 16, 16 };
			SDL_RenderFillRect(renderer, &rect);
		}
		rect = { (SCREEN_WIDTH * 11 / 15) + 32, SCREEN_HEIGHT / 3 + 8, 16, 16 };
		SDL_RenderFillRect(renderer, &rect);
		break;
	default:
		break;
	}
}

void Window::RanderInscriptions() {
	TTF_SetFontSize(font, 30);
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Rect textRect{ SCREEN_WIDTH * 2 / 3 + 10, 10, 80, 40 };
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"Счёт: "), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	textRect.y = SCREEN_HEIGHT / 6 + 15;
	textRect.w = SCREEN_WIDTH / 3 - 15;
	textRect.h = 30;
	textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"След.фигура"), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	textRect.y = SCREEN_HEIGHT / 2 - 30;
	textRect.h = 130;
	textSurface = TTF_RenderUNICODE_Blended_Wrapped(font, (Uint16*)(L"Для паузы нажмите         Esc"), textColor, textRect.w + 10);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	textRect.y += 250;
	textRect.h = 80;
	TTF_SetFontSize(font, 16);
	textSurface = TTF_RenderUNICODE_Blended_Wrapped(font, (Uint16*)(L"Для управления  Используйте стрелочки"), textColor, textRect.w);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void Window::RanderScoreCount(int score) {
	SDL_Color textColor = { 255, 255, 255 };
	TTF_SetFontSize(font, 24);
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(std::to_wstring(score).c_str()), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect{ SCREEN_WIDTH * 2 / 3 + 80, 20, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void Window::RanderGameFieldGameOver() {
	SDL_Color textColor = { 255, 255, 255 };
	TTF_SetFontSize(font, 48);
	SDL_Rect menuRect{ SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12,  SCREEN_WIDTH / 2, 100 };
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"GAME"), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &menuRect);
	menuRect.y += 110;
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"OVER"), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &menuRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	SDL_Rect buttonE{ SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 100,  SCREEN_WIDTH / 3, 70 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &buttonE);

	textColor = { 0, 0, 0 };
	TTF_SetFontSize(font, 36);
	menuRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 100,  SCREEN_WIDTH / 3, 70 };
	textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"Выход"), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &menuRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_SetFontSize(font, 24);
}

void Window::RanderStartMenu() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH * 2 / 3, 0, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT);
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 11 / 24, SCREEN_WIDTH, SCREEN_HEIGHT * 11 / 24);
	SDL_Rect nextFigure{ ((SCREEN_WIDTH * 2 / 3) + ((SCREEN_WIDTH / 3) / 5)), (SCREEN_HEIGHT / 4), (SCREEN_HEIGHT / 6), (SCREEN_HEIGHT / 6) };
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
	SDL_RenderFillRect(renderer, &nextFigure);
	SDL_Color textColor = { 255, 255, 255 };
	TTF_SetFontSize(font, 48);
	SDL_Rect menuRect{ SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12,  SCREEN_WIDTH / 2, 100 };
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"Sandtrix"), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &menuRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_SetFontSize(font, 24);


	SDL_Rect buttonS{ SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2,  SCREEN_WIDTH / 3, 70 };
	SDL_Rect buttonE = buttonS;
	buttonE.y += 100;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &buttonS);
	SDL_RenderFillRect(renderer, &buttonE);

	textColor = { 0, 0, 0 };
	TTF_SetFontSize(font, 36);
	menuRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2,  SCREEN_WIDTH / 3, 70 };
	textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"Старт"), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &menuRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	menuRect.y += 100;
	textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"Выход"), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &menuRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_SetFontSize(font, 24);
	SDL_RenderPresent(renderer);
}

void Window::CreatePause() {
	SDL_Rect pauseRect{ SCREEN_WIDTH / 6 , SCREEN_HEIGHT / 3, (SCREEN_WIDTH / 3) , SCREEN_HEIGHT / 6 };
	SDL_Color textColor = { 255, 255, 255 };
	TTF_SetFontSize(font, 48);
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)(L"Pause"), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &pauseRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_SetFontSize(font, 24);
	SDL_RenderPresent(renderer);
}
