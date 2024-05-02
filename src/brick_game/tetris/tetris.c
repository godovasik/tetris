#include "tetris.h"

int spawnFig(int figure[2][4], int* field[HEIGHT][WIDTH]) {
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++)
      if (figure[i][j]) (*field)[i + 1][j + 4] = 2;
}

int startGame() {
  int score = 0, level = 1;
  int figList[7][2][4] = {
      {{0, 0, 0, 0}, {1, 1, 1, 1}},  // I
      {{0, 1, 0, 0}, {0, 1, 1, 1}},  // J
      {{0, 0, 0, 1}, {0, 1, 1, 1}},  // L
      {{0, 0, 1, 0}, {0, 1, 1, 0}},  // O
      {{0, 1, 1, 0}, {1, 0, 1, 1}},  // S
      {{0, 0, 1, 0}, {0, 1, 1, 1}},  // T
      {{0, 1, 1, 0}, {0, 0, 1, 1}}   // Z
  };
  int field[HEIGHT][WIDTH] = {0};
  int gameState = 0;  // 0 - not falling, 1 - figure is falling,
  int currentFigId = 0;
  int nextFigId = rand() % 7;

  while (true) {
    if (gameState = 0) {
      spawnFig(figList[nextFigId], &field);
      currentFigId = nextFigId;
      nextFigId = rand() % 7;
      gameState = 1;
        }
  }
}
