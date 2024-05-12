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
  int tempField[HEIGHT][WIDTH];
  memcpy(tempField, field, sizeof(tempField));  // лол так можно оказывается
  int res = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      getRotatedCoordinates(figure, i, j, &ii, &jj);
      // if (ii < 0 || ii >= HEIGHT) continue;
      if (ii < 0 || jj < 0 || ii >= HEIGHT || jj >= WIDTH) {  // if OOB
        if (figure.fig[i][j]) {                               // if figure
          if (ii < 0) {
            res = 1;  // OOB top
          } else if (ii >= HEIGHT) {
            res = 2;  // OOB bottom
          } else if (jj < 0) {
            res = 3;  // OOB left
          } else if (jj >= WIDTH) {
            res = 4;  // OOB right
          }
          break;
        }

        continue;
        // надо допилить чтоб при повороте смещалось вбок вместо
        // отказа
      }
      if (figure.fig[i][j] && field[ii][jj]) {
        res = 5;  // we smashed into another figure
        break;  // разобраться при повороте где сначала eer 3 потом 5
      }

      if (figure.fig[i][j])
        tempField[ii][jj] = figure.fig[i][j];  // если все ок то рисуем
    }
    if (res) break;
  }
  if (!res) memcpy(fieldToPrint, tempField, sizeof(tempField));

  return res;
}

void updateCurrentFigure(figure_t* currentFigure, int figList[7][2][4]) {
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++) {
      currentFigure->fig[i ? 0 : 3][j] = 0;
      currentFigure->fig[i + 1][j] = figList[currentFigure->figID][i][j];
    }
}

int handleKeyPress(figure_t* currentFigure, int field[HEIGHT][WIDTH]) {
  int ch, err, stop;
  int tempField[HEIGHT][WIDTH] = {0};

  while ((ch = getch()) != ERR) {
    stop = err = 0;
    switch (ch) {
      case KEY_UP:
        currentFigure->rotation += 1;
        while (!stop && (err = drawFig(*currentFigure, field, tempField))) {
          if (err == 5) {
            stop = 1;
            currentFigure->rotation -= 1;
          } else if (err == 1) {
            currentFigure->y += 1;
          } else if (err == 3) {
            currentFigure->x += 1;
          } else if (err == 4) {
            currentFigure->x -= 1;
          } else {
            stop = 1;
            currentFigure->rotation -= 1;
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

      case ' ':
        pause();
        break;
      case 27:
        err = 6;
        break;
    }
    flushinp();
  }
  return err;
}

int spawnNewFigure(int field[HEIGHT][WIDTH], int fieldToPrint[HEIGHT][WIDTH],
                   int figList[7][2][4], struct Figure* currentFigure,
                   int* nextFigureID) {
  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++) field[i][j] = fieldToPrint[i][j];
  currentFigure->rotation = 0;
  currentFigure->y = -1;
  currentFigure->x = 3;
  currentFigure->figID = *nextFigureID;

  int tempField[HEIGHT][WIDTH] = {0};
  int res = 0;
  updateCurrentFigure(currentFigure, figList);
  *nextFigureID = rand() % 7;
  if (drawFig(*currentFigure, field, tempField)) res = 1;
  return res;
}

void printField(int field[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) printf("%d", field[i][j]);
    printf("\n");
  }
}

int isRowFull(int field[HEIGHT][WIDTH], int row) {
  if (row < 0) return 0;
  int isFull = 1;
  for (int j = 0; j < WIDTH; j++) {
    isFull &= (field[row][j] != 0);
  }
  return isFull;
}

int myPow(int base, int exponent) {
  int result = 1;
  for (int i = 0; i < exponent; i++) result *= base;
  return result;
}

int clearRows(int field[HEIGHT][WIDTH], int rows[HEIGHT], int* score) {
  int numRowsCleared = 0;
  for (int i = HEIGHT - 1; i >= 0; i--) {
    if (rows[i]) {
      for (int j = i; j > 0; j--) {
        memcpy(field[j], field[j - 1], sizeof(field[j]));
      }
      // memset(field[0], 0, sizeof(field[0]));
      numRowsCleared++;
    }
  }
  *score += (myPow(2, numRowsCleared) - 1) * 100;
  return numRowsCleared;
}

void updateLevelAndSpeed(int* level, int* speed, int* score,
                         int field[HEIGHT][WIDTH]) {
  int rows[HEIGHT];
  for (int i = 0; i < HEIGHT; i++) rows[i] = isRowFull(field, i);
  if (clearRows(field, rows, score)) {
    *level = *score / 600 + 1;
    *speed = 16 - *level <= 10 ? *level : 10;
  }
}

int updateFigure(figure_t* currentFigure, int field[HEIGHT][WIDTH],
                 int fieldToPrint[HEIGHT][WIDTH], int figList[7][2][4],
                 int* nextFigureID) {
  int tempField[HEIGHT][WIDTH] = {0};
  int res = 0;
  currentFigure->y += 1;
  if (drawFig(*currentFigure, field, tempField)) {
    currentFigure->y -= 1;
    spawnNewFigure(field, fieldToPrint, figList, currentFigure, nextFigureID);
  }
  if (drawFig(*currentFigure, field, tempField)) res = 1;
  return res;
}

int getMaxScore() {
  FILE* file = fopen("maxScore.txt", "a+");
  fseek(file, 0, SEEK_END);  // Seek to the end of the file
  if (ftell(file) == 0) {    // If the position is 0, the file is empty
    fprintf(file, "0");      // Write "0" to the file
  }
  fseek(file, 0, SEEK_SET);
  int maxScore;
  fscanf(file, "%d", &maxScore);
  fclose(file);
  return maxScore;
}

void newRecord(int score, int maxScore) {
  if (score > maxScore) {
    FILE* file = fopen("maxScore.txt", "a+");

    fprintf(file, "%d", score);
    fclose(file);
  }
}

int main() {
  srand(time(NULL));
  struct Figure currentFigure;
  int score = 0, level = 1, gameState = 0, time = 1, collision = 1, speed = 15;
  int maxScore = getMaxScore();
  int nextFigureID = rand() % 7;
  int notFalse = 1, rows[HEIGHT];
  int field[HEIGHT][WIDTH] = {0}, fieldToPrint[HEIGHT][WIDTH] = {0};
  int figList[7][2][4] = {
      {{4, 4, 4, 4}, {0, 0, 0, 0}},  // I
      {{0, 2, 0, 0}, {0, 2, 2, 2}},  // J
      {{0, 0, 3, 0}, {3, 3, 3, 0}},  // L
      {{0, 7, 7, 0}, {0, 7, 7, 0}},  // O
      {{0, 0, 5, 5}, {0, 5, 5, 0}},  // S
      {{0, 0, 6, 0}, {0, 6, 6, 6}},  // T
      {{0, 2, 2, 0}, {0, 0, 2, 2}}   // Z
  };

  init();
  startScreen();
  spawnNewFigure(field, fieldToPrint, figList, &currentFigure, &nextFigureID);

  while (notFalse) {
    if (handleKeyPress(&currentFigure, field) == 6) break;
    drawFig(currentFigure, field, fieldToPrint);  // fieldToPrint += figure
    drawField(fieldToPrint, score, maxScore, level, nextFigureID, figList);

    if (time % speed == 0) {
      if (updateFigure(&currentFigure, field, fieldToPrint, figList,
                       &nextFigureID))
        break;
      updateLevelAndSpeed(&level, &speed, &score, field);
    }
    time += 1;

    napms(WAIT_TIME);
  }

  if (score > maxScore) {
    FILE* file = fopen("maxScore.txt", "w");
    fprintf(file, "%d", score);
    fclose(file);
  }

  newRecord(score, maxScore);
  gg(score, maxScore);
  endwin();
  return 0;
}

/*
  Че можно сделать но не обязательно
  при arrowDown скипается время крч ты понял
  хендлить поворот корректнеее, но эт заеб

*/