#include "OmokUI.h"
#include <ncurses.h>
#include <string.h>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
    OmokUI a;
    a.run();
    return 0;
}
OmokUI::OmokUI() { winner = -1; }
void OmokUI::run() {
    WINDOW *window1;
    vector<vector<char>> checkerboard;
    bool validate[37][73];
    for (int i = 0; i < 37; i++) {
        memset(validate[i], true, sizeof(bool) * 73);
    }
    bool player = true; // true : player1, false : player2
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
        moveCursor(window1, y, x, checkerboard, validate, player);
    }

    getch();
    endwin();
}

void OmokUI::drawCheckerboard(WINDOW *win, vector<vector<char>> &checkerboard) {
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

    printCheckerboard(win, checkerboard);
}

void OmokUI::printCheckerboard(WINDOW *win, vector<vector<char>> checkerboard) {
    wclear(win);
    for (int i = 0; i < checkerboard.size(); i++) {
        for (int j = 0; j < checkerboard[i].size(); j++) {
            wprintw(win, "%c", checkerboard[i][j]);
        }
        wprintw(win, "\n");
    }
    wrefresh(win);
}

void OmokUI::moveCursor(WINDOW *win, int &y, int &x,
                        vector<vector<char>> &checkerboard, bool validate[][73],
                        bool &player) {
    int c;
    keypad(win, TRUE);
    noecho();
    c = wgetch(win);
    if (c == KEY_RIGHT) {
        if (y == 72) {
            return;
        }
        y += 4;
        wmove(win, x, y);
    }
    if (c == KEY_LEFT) {
        if (y == 0) {
            return;
        }
        y -= 4;
        wmove(win, x, y);
    }
    if (c == KEY_UP) {
        if (x == 0) {
            return;
        }
        x -= 2;
        wmove(win, x, y);
    }
    if (c == KEY_DOWN) {
        if (x == 36) {
            return;
        }
        x += 2;
        wmove(win, x, y);
    }
    if (c == 10) {
        if (validate[x][y] && player) { // player 1
            checkerboard[x][y] = 'O';
            validate[x][y] = false;
            player = false;
        } else if (validate[x][y] && !player) { // player 2
            checkerboard[x][y] = 'X';
            validate[x][y] = false;
            player = true;
        }
        printCheckerboard(win, checkerboard);
        wmove(win, x, y);
        decideWinner(win, x, y, checkerboard);
    }
}

void OmokUI::decideWinner(WINDOW *win, int x, int y,
                          vector<vector<char>> checkerboard) {
    int count1 = 1; // count row
    int count2 = 1; // count col
    int count3 = 1; // count diag
    bool iscontinue1 = true;
    bool iscontinue2 = true;
    char comp = checkerboard[x][y];

    for (int i = 1; i < 5; i++) {
        if (checkStone(x, y + 4 * i, checkerboard, comp, iscontinue1)) {
            count1++;
        } // row
        if (checkStone(x + 2 * i, y, checkerboard, comp, iscontinue1)) {
            count2++;
        } // column
        if (checkStone(x + 2 * i, y + 4 * i, checkerboard, comp, iscontinue1)) {
            count3++;
        } // diagonal
    }
    for (int i = -1; i > -5; i--) {
        if (checkStone(x, y + 4 * i, checkerboard, comp, iscontinue2)) {
            count1++;
        } // row
        if (checkStone(x + 2 * i, y, checkerboard, comp, iscontinue1)) {
            count2++;
        } // column
        if (checkStone(x + 2 * i, y + 4 * i, checkerboard, comp, iscontinue1)) {
            count3++;
        } // diagonal
    }

    if (count1 == 5 || count2 == 5 || count3 == 5) {
        wmove(win, 37, 0);
        if (checkerboard[x][y] == 'O') {
            wprintw(win, "player 1win");
            wrefresh(win);
            winner = 1;
        }
        if (checkerboard[x][y] == 'X') {
            wprintw(win, "player 2win");
            wrefresh(win);
            winner = 0;
        }
    }
}

bool OmokUI::checkStone(int x, int y, vector<vector<char>> checkerboard,
                        char comp, bool &iscontinue) {
    if (x < 0 || x >= 37 || y < 0 || y >= 73) {
        return false;
    }
    if (!iscontinue) {
        return false;
    }
    if (checkerboard[x][y] == comp) {
        return true;
    }
    return false;
}

int OmokUI::getWinner() { return winner; }