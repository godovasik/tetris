#include "gui.h"

int boolBorder(int i, int j) {
  return (((i == 0) || (i == HEIGHT + 1) || (j == 0) || (j == WIDTH + 1)) &&
          (i <= HEIGHT + 1) && (j <= WIDTH + 1));
}

int boolPreview(int i, int j) {
  return 0;  //(((i == 5) || (i == 10)) && (j > WIDTH + 1) && (j < WIDTH + 9));
}
// int draw_preview(){};

int printStaticText() {
  for (int i = 0; i <= HEIGHT + 1; i++)
    for (int j = 0; j <= WIDTH + 10; j++)
      if (boolBorder(i, j) || boolPreview(i, j)) drawCell(1, i, j);
  attron(COLOR_PAIR(1));
  mvprintw(0, WIDTH + 2, "Next Piece");
  mvprintw(5, WIDTH + 2, "Score     ");
  mvprintw(8, WIDTH + 2, "Level     ");
  attroff(COLOR_PAIR(1));
}

int printDynamicText(int score, int level) {
  attron(COLOR_PAIR(1));
  mvprintw(6, WIDTH + 2, "%010d", score);
  mvprintw(9, WIDTH + 2, "%d", level);
  attroff(COLOR_PAIR(1));
}

void drawCell(int color, int i, int j) {
  attron(COLOR_PAIR(color));
  mvprintw(i, j, " ");
  attroff(COLOR_PAIR(color));
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
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

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

// int main() {
//   init();

//   while (1) {
//   }

//   getch();   // Wait for user input
//   endwin();  // End ncurses
//   return 0;
// }