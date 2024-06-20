#include "FigureManager.h"

Figure::Figure(int color, int type) {
	this->color = color;
	this->type = type;
	switch(type) {
	case line:
		for(int k = 0; k < 4; k++) {
			for(int i = 0; i < BLOCK_SIZE; i++) {
				for(int j = 0; j < BLOCK_SIZE; j++) {
					GameFild[(COLUMNS / 2) - (BLOCK_SIZE) * 2 + (i)+(k)*BLOCK_SIZE][(j)].color = color;
					GameFild[(COLUMNS / 2) - (BLOCK_SIZE) * 2 + (i)+(k)*BLOCK_SIZE][(j)].isStruct = dFigure;
				}
			}
		}
		this->prevX = (COLUMNS / 2) - (BLOCK_SIZE) * 2;
		this->prevY = 28;
		break;
	case square:
		for(int l = 0; l < 2; l++) {
			for(int k = 0; k < 2; k++) {
				for(int i = 0; i < 8; i++) {
					for(int j = 0; j < 8; j++) {
						GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].color = color;
						GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].isStruct = dFigure;
					}
				}
			}
		}
		this->prevX = (COLUMNS / 2) - BLOCK_SIZE;
		this->prevY = 20;
		break;
	case triangle:
		for(int l = 0; l < 2; l++) {
			for(int k = 0; k < 3; k++) {
				for(int i = 0; i < 8; i++) {
					for(int j = 0; j < 8; j++) {
						if(!((k == 0 && l == 0) || (k == 2 && l == 0))) {
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].color = color;
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].isStruct = dFigure;
						}
					}
				}
			}
		}
		this->prevX = (COLUMNS / 2) - BLOCK_SIZE;
		this->prevY = 20;
		break;
	case zigzag:
		for(int l = 0; l < 2; l++) {
			for(int k = 0; k < 3; k++) {
				for(int i = 0; i < 8; i++) {
					for(int j = 0; j < 8; j++) {
						if(!((k == 0 && l == 1) || (k == 2 && l == 0))) {
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].color = color;
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].isStruct = dFigure;
						}
					}
				}
			}
		}
		this->prevX = (COLUMNS / 2) - BLOCK_SIZE;
		this->prevY = 20;
		break;
	case zigzag2:
		for(int l = 0; l < 2; l++) {
			for(int k = 0; k < 3; k++) {
				for(int i = 0; i < 8; i++) {
					for(int j = 0; j < 8; j++) {
						if(!((k == 0 && l == 0) || (k == 2 && l == 1))) {
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].color = color;
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].isStruct = dFigure;
						}
					}
				}
			}
		}
		this->prevX = (COLUMNS / 2) - BLOCK_SIZE;
		this->prevY = 20;
		break;
	case letterL:
		for(int l = 0; l < 3; l++) {
			for(int k = 0; k < 2; k++) {
				for(int i = 0; i < 8; i++) {
					for(int j = 0; j < 8; j++) {
						if(!((k == 1 && l == 0) || (k == 1 && l == 1))) {
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].color = color;
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].isStruct = dFigure;
						}
					}
				}
			}
		}
		this->prevX = (COLUMNS / 2) - BLOCK_SIZE;
		this->prevY = 12;
		break;
	case letterL2:
		for(int l = 0; l < 3; l++) {
			for(int k = 0; k < 2; k++) {
				for(int i = 0; i < 8; i++) {
					for(int j = 0; j < 8; j++) {
						if(!((k == 0 && l == 0) || (k == 0 && l == 1))) {
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].color = color;
							GameFild[(COLUMNS / 2) - BLOCK_SIZE + (i)+(k)*BLOCK_SIZE][(j)+(l)*BLOCK_SIZE].isStruct = dFigure;
						}
					}
				}
			}
		}
		this->prevX = (COLUMNS / 2) - BLOCK_SIZE;
		this->prevY = 12;
		break;
	default:
		SDL_Log("Error: Unknown type of figure");
		prevX = 0;
		prevY = 0;
		break;
	}
	this->rotation = 0;
}

bool Figure::MoveFigure(int x, int y) {
	int currentX = this->prevX + x;
	int currentY = this->prevY + y;
	bool success = false;
	bool canMove = true;
	switch(type) {
	case line:
		if(rotation == 0) {
			if(currentX + 4 * 8 <= COLUMNS && currentY + 8 <= ROWS && currentX >= 0 && currentY >= 0) {
				for(int k = 0; k < 4; k++) {
					for(int i = 0; i < BLOCK_SIZE; i++) {
						for(int j = 0; j < BLOCK_SIZE; j++) {
							if(GameFild[currentX + i + (k)*BLOCK_SIZE][(currentY)+j].color != 0 && GameFild[\
								(currentX)+i + (k)*BLOCK_SIZE][(currentY)+j].isStruct == dSand) {
								success = false;
								canMove = false;
							}
						}
					}
				}
				if(canMove) {
					for(int k = 0; k < 4; k++) {
						for(int i = 0; i < BLOCK_SIZE; i++) {
							for(int j = 0; j < BLOCK_SIZE; j++) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)].isStruct = dField;
							}
						}
					}
					for(int k = 0; k < 4; k++) {
						for(int i = 0; i < BLOCK_SIZE; i++) {
							for(int j = 0; j < BLOCK_SIZE; j++) {
								GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)].color = color;
								GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)].isStruct = dFigure;
							}
						}
					}
					success = true;
				}
			}
		}
		else if(rotation == 1) {
			if(currentX + 8 <= COLUMNS && currentY + 4 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
				for(int k = 0; k < 4; k++) {
					for(int i = 0; i < BLOCK_SIZE; i++) {
						for(int j = 0; j < BLOCK_SIZE; j++) {
							if(GameFild[currentX + (i)][currentY + (j)+(k)*BLOCK_SIZE].isStruct == dSand) {
								success = false;
								canMove = false;
							}
						}
					}
				}
				if(canMove) {
					for(int k = 0; k < 4; k++) {
						for(int i = 0; i < BLOCK_SIZE; i++) {
							for(int j = 0; j < BLOCK_SIZE; j++) {
								GameFild[prevX + (i)][prevY + (j)+(k)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)][prevY + (j)+(k)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
					for(int k = 0; k < 4; k++) {
						for(int i = 0; i < BLOCK_SIZE; i++) {
							for(int j = 0; j < BLOCK_SIZE; j++) {
								GameFild[currentX + (i)][currentY + (j)+(k)*BLOCK_SIZE].color = color;
								GameFild[currentX + (i)][currentY + (j)+(k)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
					success = true;
				}
			}
		}
		break;
	case square:
		if(currentX + 2 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct == dSand) {
								success = false;
								canMove = false;
							}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + i + k * BLOCK_SIZE][prevY + j + l * BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
				success = true;
			}
		}
		break;
	case triangle:
		if(rotation == 0) {
			if(currentX + 3 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 2 && l == 0)))
									if(GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct == dSand) {
										success = false;
										canMove = false;
									}
							}
						}
					}
				}
				if(canMove) {
					for(int l = 0; l < 2; l++) {
						for(int k = 0; k < 3; k++) {
							for(int i = 0; i < 8; i++) {
								for(int j = 0; j < 8; j++) {
									if(!((k == 0 && l == 0) || (k == 2 && l == 0))) {
										GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
										GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
									}
								}
							}
						}
					}
					for(int l = 0; l < 2; l++) {
						for(int k = 0; k < 3; k++) {
							for(int i = 0; i < 8; i++) {
								for(int j = 0; j < 8; j++) {
									if(!((k == 0 && l == 0) || (k == 2 && l == 0))) {
										GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
										GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
									}
								}
							}
						}
					}
					success = true;
				}
			}
		}
		else if(rotation == 1) {
			if(currentX + 2 * 8 <= COLUMNS && currentY + 3 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 0) || (k == 1 && l == 2)))
									if(GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct == dSand) {
										success = false;
										canMove = false;
									}
							}
						}
					}
				}
				if(canMove) {
					for(int l = 0; l < 3; l++) {
						for(int k = 0; k < 2; k++) {
							for(int i = 0; i < 8; i++) {
								for(int j = 0; j < 8; j++) {
									if(!((k == 1 && l == 0) || (k == 1 && l == 2))) {
										GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
										GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
									}
								}
							}
						}
					}
					for(int l = 0; l < 3; l++) {
						for(int k = 0; k < 2; k++) {
							for(int i = 0; i < 8; i++) {
								for(int j = 0; j < 8; j++) {
									if(!((k == 1 && l == 0) || (k == 1 && l == 2))) {
										GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
										GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
									}
								}
							}
						}
					}
					success = true;
				}
			}
		}
		else if(rotation == 2) {
			if(currentX + 3 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 1) || (k == 2 && l == 1)))
									if(GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct == dSand) {
										success = false;
										canMove = false;
									}
							}
						}
					}
				}
				if(canMove) {
					for(int l = 0; l < 2; l++) {
						for(int k = 0; k < 3; k++) {
							for(int i = 0; i < 8; i++) {
								for(int j = 0; j < 8; j++) {
									if(!((k == 0 && l == 1) || (k == 2 && l == 1))) {
										GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
										GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
									}
								}
							}
						}
					}
					for(int l = 0; l < 2; l++) {
						for(int k = 0; k < 3; k++) {
							for(int i = 0; i < 8; i++) {
								for(int j = 0; j < 8; j++) {
									if(!((k == 0 && l == 1) || (k == 2 && l == 1))) {
										GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
										GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
									}
								}
							}
						}
					}
					success = true;
				}
			}
		}
		else if(rotation == 3) {
			if(currentX + 2 * 8 <= COLUMNS && currentY + 3 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 0 && l == 2)))
									if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
										success = false;
										canMove = false;
									}
							}
						}
					}
				}
				if(canMove) {
					for(int l = 0; l < 3; l++) {
						for(int k = 0; k < 2; k++) {
							for(int i = 0; i < 8; i++) {
								for(int j = 0; j < 8; j++) {
									if(!((k == 0 && l == 0) || (k == 0 && l == 2))) {
										GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
										GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
									}
								}
							}
						}
					}
					for(int l = 0; l < 3; l++) {
						for(int k = 0; k < 2; k++) {
							for(int i = 0; i < 8; i++) {
								for(int j = 0; j < 8; j++) {
									if(!((k == 0 && l == 0) || (k == 0 && l == 2))) {
										GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
										GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
									}
								}
							}
						}
					}
					success = true;
				}
			}
		}
		break;
	case zigzag:
		if(rotation == 0 && currentX + 3 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 2 && l == 0)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 1) || (k == 2 && l == 0))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 1) || (k == 2 && l == 0))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		else if(rotation == 1 && currentX + 2 * 8 <= COLUMNS && currentY + 3 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 1 && l == 2)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 1 && l == 2))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 1 && l == 2))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		break;
	case zigzag2:
		if(rotation == 0 && currentX + 3 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 2 && l == 1)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 2 && l == 1))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 2 && l == 1))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		else if(rotation == 1 && currentX + 2 * 8 <= COLUMNS && currentY + 3 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 0 && l == 2)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 0) || (k == 0 && l == 2))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 0) || (k == 0 && l == 2))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		break;
	case letterL:
		if(rotation == 0 && currentX + 2 * 8 <= COLUMNS && currentY + 3 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 1 && l == 1)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 0) || (k == 1 && l == 1))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 0) || (k == 1 && l == 1))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		else if(rotation == 1 && currentX + 3 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 1 && l == 0)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 1 && l == 0))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 1 && l == 0))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		else if(rotation == 2 && currentX + 2 * 8 <= COLUMNS && currentY + 3 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 0 && l == 2)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 1) || (k == 0 && l == 2))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 1) || (k == 0 && l == 2))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		else if(rotation == 3 && currentX + 3 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 1) || (k == 2 && l == 1)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 1) || (k == 2 && l == 1))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 1) || (k == 2 && l == 1))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		break;
	case letterL2:
		if(rotation == 0 && currentX + 2 * 8 <= COLUMNS && currentY + 3 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 0 && l == 1)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 0 && l == 1))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 0) || (k == 0 && l == 1))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		else if(rotation == 1 && currentX + 3 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 2 && l == 0)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 0) || (k == 2 && l == 0))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 0) || (k == 2 && l == 0))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		else if(rotation == 2 && currentX + 2 * 8 <= COLUMNS && currentY + 3 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 1) || (k == 1 && l == 2)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 1) || (k == 1 && l == 2))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 3; l++) {
					for(int k = 0; k < 2; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 1 && l == 1) || (k == 1 && l == 2))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		else if(rotation == 3 && currentX + 3 * 8 <= COLUMNS && currentY + 2 * 8 <= ROWS && currentX >= 0 && currentY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 1 && l == 1)))
								if(GameFild[currentX + i + k * BLOCK_SIZE][currentY + j + l * BLOCK_SIZE].isStruct == dSand) {
									success = false;
									canMove = false;
								}
						}
					}
				}
			}
			if(canMove) {
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 1) || (k == 1 && l == 1))) {
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
									GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
								}
							}
						}
					}
				}
				for(int l = 0; l < 2; l++) {
					for(int k = 0; k < 3; k++) {
						for(int i = 0; i < 8; i++) {
							for(int j = 0; j < 8; j++) {
								if(!((k == 0 && l == 1) || (k == 1 && l == 1))) {
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].color = color;
									GameFild[currentX + (i)+(k)*BLOCK_SIZE][currentY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
								}
							}
						}
					}
				}
				success = true;
			}
		}
		break;
	default:
		break;
	}
	if(success) {
		this->prevX = currentX;
		this->prevY = currentY;
	}
	return success;
}

void Figure::RotateFigure() {
	switch(type) {
	case line:
		if(rotation == 0 && prevX + 4 * 8 <= COLUMNS && prevY + 4 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int k = 0; k < 4; k++) {
				for(int i = 0; i < BLOCK_SIZE; i++) {
					for(int j = 0; j < BLOCK_SIZE; j++) {
						GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)].color = 0;
						GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)].isStruct = dField;
					}
				}
			}
			for(int k = 0; k < 4; k++) {
				for(int i = 0; i < BLOCK_SIZE; i++) {
					for(int j = 0; j < BLOCK_SIZE; j++) {
						GameFild[prevX + (i)][prevY + (j)+(k)*BLOCK_SIZE].color = color;
						GameFild[prevX + (i)][prevY + (j)+(k)*BLOCK_SIZE].isStruct = dFigure;
					}
				}
			}
			rotation = 1;
		}
		else if(rotation == 1 && prevX + 4 * 8 <= COLUMNS && prevY + 4 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int k = 0; k < 4; k++) {
				for(int i = 0; i < BLOCK_SIZE; i++) {
					for(int j = 0; j < BLOCK_SIZE; j++) {
						GameFild[prevX + (i)][prevY + (j)+(k)*BLOCK_SIZE].color = 0;
						GameFild[prevX + (i)][prevY + (j)+(k)*BLOCK_SIZE].isStruct = dField;
					}
				}
			}
			for(int k = 0; k < 4; k++) {
				for(int i = 0; i < BLOCK_SIZE; i++) {
					for(int j = 0; j < BLOCK_SIZE; j++) {
						GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)].color = color;
						GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)].isStruct = dFigure;
					}
				}
			}
			rotation = 0;
		}
		break;
	case square:
		//nothing
		break;
	case triangle:
		if(rotation == 0 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 1;
		}
		else if(rotation == 1 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 2;
		}
		else if(rotation == 2 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 3;
		}
		else if(rotation == 3 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 0;
		}
		break;
	case zigzag:
		if(rotation == 0 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 1;
		}
		else if(rotation == 1 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 0;
		}
		break;
	case zigzag2:
		if(rotation == 0 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 1;
		}
		else if(rotation == 1 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 0;
		}
		break;
	case letterL:
		if(rotation == 0 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 1 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 1 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 1;
		}
		else if(rotation == 1 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 1 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 2;
		}
		else if(rotation == 2 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 1) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}

			rotation = 3;
		}
		else if(rotation == 3 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 1) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 1 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 0;
		}
		break;
	case letterL2:
		if(rotation == 0 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 0 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 1;
		}
		else if(rotation == 1 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 1) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 2;
		}
		else if(rotation == 2 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 1) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 1 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 3;
		}
		else if(rotation == 3 && prevX + 3 * 8 <= COLUMNS && prevY + 3 * 8 <= ROWS && prevX >= 0 && prevY >= 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 1 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = 0;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dField;
							}
						}
					}
				}
			}
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 0 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].color = color;
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dFigure;
							}
						}
					}
				}
			}
			rotation = 0;
		}
		break;
	}
}

Figure& Figure::operator=(const Figure&& other) noexcept {
	if(this != &other) {
		this->color = other.color;
		this->type = other.type;
		this->rotation = other.rotation;
		this->prevX = other.prevX;
		this->prevY = other.prevY;
	}
	return *this;
}

void Figure::SandCreator() {
	switch(type) {
	case line:
		if(rotation == 0) {
			for(int k = 0; k < 4; k++) {
				for(int i = 0; i < BLOCK_SIZE; i++) {
					for(int j = 0; j < BLOCK_SIZE; j++) {
						GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)].isStruct = dSand;
					}
				}

			}
		}
		if(rotation == 1) {
			for(int k = 0; k < 4; k++) {
				for(int i = 0; i < BLOCK_SIZE; i++) {
					for(int j = 0; j < BLOCK_SIZE; j++) {
						GameFild[prevX + (i)][prevY + (j)+(k)*BLOCK_SIZE].isStruct = dSand;
					}
				}
			}
		}
		break;
	case square:
		for(int l = 0; l < 2; l++) {
			for(int k = 0; k < 2; k++) {
				for(int i = 0; i < 8; i++) {
					for(int j = 0; j < 8; j++) {
						GameFild[prevX + i + k * BLOCK_SIZE][prevY + j + l * BLOCK_SIZE].isStruct = dSand;
					}
				}
			}
		}
		break;
	case triangle:
		if(rotation == 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 1) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 2) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 3) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		break;
	case zigzag:
		if(rotation == 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 1) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		break;
	case zigzag2:
		if(rotation == 0) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 1) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		break;
	case letterL:
		if(rotation == 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 1 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 1) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 1 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 2) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 0 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 3) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 1) || (k == 2 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		break;
	case letterL2:
		if(rotation == 0) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 0) || (k == 0 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 1) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 0) || (k == 2 && l == 0))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 2) {
			for(int l = 0; l < 3; l++) {
				for(int k = 0; k < 2; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 1 && l == 1) || (k == 1 && l == 2))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		if(rotation == 3) {
			for(int l = 0; l < 2; l++) {
				for(int k = 0; k < 3; k++) {
					for(int i = 0; i < 8; i++) {
						for(int j = 0; j < 8; j++) {
							if(!((k == 0 && l == 1) || (k == 1 && l == 1))) {
								GameFild[prevX + (i)+(k)*BLOCK_SIZE][prevY + (j)+(l)*BLOCK_SIZE].isStruct = dSand;
							}
						}
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void Figure::SandMove() {
	for(int j = ROWS - 1; j >= 0; j--) {
		for(int i = 0; i < COLUMNS; i++) {
			if(GameFild[i][j].isStruct == dSand) {
				if(j + 1 < ROWS && i < COLUMNS && i >= 0) {
					if(GameFild[i][j + 1].isStruct == dField) {
						GameFild[i][j + 1].color = GameFild[i][j].color;
						GameFild[i][j].color = 0;
						GameFild[i][j + 1].isStruct = dSand;
						GameFild[i][j].isStruct = dField;
					}
					else {
						if(i + 1 < COLUMNS) {
							if(GameFild[i + 1][j + 1].isStruct == dField && GameFild[i + 1][j].isStruct == dField) {
								GameFild[i + 1][j].color = GameFild[i][j].color;
								GameFild[i][j].color = 0;
								GameFild[i + 1][j].isStruct = dSand;
								GameFild[i][j].isStruct = dField;
							}
						}
						if(i - 1 >= 0) {
							if(GameFild[i - 1][j + 1].isStruct == dField && GameFild[i - 1][j].isStruct == dField) {
								GameFild[i - 1][j + 1].color = GameFild[i][j].color;
								GameFild[i][j].color = 0;
								GameFild[i - 1][j + 1].isStruct = dSand;
								GameFild[i][j].isStruct = dField;
							}
						}
					}
				}
			}
		}
	}
}

void ColorChecker(std::vector<std::vector<Sand>>& array, int rowID, int colID, int color, bool& touch, std::vector<std::vector<int>>& buffer) {
	buffer[colID][rowID] = 1;
	if(colID == COLUMNS - 1)
		touch = true;
	if(rowID - 1 >= 0 && !buffer[colID][rowID - 1] && array[colID][rowID - 1].isStruct == dSand && array[colID][rowID - 1].color == color)
		ColorChecker(array, rowID - 1, colID, color, touch, buffer);
	if(colID + 1 < COLUMNS && !buffer[colID + 1][rowID] && array[colID + 1][rowID].isStruct == dSand && array[colID + 1][rowID].color == color)
		ColorChecker(array, rowID, colID + 1, color, touch, buffer);
	if(rowID + 1 < ROWS && !buffer[colID][rowID + 1] && array[colID][rowID + 1].isStruct == dSand && array[colID][rowID + 1].color == color)
		ColorChecker(array, rowID + 1, colID, color, touch, buffer);
	if(colID - 1 >= 0 && !buffer[colID - 1][rowID] && array[colID - 1][rowID].isStruct == dSand && array[colID - 1][rowID].color == color)
		ColorChecker(array, rowID, colID - 1, color, touch, buffer);
}

int Figure::LineDestroyer() {
	int count = 0;
	bool touch = false;
	for(int j = 0; j < ROWS; j++) {
		if(GameFild[0][j].isStruct == dSand) {
			ColorChecker(GameFild, j, 0, GameFild[0][j].color, touch, tempArr);
		}
		if(touch)
			break;
		for(int i = 0; i < COLUMNS; i++) {
			std::fill(tempArr[i].begin(), tempArr[i].end(), 0);
		}
	}
	if(touch)
		for(int i = 0; i < COLUMNS; i++) {
			for(int j = 0; j < ROWS; j++) {
				if(tempArr[i][j] == 1) {
					GameFild[i][j].color = 0;
					GameFild[i][j].isStruct = dField;
					count++;
				}
			}
		}
	return count;
}

bool Figure::GameoverChecker() {
	for(int i = 0; i < COLUMNS; i++) {
		if(GameFild[i][27].isStruct == dSand) {
			return true;
		}
	}
	return false;
}

void Figure::GameOverAnimation() {
	int tempColumn = rand() % COLUMNS;
	GameFild[tempColumn][0].color = rand() % 4 + 1;
	GameFild[tempColumn][0].isStruct = dSand;
	for(int i = 0; i < COLUMNS; i++) {
		GameFild[i][ROWS - 1].color = 0;
		GameFild[i][ROWS - 1].isStruct = dField;
	}
	for(int j = ROWS - 1; j >= 0; j--) {
		for(int i = 0; i < COLUMNS; i++) {
			if(GameFild[i][j].isStruct == dSand) {
				if(j + 1 < ROWS && i < COLUMNS && i >= 0) {
					if(GameFild[i][j + 1].isStruct == dField) {
						GameFild[i][j + 1].color = GameFild[i][j].color;
						GameFild[i][j].color = 0;
						GameFild[i][j + 1].isStruct = dSand;
						GameFild[i][j].isStruct = dField;
					}
				}
			}
		}
	}
}
