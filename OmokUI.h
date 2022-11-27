#include <ncurses.h>
#include <string.h>
#include <vector>

using namespace std;

class OmokUI {
  private:
    int winner;
    WINDOW *win;
    

  public:
    vector<vector<char>> checkerboard;
    OmokUI();
    void run();
    void drawCheckerboard();
    void moveCursor(int &y, int &x, bool validate[][73], bool &player);
    void printCheckerboard();
    void decideWinner(int x, int y);
    bool checkStone(int x, int y, char comp, bool &iscontinue);
    int getWinner(); // return winner (player1 return 1, player2 return 0)
};