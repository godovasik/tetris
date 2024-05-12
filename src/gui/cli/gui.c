#include "gui.h"

int boolBorder(int i, int j) {
  return (((i == 0) || (i == HEIGHT + 1) || (j == 0) || (j == WIDTH + 1) ||
           (j == WIDTH * 2 + 2)) &&
          (i <= HEIGHT + 1) && (j <= WIDTH * 2 + 2));
}

int printStaticText() {
  for (int i = 0; i <= HEIGHT + 1; i++)
    for (int j = 0; j <= WIDTH * 2 + 2; j++)
      if (boolBorder(i, j)) drawCell(1, i, j);
  attron(COLOR_PAIR(1));
  mvprintw(0, WIDTH + 2, "Next Piece");
  mvprintw(5, WIDTH + 2, "Score     ");
  mvprintw(6, WIDTH + 2, "          ");
  mvprintw(8, WIDTH + 2, "Level     ");
  mvprintw(9, WIDTH + 2, "          ");
  mvprintw(HEIGHT + 1, 5, "(c) baileyfl, 2024");
  attroff(COLOR_PAIR(1));
}

int printDynamicText(int score, int level) {
  attron(COLOR_PAIR(1));
  mvprintw(6, WIDTH + 2, "%d", score);
  mvprintw(9, WIDTH + 2, "%d", level);
  attroff(COLOR_PAIR(1));
}

void drawCell(int color, int i, int j) {
  attron(COLOR_PAIR(color));
  mvprintw(i, j, " ");
  attroff(COLOR_PAIR(color));
}

void startScreen() {
  int tetris[5][23] = {
      {2, 2, 2, 0, 3, 3, 3, 0, 4, 4, 4, 0, 5, 5, 5, 0, 6, 6, 6, 0, 7, 7, 7},
      {0, 2, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 5, 0, 5, 0, 0, 6, 0, 0, 7, 0, 0},
      {0, 2, 0, 0, 3, 3, 3, 0, 0, 4, 0, 0, 5, 5, 0, 0, 0, 6, 0, 0, 7, 7, 7},
      {0, 2, 0, 0, 3, 0, 0, 0, 0, 4, 0, 0, 5, 0, 5, 0, 0, 6, 0, 0, 0, 0, 7},
      {0, 2, 0, 0, 3, 3, 3, 0, 0, 4, 0, 0, 5, 0, 5, 0, 6, 6, 6, 0, 7, 7, 7}};
  ;
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 23; j++) drawCell(tetris[i][j], i, j);
  attron(COLOR_PAIR(1));

  mvprintw(7, 1, "Press any key to start");
  attroff(COLOR_PAIR(1));

  mvprintw(10, 1, "Controls:");
  mvprintw(12, 1, "Arrows - move piece");
  mvprintw(13, 1, "Space  - rotate piece");
  mvprintw(14, 1, "P      - pause");
  mvprintw(15, 1, "ESC    - end game");

  while (true) {
    if (getch() != ERR) break;
    napms(100);
  }
  clear();
}

void pause() {
  attron(COLOR_PAIR(0));
  mvprintw(11, WIDTH + 2, "  PAUSE   ");
  mvprintw(13, WIDTH + 2, "  Press   ");
  mvprintw(14, WIDTH + 2, "any key to");
  mvprintw(15, WIDTH + 2, " continue ");
  attroff(COLOR_PAIR(0));
  while (true) {
    if (getch() != ERR) break;
    napms(50);
  }
  clear();
}

void gg(int score) {
  attron(COLOR_PAIR(1));
  int scoreSize = snprintf(NULL, 0, "%d", score);
  mvprintw(11, 2, "     GAME OVER     ");
  mvprintw(12, 2, " Your final score: ");
  mvprintw(13, 2, "                   ");
  move(13, 2);
  for (int i = 0; i < 10 - (scoreSize + 1) / 2; i++) printw(" ");
  printw("%d", score);
  mvprintw(14, 2, "   Press any key   ");
  mvprintw(15, 2, "      to exit      ");
  attroff(COLOR_PAIR(1));

  while (true) {
    if (getch() != ERR) break;
    napms(50);
  }
  clear();
}

int drawField(int field[HEIGHT][WIDTH], int score, int level, int nextFigureID,
              int figList[7][2][4]) {
  for (int i = 0; i <= HEIGHT; i++) {
    for (int j = 0; j <= WIDTH; j++) {
      drawCell(field[i][j], i + 1, j + 1);  // draws current game state
    }
  }
  printStaticText();
  printDynamicText(score, level);
  if (nextFigureID != -1)
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 4; j++)
        drawCell(figList[nextFigureID][i][j], i + 2, j + WIDTH + 5);
  refresh();
}

int init() {
  initscr();      // Initialize ncurses
  start_color();  // Start color functionality
  noecho();
  curs_set(FALSE);  // Don't display a cur
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  init_pair(0, COLOR_WHITE, COLOR_BLACK);    // black
  init_pair(1, COLOR_BLACK, COLOR_WHITE);    // white
  init_pair(2, COLOR_BLACK, COLOR_RED);      // red
  init_pair(3, COLOR_BLACK, COLOR_GREEN);    // green
  init_pair(4, COLOR_BLACK, COLOR_BLUE);     // blue
  init_pair(5, COLOR_BLACK, COLOR_YELLOW);   // yellow
  init_pair(6, COLOR_BLACK, COLOR_MAGENTA);  // magenta
  init_pair(7, COLOR_BLACK, COLOR_CYAN);     // cyan

  bkgd(COLOR_PAIR(0));  // Set the background to color pair 1
}