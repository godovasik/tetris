#include "tetris.h"

int drawFig(int figId, figure_t figure, int* fieldToPrint[HEIGHT][WIDTH]) {
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) {
      if (figure.rotation == 0)
        (*fieldToPrint)[i + figure.y][j + figure.x] = figure.fig[i][j];
      else if (figure.rotation == 1)
        (*fieldToPrint)[i + figure.y][j + figure.x] = figure.fig[i][j];
      else if (figure.rotation == 1)
        (*fieldToPrint)[i + figure.y][j + figure.x] = figure.fig[i][j];
      else if (figure.rotation == 1)
        (*fieldToPrint)[i + figure.y][j + figure.x] = figure.fig[i][j];
    }
}

int main() {
  struct Figure currentFigure = {0, {{0, 0, 0, 0}, {0, 0, 0, 0}}, 0, 3, 0};
  int score = 0, level = 1, gameState = 0, time = 0, collision = 1;
  int nextFigureID = rand() % 7;
  int field[HEIGHT][WIDTH] = {0};
  int fieldToPrint[HEIGHT][WIDTH] = {0};
  int figList[7][2][4] = {
      {{4, 4, 4, 4}, {0, 0, 0, 0}},  // I
      {{0, 2, 0, 0}, {0, 2, 2, 2}},  // J
      {{0, 0, 0, 3}, {0, 3, 3, 3}},  // L
      {{0, 7, 7, 0}, {0, 7, 7, 0}},  // O
      {{0, 5, 5, 0}, {0, 0, 5, 5}},  // S
      {{0, 0, 6, 0}, {0, 6, 6, 6}},  // T
      {{0, 2, 2, 0}, {0, 0, 2, 2}}   // Z
  };
  while (true) {
    if (collision) {
      for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) field[i][j] = fieldToPrint[i][j];

      currentFigure.y = collision = currentFigure.rotation = 0;
      currentFigure.figID = nextFigureID;
      nextFigureID = rand() % 7;
    }

    position napms(200);
  }
}
