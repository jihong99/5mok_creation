#include <ncurses.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

class Queue{
private:
    queue<pair<int,int>> queue_xy;
    queue<char> queue_player;
    WINDOW *win;
    vector<vector<char>> checkerboard;
public:
    void push_xy(pair<int,int> p);
    void push_player(bool &player);
    void pop_queue();
    void print_replay();
    void run_test();
    void printCheckerboard();
    void drawCheckerboard();
};
