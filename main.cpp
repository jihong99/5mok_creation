#include <fcntl.h>
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


using std::string;

string name1;  // 전역변수를 통해 userid 저장 (중요)
string name2;

void sam(){  // 로그인 창 함수를 임의로 흉내낸 버전, 로그인창 팀은 그냥 함수 안에서 name1이랑 name2 전역변수에 이름 저장해주면 됨
    string user[2]={"player1","player2"};
    name1=user[0];
    name2=user[1];



}


int main(){

    sam();

    userfilecreate(name1,name2);

    // ingame

    int result=0;

    userfilesave(name1,name2,result);


    return 0;


}
