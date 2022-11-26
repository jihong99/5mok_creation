#include <fcntl.h>
#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "filefunc.h"


void userfilesave(char* loginname1,char* loginname2, int result){

    // loginname= received username from login (changeable)
    // result = win(1) or lose(0) from last game (changeable)

    
    

    char filename1[30] = "./"; // path fix
    char filename2[30] = "./";
    char dat[] = ".dat";
    strcat(filename1, loginname1);    // making the './name.dat' form
    strcat(filename1, dat);

    strcat(filename2, loginname2);
    strcat(filename2, dat);

    printf("filename1 : %s\n", filename1);
    printf("filename2 : %s\n", filename2);
    char *pathname2 = filename2;
    char *pathname1 = filename1; // convert to pointer

    
    
    int fd1;
    int fd2;
    ssize_t wsize = 0;
    ssize_t readsize = 0;

    if (access(pathname1, F_OK) != -1) {

        User *olduser1 = (User *)malloc(sizeof(User)); // struct generate
        memset(olduser1->name, '\0', 31);

        olduser1->win = 0;
        olduser1->lose = 0;
        olduser1->score = 0;

        fd1 = open(pathname1, O_RDWR, 0666); // open

        if (fd1 == -1) {
            perror("open error");
            exit(-1);
        }

        readsize = read(fd1, (User *)olduser1, sizeof(User)); // read

        if (readsize == -1) {
            perror("read error");
            exit(-2);
        }
        printf("fd1 : %d , rsize: %ld\n", fd1, readsize);

        if (result == 0) { // if player1 last game lost
            olduser1->lose = olduser1->lose + 1;
            olduser1->score = olduser1->score - 1;

        } else if(result==1){ // if player1 last game won
            olduser1->win = olduser1->win + 1;
            olduser1->score = olduser1->score + 3;
        }

        wsize = (write(fd1, (User *)olduser1, sizeof(User)));
        if (wsize == -1) {
            perror("write name error");
            exit(-2);
        }
        // 이부분에 mvprintw 를 통해 원하는 좌표에 사용자의 최신화된 정보 출력
        printf("%s's scoreboard\nWin %d times\nLose %d times\nYour score now : "
               "%d\n",
               olduser1->name, olduser1->win, olduser1->lose, olduser1->score);

        close(fd1);
        free(olduser1);

    } else { // ONLY first time login
        perror("file does not exists");
        exit(-3);
    }

    //  ------------------------------ now user2
    if (access(pathname2, F_OK) != -1) {

        User *olduser2 = (User *)malloc(sizeof(User)); // struct generate
        memset(olduser2->name, '\0', 31);

        olduser2->win = 0;
        olduser2->lose = 0;
        olduser2->score = 0;

        fd2 = open(pathname2, O_RDWR, 0666); // open

        if (fd2 == -1) {
            perror("open error");
            exit(-1);
        }

        readsize = read(fd2, (User *)olduser2, sizeof(User)); // read

        if (readsize == -1) {
            perror("read error");
            exit(-2);
        }
        printf("fd2 : %d , rsize: %ld\n", fd2, readsize);

        if (result == 1) { // if player2 last game lost
            olduser2->lose = olduser2->lose + 1;
            olduser2->score = olduser2->score - 1;

        } else if(result==0) { // if player2 last game won
            olduser2->win = olduser2->win + 1;
            olduser2->score = olduser2->score + 3;
        }

        wsize = (write(fd2, (User *)olduser2, sizeof(User)));
        if (wsize == -1) {
            perror("write name error");
            exit(-2);
        }
        // 이부분에 mvprintw 를 통해 원하는 좌표에 사용자의 최신화된 정보 출력
        printf("%s's scoreboard\nWin %d times\nLose %d times\nYour score now : "
               "%d\n",
               olduser2->name, olduser2->win, olduser2->lose, olduser2->score);

        close(fd2);
        free(olduser2);

    } else { // ONLY first time login
        perror("file does not exists");
        exit(-3);
    }
}

void userfilecreate(char* newusername) {  //user file first time create, one time per one user
    char newfilename[30] = "./";
    char newdat[] = ".dat";
    strcat(newfilename, newusername);
    strcat(newfilename, newdat);
    printf("newfilename: %s\n", newfilename);
    char *newpathname = newfilename;
    int nothing = 0;
    int fd;
    ssize_t wsize = 0;
    if (access(newpathname, F_OK) != -1) { // already file exists
        nothing++;  // do nothing

    } else { // first time login
        User *user = (User *)malloc(sizeof(User));
        memset(user->name, '\0', 31);
        strcpy(user->name, newusername);

        user->win = 0;
        user->lose = 0;
        user->score = 100;

        fd = open(newpathname, O_CREAT | O_RDWR, 0666); // open

        if (fd == -1) {
            perror("open error");
            exit(-1);
        }

        wsize = write(fd, (User *)user, sizeof(User)); // write

        if (wsize == -1) {
            perror("write name error");
            exit(-2);
        }

        printf("fd : %d , wsize: %ld\n", fd, wsize);

        close(fd);
        free(user);
    }
}

void scoreboard(char* loginname1, char* loginname2) { 
        
    char filename1[30] = "./"; // path fix
    char filename2[30] = "./";
    char dat[] = ".dat";
    strcat(filename1, loginname1); // making the './name.dat' form
    strcat(filename1, dat);

    strcat(filename2, loginname2);
    strcat(filename2, dat);

    //printf("filename1 : %s\n", filename1);
    //printf("filename2 : %s\n", filename2);
    char *pathname2 = filename2;
    char *pathname1 = filename1; // convert to pointer

    int fd1;
    int fd2;
    ssize_t readsize1 = 0;
    ssize_t readsize2 = 0;

    if(access(pathname1, F_OK)==0 && access(pathname2, F_OK)==0){
        User *olduser1 = (User *)malloc(sizeof(User)); // struct generate
        memset(olduser1->name, '\0', 31);

        olduser1->win = 0;
        olduser1->lose = 0;
        olduser1->score = 0;

        fd1 = open(pathname1, O_RDWR, 0666); // open

        if (fd1 == -1) {
            //perror("open error");
            exit(-1);
        }

        readsize1 = read(fd1, (User *)olduser1, sizeof(User)); // read

        if (readsize1 == -1) {
            //perror("read error");
            exit(-2);
        }
        //printf("fd1 : %d , rsize: %ld\n", fd1, readsize);
        User *olduser2 = (User *)malloc(sizeof(User)); // struct generate
        memset(olduser2->name, '\0', 31);

        olduser2->win = 0;
        olduser2->lose = 0;
        olduser2->score = 0;

        fd2 = open(pathname2, O_RDWR, 0666); // open

        if (fd2 == -1) {
            //perror("open error");
            exit(-1);
        }

        readsize2 = read(fd2, (User *)olduser2, sizeof(User)); // read

        if (readsize2 == -1) {
            //perror("read error");
            exit(-2);
        }

        initscr();
        noecho();
        clear();

        mvprintw(0, 0, "Press any botton to leave");

        mvprintw(15, 10, "[%s's scoreboard]", olduser1->name);
        mvprintw(16, 10, "Win %d times", olduser1->win);
        mvprintw(17, 10, "Lose %d times", olduser1->lose);
        mvprintw(18, 10, "Your score now : %d", olduser1->score);

        mvprintw(15, 35, "[%s's scoreboard]", olduser2->name);
        mvprintw(16, 35, "Win %d times", olduser2->win);
        mvprintw(17, 35, "Lose %d times", olduser2->lose);
        mvprintw(18, 35, "Your score now : %d", olduser2->score);

        refresh();

        getch();
        endwin();

        close(fd1);
        close(fd2);
        free(olduser1);
        free(olduser2);
    }
    else{
        perror("File not exists");
        exit(-4);
    }

    
}
