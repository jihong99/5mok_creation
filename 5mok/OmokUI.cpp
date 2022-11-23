#include <ncurses.h>
#include <vector>

using namespace std;
void drawCheckerboard(WINDOW *win);
int main(int argc, char const *argv[]) {
    WINDOW *window1;
    WINDOW *window2;

    initscr();

    if (has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return 1;
    } else {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    }
    refresh();

    window1 = newwin(80, 80, 0, 0);

    wbkgd(window1, COLOR_PAIR(1));

    drawCheckerboard(window1);
    wrefresh(window1);

    getch();
    endwin();
    return 0;
}

void drawCheckerboard(WINDOW *win) {
    vector<vector<char>> checkerboard;
    vector<char> row1;
    vector<char> row2;
    row1.push_back('+');
    row2.push_back('|');
    for (int i = 0; i < 19; i++) {
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
}
