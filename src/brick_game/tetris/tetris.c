#include "tetris.h"

void getRotatedCoordinates(figure_t figure, int i, int j, int* ii, int* jj) {
  switch (figure.rotation % 4) {
    case 0:
      *ii = i + figure.y;
      *jj = j + figure.x;
      break;
    case 1:
      *ii = j + figure.y;
      *jj = 3 - i + figure.x;
      break;
    case 2:
      *ii = 3 - i + figure.y;
      *jj = 3 - j + figure.x;
      break;
    case 3:
      *ii = 3 - j + figure.y;
      *jj = i + figure.x;
      break;
  }
}

int drawFig(figure_t figure, int field[HEIGHT][WIDTH],
            int fieldToPrint[HEIGHT][WIDTH]) {
  int currentCell = 0, ii = 0, jj = 0;
  int tempField[HEIGHT][WIDTH] = {0};
  int res = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      getRotatedCoordinates(figure, i, j, &ii, &jj);
      if (field[ii][jj]) {
        res = 5;  // we smashed into another figure
        break;
      }
      if (ii < 0 || jj < 0 || ii > HEIGHT || jj >= WIDTH) {
        if (figure.fig[i][j]) {
          if (ii < 0) {
            res = 1;  // OOB top
            break;
          } else if (ii > HEIGHT) {
            res = 2;  // OOB bottom
            break;
          } else if (jj < 0) {
            res = 3;  // OOB left
            break;
          } else if (jj >= WIDTH) {
            res = 4;  // OOB right
            break;
          }
        }
        continue;
        // надо допилить чтоб при повороте смещалось вбок вместо
        // отказа
      }

      tempField[ii][jj] = figure.fig[i][j];  // если все ок то рисуем
    }
    if (res) break;
  }
  if (!res)
    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH; j++) {
        fieldToPrint[i][j] = tempField[i][j];
      }
    }
  return res;
}

void updateCurrentFigure(figure_t* currentFigure, int figList[7][2][4]) {
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) {
      currentFigure->fig[i ? 0 : 3][j] = 0;
      currentFigure->fig[i + 1][j] = figList[currentFigure->figID][i][j];
    }
}

void handleKeyPress(figure_t* currentFigure, int field[HEIGHT][WIDTH]) {
  int ch, err, stop;
  int tempField[HEIGHT][WIDTH] = {0};

  while ((ch = getch()) != ERR) {
    stop = err = 0;
    switch (ch) {
      case KEY_UP:
        currentFigure->rotation += 1;
        while (!stop && (err = drawFig(*currentFigure, field, tempField))) {
          switch (err) {
            case 5:
              stop = 1;
              currentFigure->rotation -= 1;
              break;
            case 1:
              currentFigure->x += 1;
              break;
            case 3:
              currentFigure->y += 1;
              break;
            case 4:
              currentFigure->y -= 1;
              break;
            default:
              stop = 1;
              currentFigure->rotation -= 1;
              break;
          }
        }
        break;

      case KEY_DOWN:
        currentFigure->y += 1;  // nado brake na ves' cycle delat'
        if (err = drawFig(*currentFigure, field, tempField))
          currentFigure->y -= 1;
        break;

      case KEY_LEFT:
        currentFigure->x -= 1;
        if (err = drawFig(*currentFigure, field, tempField))
          currentFigure->x += 1;
        break;

      case KEY_RIGHT:
        currentFigure->x += 1;
        if (err = drawFig(*currentFigure, field, tempField))
          currentFigure->x -= 1;
        break;
    }
    flushinp();
  }
}

void printField(int field[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) printf("%d", field[i][j]);
    printf("\n");
  }
}

int main() {
  srand(time(NULL));
  struct Figure currentFigure = {
      0, {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 0, 3, 0};
  int score = 0, level = 1, gameState = 0, time = 1, collision = 1, speed = 20;
  int nextFigureID = rand() % 7;
  int ch;
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

  init();

  while (true) {
    handleKeyPress(&currentFigure, field);

    if (collision) {
      for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) field[i][j] = fieldToPrint[i][j];

      collision = currentFigure.rotation = 0;
      currentFigure.y = -1;
      currentFigure.figID = nextFigureID;

      updateCurrentFigure(&currentFigure, figList);
      nextFigureID = rand() % 7;
    }
    drawFig(currentFigure, field, fieldToPrint);

    drawField(fieldToPrint, score, level, nextFigureID, figList);
    // printf("\033[H\033[J");
    // printField(fieldToPrint);
    if (time % speed == 0) currentFigure.y += 1;

    time += 1;

    napms(WAIT_TIME);
  }
  endwin();
  return 0;
}
