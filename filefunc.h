#ifndef FILEFUNC_H
# define FILEFUNC_H

# include <fcntl.h>
# include <ncurses.h>
# include <curses.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>


typedef struct Userdata {
    char name[31];
    int score;
    int win;
    int lose;
} User;

void userfilesave(char* loginname1, char* loginname2 ,int result);

void userfilecreate(char* newusername);

void scoreboard(char* loginname1,char* loginname2);

#endif
