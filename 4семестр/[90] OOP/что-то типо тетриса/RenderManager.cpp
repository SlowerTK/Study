#include "RenderManager.h"

RenderManager::RenderManager(Figure& ref) : refFigure(ref) {
}
RenderManager::~RenderManager() {

}
void RenderManager::Renderer(int figure, int score) {
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(refFigure.GetWindow().GetRenderer());
	RanderGameField();
		//RanderGameFieldBorder();
	RanderMenu();
	RanderInscriptions();
	RanderScoreCount(score);
	RanderNextFigure(figure);

	if(!figure)
		RanderGameFieldGameOver();
	SDL_RenderPresent(refFigure.GetWindow().GetRenderer());
}
void RenderManager::RanderGameField() const {
	SDL_Rect rect;
	for(int i = 0; i < COLUMNS; i++) {
		for(int j = 0; j < ROWS; j++) {
			if(refFigure.GetGameFild()[i][j].color != 0) {
				rect = { i * PIXEL_SIZE + (SCREEN_WIDTH / 3 - COLUMNS * 2) , j * PIXEL_SIZE - 35 * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
				switch(refFigure.GetGameFild()[i][j].color) {
				case red:
					SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 255, 0, 0, 255);
					break;
				case green:
					SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 0, 255, 0, 255);
					break;
				case blue:
					SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 0, 0, 255, 255);
					break;
				case yellow:
					SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 255, 255, 0, 255);
					break;
				}
				SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
			}
		}
	}
}

void RenderManager::RanderMenu() const {
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawLine(refFigure.GetWindow().GetRenderer(), SCREEN_WIDTH * 2 / 3, 0, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT);
	SDL_RenderDrawLine(refFigure.GetWindow().GetRenderer(), SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 11 / 24, SCREEN_WIDTH, SCREEN_HEIGHT * 11 / 24);
	SDL_Rect nextFigure{ ((SCREEN_WIDTH * 2 / 3) + ((SCREEN_WIDTH / 3) / 5)), (SCREEN_HEIGHT / 4), (SCREEN_HEIGHT / 6), (SCREEN_HEIGHT / 6) };
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 25, 25, 25, 255);
	SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &nextFigure);
	SDL_Color textColor = { 255, 255, 255 };
}

void RenderManager::RanderStartMenu() {
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawLine(refFigure.GetWindow().GetRenderer(), SCREEN_WIDTH * 2 / 3, 0, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT);
	SDL_RenderDrawLine(refFigure.GetWindow().GetRenderer(), SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 11 / 24, SCREEN_WIDTH, SCREEN_HEIGHT * 11 / 24);
	SDL_Rect nextFigure{ ((SCREEN_WIDTH * 2 / 3) + ((SCREEN_WIDTH / 3) / 5)), (SCREEN_HEIGHT / 4), (SCREEN_HEIGHT / 6), (SCREEN_HEIGHT / 6) };
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 25, 25, 25, 255);
	SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &nextFigure);
	SDL_Color textColor = { 255, 255, 255 };
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 48);
	SDL_Rect menuRect{ SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12,  SCREEN_WIDTH / 2, 100 };
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"Tetris"), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &menuRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 24);


	SDL_Rect buttonS{ SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2,  SCREEN_WIDTH / 3, 70 };
	SDL_Rect buttonE = buttonS;
	buttonE.y += 100;
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &buttonS);
	SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &buttonE);

	textColor = { 0, 0, 0 };
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 36);
	menuRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2,  SCREEN_WIDTH / 3, 70 };
	textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"Старт"), textColor);
	textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &menuRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	menuRect.y += 100;
	textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"Выход"), textColor);
	textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &menuRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 24);
	SDL_RenderPresent(refFigure.GetWindow().GetRenderer());
}

int RenderManager::CreateStartMenu() {
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

void RenderManager::RanderGameFieldBorder() const {
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 255, 255, 255, 255);
	SDL_Rect frame{ 0, 0, (SCREEN_WIDTH * 2 / 3 - COLUMNS * PIXEL_SIZE) / 2, SCREEN_HEIGHT };
	SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &frame);
	frame = { (SCREEN_WIDTH * 2 / 3 - COLUMNS * PIXEL_SIZE) / 2 + COLUMNS * PIXEL_SIZE, 0, (SCREEN_WIDTH * 2 / 3 - COLUMNS * PIXEL_SIZE) / 2, SCREEN_HEIGHT };
	SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &frame);
	frame = { 0, SCREEN_HEIGHT - 5, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT };
	SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &frame);
}

void RenderManager::CreatePause() {
	SDL_Rect pauseRect{ SCREEN_WIDTH / 6 , SCREEN_HEIGHT / 3, (SCREEN_WIDTH / 3) , SCREEN_HEIGHT / 6 };
	SDL_Color textColor = { 255, 255, 255 };
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 48);
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"Pause"), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &pauseRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 24);
	SDL_RenderPresent(refFigure.GetWindow().GetRenderer());
}

int RenderManager::RanderPauseMenu() {
	CreatePause();
	SDL_Log("Pause");
	while(true) {
		if(SDL_PollEvent(&refFigure.GetWindow().GetEventRef()) != 0) {
			if(refFigure.GetWindow().GetEvent().type == SDL_KEYDOWN && refFigure.GetWindow().GetEvent().key.keysym.sym == SDLK_ESCAPE && refFigure.GetWindow().GetEvent().key.repeat == 0) {
				SDL_Log("Unpause");
				return 0;
			}
		}
		if(refFigure.GetWindow().GetEvent().type == SDL_QUIT) {
			SDL_Log("Quit");
			return 1;
		}
		SDL_Delay(10);
	}
}

void RenderManager::RanderNextFigure(int figure) {
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 255, 255, 255, 255);
	SDL_Rect rect{ (SCREEN_WIDTH * 2 / 3) + ((SCREEN_WIDTH / 3) / 5), SCREEN_HEIGHT / 4, (SCREEN_WIDTH / 3) - 10, SCREEN_HEIGHT / 6 };
	switch(figure) {
	case line:
		for(int i = 0; i < 4; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 16 + i * 16, SCREEN_HEIGHT / 3 - 8 , 16, 16 };
			SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		}
		break;
	case square:
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++) {
				rect = { (SCREEN_WIDTH * 11 / 15) + 32 + i * 16, SCREEN_HEIGHT / 3 - 16 + j * 16, 16, 16 };
				SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
			}
		}
		break;
	case triangle:
		for(int i = 0; i < 3; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 24 + i * 16, SCREEN_HEIGHT / 3, 16, 16 };
			SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		}
		rect = { (SCREEN_WIDTH * 11 / 15) + 24 + 16, SCREEN_HEIGHT / 3 - 16, 16, 16 };
		SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		break;
	case zigzag:
		for(int i = 0; i < 2; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 24 + i * 16, SCREEN_HEIGHT / 3 - 16, 16, 16 };
			SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		}
		for(int i = 0; i < 2; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 40 + i * 16, SCREEN_HEIGHT / 3, 16, 16 };
			SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		}
		break;
	case zigzag2:
		for(int i = 0; i < 2; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 40 + i * 16, SCREEN_HEIGHT / 3 - 16, 16, 16 };
			SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		}
		for(int i = 0; i < 2; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 24 + i * 16, SCREEN_HEIGHT / 3, 16, 16 };
			SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		}
		break;
	case letterL:
		for(int i = 0; i < 3; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 32, SCREEN_HEIGHT / 3 - 24 + i * 16, 16, 16 };
			SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		}
		rect = { (SCREEN_WIDTH * 11 / 15) + 16 + 32, SCREEN_HEIGHT / 3 + 8, 16, 16 };
		SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		break;
	case letterL2:
		for(int i = 0; i < 3; i++) {
			rect = { (SCREEN_WIDTH * 11 / 15) + 32+16, SCREEN_HEIGHT / 3 - 24 + i * 16, 16, 16 };
			SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		}
		rect = { (SCREEN_WIDTH * 11 / 15) + 32, SCREEN_HEIGHT / 3 +8, 16, 16 };
		SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &rect);
		break;
	default:
		break;
	}
}

void RenderManager::RanderInscriptions() {
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 30);
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Rect textRect{ SCREEN_WIDTH * 2 / 3 + 10, 10, 80, 40 };
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"Счёт: "), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	textRect.y = SCREEN_HEIGHT / 6 + 15;
	textRect.w = SCREEN_WIDTH / 3 - 15;
	textRect.h = 30;
	textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"След.фигура"), textColor);
	textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	textRect.y = SCREEN_HEIGHT / 2 - 30;
	textRect.h = 130;
	textSurface = TTF_RenderUNICODE_Blended_Wrapped(refFigure.GetWindow().GetFont(), (Uint16*)(L"Для паузы нажмите         Esc"), textColor, textRect.w + 10);
	textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	textRect.y += 250;
	textRect.h = 80;
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 16);
	textSurface = TTF_RenderUNICODE_Blended_Wrapped(refFigure.GetWindow().GetFont(), (Uint16*)(L"Для управления  Используйте стрелочки"), textColor, textRect.w);
	textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void RenderManager::RanderScoreCount(int score) {
	SDL_Color textColor = { 255, 255, 255 };
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 24);
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(std::to_wstring(score).c_str()), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_Rect textRect{ SCREEN_WIDTH * 2 / 3 + 80, 20, textSurface->w, textSurface->h };
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void RenderManager::RanderGameFieldGameOver() {
	SDL_Color textColor = { 255, 255, 255 };
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 48);
	SDL_Rect menuRect{ SCREEN_WIDTH / 12, SCREEN_HEIGHT / 12,  SCREEN_WIDTH / 2, 100 };
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"GAME"), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &menuRect);
	menuRect.y += 110;
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"OVER"), textColor);
	textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &menuRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	SDL_Rect buttonE{ SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 100,  SCREEN_WIDTH / 3, 70 };
	SDL_SetRenderDrawColor(refFigure.GetWindow().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderFillRect(refFigure.GetWindow().GetRenderer(), &buttonE);

	textColor = { 0, 0, 0 };
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 36);
	menuRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2 + 100,  SCREEN_WIDTH / 3, 70 };
	textSurface = TTF_RenderUNICODE_Blended(refFigure.GetWindow().GetFont(), (Uint16*)(L"Выход"), textColor);
	textTexture = SDL_CreateTextureFromSurface(refFigure.GetWindow().GetRenderer(), textSurface);
	SDL_RenderCopy(refFigure.GetWindow().GetRenderer(), textTexture, NULL, &menuRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_SetFontSize(refFigure.GetWindow().GetFont(), 24);
}