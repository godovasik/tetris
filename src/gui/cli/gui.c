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
  attron(COLOR_PAIR(2));
  mvprintw(0, WIDTH + 2, "Next Piece");
  mvprintw(6, WIDTH + 2, "Score     ");
  mvprintw(9, WIDTH + 2, "Level     ");
  attroff(COLOR_PAIR(2));
}

int printDynamicText(int score, int level) {
  attron(COLOR_PAIR(1));
  mvprintw(7, WIDTH + 2, "%d", score);
  mvprintw(13, WIDTH + 2, "%d", level);
  attroff(COLOR_PAIR(1));
}

void drawWhiteBox(int i, int j) {
  attron(COLOR_PAIR(2));
  mvprintw(i, j, " ");
  attroff(COLOR_PAIR(2));
}

int draw() {
  for (int i = 0; i <= HEIGHT + 1; i++) {
    for (int j = 0; j <= WIDTH + 10; j++) {
      if (boolBorder(i, j) || boolPreview(i, j)) drawWhiteBox(i, j);
    }
  }
  printStaticText();
}

int main() {
  initscr();      // Initialize ncurses
  start_color();  // Start color functionality
  noecho();
  curs_set(FALSE);  // Don't display a cur

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  bkgd(COLOR_PAIR(1));  // Set the background to color pair 1

  draw();
  printStaticText(0, 0, 0);
  refresh();  // Refresh the screen to match what's in memory
  startGame();

  getch();   // Wait for user input
  endwin();  // End ncurses
  return 0;
}