#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../gui/cli/gui.h"

#define WAIT_TIME 50

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

typedef struct Figure {
  int figID;
  int fig[4][4];
  int y, x;
  int rotation;
} figure_t;
