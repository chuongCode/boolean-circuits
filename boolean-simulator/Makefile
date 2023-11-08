#
# File: Makefile
# Creator: George Ferguson
# Created: Mon Nov 28 13:52:02 2016
# Time-stamp: <Tue Nov 29 14:52:45 EST 2022 ferguson>
#

SRCS = Boolean.c Gates.c Circuit.c strdup.c main.c
HDRS = Boolean.h Gates.h Circuit.h strdup.h
OBJS = $(SRCS:.c=.o)
EXE = boosim
ZIPDIR = CSC173 Project 5 Boolean Circuit Simulator

CFLAGS = -std=c99 -Wall -Werror -g

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

valgrind:
	valgrind ./$(EXE)

clean:
	-rm $(OBJS) $(EXE)

