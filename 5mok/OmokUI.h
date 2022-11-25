#include <ncurses.h>
#include <string.h>
#include <vector>

using namespace std;

#pragma once
class OmokUI {
  private:
    int winner;
    WINDOW *win;
    vector<vector<char>> checkerboard;

  public:
    OmokUI();
    void run();
    void drawCheckerboard();
    void moveCursor(int &y, int &x, bool validate[][73], bool &player);
    void printCheckerboard();
    void decideWinner(int x, int y);
    bool checkStone(int x, int y, char comp, bool &iscontinue);
    int getWinner(); // return winner (player1 return 1, player2 return 0)
    pair<int, int>
    getCurrentPosition(int x, int y); // return current position for queue
};
