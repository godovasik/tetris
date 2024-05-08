#include <stdio.h>
#include <stdlib.h>

#include "../../gui/cli/gui.h"

#define FPS 60

typedef struct Figure {
  int figID;
  int fig[4][4];
  int y, x;
  int rotation;
} figure_t;
