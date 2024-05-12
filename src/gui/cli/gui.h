#ifndef GUI_H
#define GUI_H

#include <ncurses.h>
#include <stdlib.h>

#define HEIGHT 20
#define WIDTH 10

int boolBorder(int i, int j);
int boolPreview(int i, int j);
int printStaticText();
int printDynamicText(int score, int level);
void drawCell(int color, int i, int j);
int drawField(int field[HEIGHT][WIDTH], int score, int level, int nextFigureID,
              int figList[7][2][4]);
void startScreen();
int init();

#endif  // GUI_H