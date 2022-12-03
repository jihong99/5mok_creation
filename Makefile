filefunc.o : filefunc.h filefunc.cpp
    g++ -c filefunc.cpp -lncurses
OmokUI.o : OmokUI.h replay.h OmokUI.cpp
    g++ -c OmokUI.cpp -lncurses
replay.o : OmokUI.h replay.h replay.cpp
    g++ -c replay.cpp -lncurses
main.o : main.cpp filefunc.h OmokUI.h replay.h
    g++ -c main.cpp -lncurses -lform
main : filefunc.o OmokUI.o replay.o main.o
    g++ filefunc.o OmokUI.o replay.o main.o -o main -lncurses -lform
