#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#

#define WIDTH 10
#define HEIGHT 20

#define FPS 60

typedef struct Figure {
  int figID;
  int fig[2][4];
  int y, x;
  int rotation;
} figure_t;
