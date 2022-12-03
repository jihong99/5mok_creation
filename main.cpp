#include <fcntl.h>
#include <form.h>
#include <ctype.h>
#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include "filefunc.h"
#include "OmokUI.h"
#include "replay.h"
//주석부분 풀지 말것

using std::string;

string user1;  // 전역변수를 통해 userid 저장 (중요)
string user2;

/*void sam(){  // 로그인 창 함수를 임의로 흉내낸 버전, 로그인창 팀은 그냥 함수 안에서 name1이랑 name2 전역변수에 이름 저장해주면 됨
	string user[2]={"player1","player2"};
	user1=user[0];
	user2=user[1];



}*/

int login() {
    FIELD *field[3]; // for input user name
    FORM *my_form;   // making field
    clear();
    int ch;

    initscr();
    cbreak();
    noecho();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    keypad(stdscr, TRUE);
    field[0] =
        new_field(1, 10, 12, 38, 0, 0); // make a file in a proper location
    field[1] = new_field(1, 10, 14, 38, 0, 0);
    field[2] = NULL;

    set_field_back(field[0], A_UNDERLINE); // show underline
    field_opts_off(field[0], O_AUTOSKIP);

    set_field_back(field[1], A_UNDERLINE);
    field_opts_off(field[1], O_AUTOSKIP);

    my_form = new_form(field);
    post_form(my_form);
    refresh();

    attron(COLOR_PAIR(1));

    mvprintw(12, 35, "P1:");
    mvprintw(14, 35, "P2:");
    mvprintw(1, 1, "Start press F1.");                  // show manual
    mvprintw(2, 1, "Press ESC if you want to go back"); // show manual
    refresh();                                          // show!!
    while (1) { // repeat untill pressed f1key
        while ((ch = getch()) != KEY_F(1)) {
            switch (ch) {
            case '\n':     // when press enter, down key
            case KEY_DOWN: // move under field
                form_driver(my_form, REQ_NEXT_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;
            case KEY_UP: // when press key up
                form_driver(my_form, REQ_PREV_FIELD);
                form_driver(my_form, REQ_END_LINE);
                break;                              // move top field
            case KEY_BACKSPACE:                     // when press key backspace
                form_driver(my_form, REQ_DEL_PREV); // remove
                break;
            case 27:      // esc key
                endwin(); // exit --> back to menu window
				return 27;
            default:
                form_driver(my_form, ch); // input string
                break;
            }
        }

       /* char usr1[30],usr2[30];

        strcpy(usr1, field_buffer(field[0], 0)); // make user1 name
        strcpy(usr2, field_buffer(field[1], 0)); // make user2 name
        if (isspace(usr1[0]) || isspace(usr2[0])) {
            // if the name begins with a blank space, show error message
            mvprintw(16, 20, "please remove the spaces in the first letter");
            continue;
        }
		mvprintw(20,20,"%s %s",usr1,usr2);
		refresh();

        char u1[30];
        char u2[30];

        for (int i = 0; i < sizeof(usr1); i++) {
            u1[i] = usr1[i];
        }
        for (int i = 0; i < sizeof(usr2); i++) {
            u2[i] = usr2[i];
        }*/

        string name1(field_buffer(field[0],0));
        string name2(field_buffer(field[1],0));

        mvprintw(20, 35, "%s%s", name1, name2);
        refresh();

        user1 = name1;
        user2 = name2;
		
        unpost_form(my_form);
        free_form(my_form); // end use form
        free_field(field[0]);
        free_field(field[1]);
        free_field(field[2]);
        endwin();
		

    }
	return 1;
}



int main(){

	login();
	
	userfilecreate(user1,user2);
	scoreboard(user1,user2);

	OmokUI a;
	a.run();
	
	int result=0;

  userfilesave(user1, user2, result); 
        //이름 공백 오류로 덮어쓰기 안이루어짐, 구동에는 문제없으니 후에 고침

  return 0;
}