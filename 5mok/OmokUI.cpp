#include <ncurses.h>
#include <vector>

using namespace std;
void run();
void drawCheckerboard(WINDOW *win, vector<vector<char>> &checkerboard);
void moveCursor(WINDOW *win, int &y, int &x);

int main(int argc, char const *argv[]) {
    run();
    return 0;
}
void run() {
    WINDOW *window1;
    vector<vector<char>> checkerboard;
    int x, y;
    initscr();

    if (has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return;
    } else {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    }
    refresh();
    window1 = newwin(80, 80, 0, 0);

    wbkgd(window1, COLOR_PAIR(1));
    getyx(window1, y, x);
    drawCheckerboard(window1, checkerboard);

    wmove(window1, 0, 0);

    while (1) { // test while
        moveCursor(window1, y, x);
    }

    getch();
    endwin();
}
void drawCheckerboard(WINDOW *win, vector<vector<char>> &checkerboard) {
    vector<char> row1;
    vector<char> row2;
    row1.push_back('+');
    row2.push_back('|');
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 3; j++) {
            row1.push_back('-');
            row2.push_back(' ');
        }
        row1.push_back('+');
        row2.push_back('|');
    }
    for (int i = 0; i < 18; i++) {
        checkerboard.push_back(row1);
        checkerboard.push_back(row2);
    }
    checkerboard.push_back(row1);

    for (int i = 0; i < checkerboard.size(); i++) {
        for (int j = 0; j < checkerboard[i].size(); j++) {
            wprintw(win, "%c", checkerboard[i][j]);
        }
        wprintw(win, "\n");
    }
    wrefresh(win);
}
void moveCursor(WINDOW *win, int &y, int &x) {
    int c;
    keypad(win, TRUE);
    noecho();
    c = wgetch(win);
    if (c == KEY_RIGHT) {
        if (y == 72) {
            return;
        }
        wmove(win, x, y + 4);
        y += 4;
    }
    if (c == KEY_LEFT) {
        if (y == 0) {
            return;
        }
        wmove(win, x, y - 4);
        y -= 4;
    }
    if (c == KEY_UP) {
        if (x == 0) {
            return;
        }
        wmove(win, x - 2, y);
        x -= 2;
    }
    if (c == KEY_DOWN) {
        if (x == 36) {
            return;
        }
        wmove(win, x + 2, y);
        x += 2;
    }
}
