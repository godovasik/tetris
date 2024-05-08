#include "tetris.h"

int drawFig(int figId, figure_t figure, int* fieldToPrint[HEIGHT][WIDTH]) {
  int* p = NULL;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (figure.rotation == 0)
        p = &((*fieldToPrint)[i + figure.y][j + figure.x]);
      else if (figure.rotation == 1)
        p = &((*fieldToPrint)[j + figure.y][3 - i + figure.x]);
      else if (figure.rotation == 2)
        p = &((*fieldToPrint)[3 - i + figure.y][3 - j + figure.x]);
      else if (figure.rotation == 3)
        p = &((*fieldToPrint)[3 - j + figure.y][i + figure.x]);
      if (figure.fig[i][j] && *p) return 1;  // занято нахуй
    }
  return 0;  // success
}

int main() {
  struct Figure currentFigure = {
      0, {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 0, 3, 0};
  int score = 0, level = 1, gameState = 0, time = 0, collision = 1;
  int nextFigureID = rand() % 7;
  int field[HEIGHT][WIDTH] = {0};
  int fieldToPrint[HEIGHT][WIDTH] = {0};
  int figList[7][2][4] = {
      {{4, 4, 4, 4}, {0, 0, 0, 0}},  // I
      {{0, 2, 0, 0}, {0, 2, 2, 2}},  // J
      {{0, 0, 3, 0}, {3, 3, 3, 0}},  // L
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

      for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++) {
          currentFigure.fig[i ? 0 : 3][j] = 0;  // кастыыыыль
          currentFigure.fig[i + 1][j] = figList[currentFigure.figID][i][j];
        }
      nextFigureID = rand() % 7;
    }

    position napms(200);
  }
}
