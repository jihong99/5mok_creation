CC=g++
CFLAGS=-g -Wall
TARGET=omok

OBJS=OmokUI.o filefunc.o replay.o maintest.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lncurses -lform

OmokUI.o : OmokUI.cpp
	$(CC) -c -o OmokUI.o OmokUI.cpp

filefunc.o : filefunc.cpp
	$(CC) -c -o filefunc.o filefunc.cpp

replay.o : replay.cpp
	$(CC) -c -o replay.o replay.cpp
maintest.o : maintest.cpp
	$(CC) -c -o maintest.o maintest.cpp
