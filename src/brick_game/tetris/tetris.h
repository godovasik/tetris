#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../gui/cli/gui.h"

#define WAIT_TIME 50

typedef struct Figure {
  int figID;
  int fig[4][4];
  int y, x;
  int rotation;
} figure_t;
