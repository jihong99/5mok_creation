#include <ncurses.h>
#include <string.h>
#include <vector>

using namespace std;

#pragma once
class OmokUI {
  private:
    int winner;

  public:
    OmokUI();
    void run();
    void drawCheckerboard(WINDOW *win, vector<vector<char>> &checkerboard);
    void moveCursor(WINDOW *win, int &y, int &x,
                    vector<vector<char>> &checkerboard, bool validate[][73],
                    bool &player);
    void printCheckerboard(WINDOW *win, vector<vector<char>> checkerboard);
    void decideWinner(WINDOW *win, int x, int y,
                      vector<vector<char>> checkerboard);
    bool checkStone(int x, int y, vector<vector<char>> checkerboard, char comp,
                    bool &iscontinue);
    int getWinner(); // return winner (player1 return 1, player2 return 0)
};
