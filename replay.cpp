#include "OmokUI.h"
#include "replay.h"
#include <ncurses.h>
#include <string.h>
#include <vector>
using namespace std;

void Queue::run_test(){
    OmokUI a;
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
    win = newwin(80, 80, 0, 0);

    wbkgd(win, COLOR_PAIR(1));
    drawCheckerboard();
    wmove(win,0,0);

    while(1){
        print_replay();
    }

    getch();
    endwin();
}
void Queue::push_xy(pair<int,int> p){
    queue_xy.push(p); //push xy
}

void Queue::push_player(bool &player){
    if(player){
        queue_player.push('O'); //player 1
    }
    else{
        queue_player.push('X'); //player 2
    }
}

void Queue::pop_queue(){
    queue_xy.pop();
    queue_player.pop();
}

void Queue::print_replay(){
    OmokUI ui;
    int c;
    keypad(win, TRUE);
    noecho();
    c=wgetch(win);

    if(c == 10){
        int x = queue_xy.front().first;
        int y = queue_xy.front().second;
        
        checkerboard[x][y] = queue_player.front();
        printCheckerboard();
        wprintw(win, "Press ENTER KEY to see next..\n");

        pop_queue();

        if(queue_xy.empty() == true && queue_player.empty() == true){
            wrefresh(win);
            wprintw(win, "do you want to play again? or go to login page?\n");
            wprintw(win, "(play again : y / go to login page : n)");
            //go play or quit
            if(c == 'y'){
                //go to play
            }
            if(c == 'n'){
                //go to login page
            }
        }
        
    }
    else if(c == 27){
        wprintw(win, "do you go to login page?\n");
        //quit
    }
    else{
        wprintw(win,"Wrong Command!\n");
    }
    
}
void Queue::drawCheckerboard() {
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

    printCheckerboard();
    wprintw(win, "Press ENTER KEY to see next..\n");
}

void Queue::printCheckerboard() {
    wclear(win);
    for (int i = 0; i < checkerboard.size(); i++) {
        for (int j = 0; j < checkerboard[i].size(); j++) {
            wprintw(win, "%c", checkerboard[i][j]);
        }
        wprintw(win, "\n");
    }
    wrefresh(win);
}