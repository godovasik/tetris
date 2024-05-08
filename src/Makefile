CC = gcc
# FLAGS = -Wall -Wextra -Werror -std=c11
FLAGS = -std=c11

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    NCURSES_LIB += -lncurses
else ifeq ($(UNAME), Darwin)
    NCURSES_LIB += -lncursesw
endif

LIB_NAME = s21_tetris

SRCS = $(wildcard brick_game/tetris/*.c) $(wildcard gui/cli/*.c)

all: $(LIB_NAME)

$(LIB_NAME): $(SRCS)
	$(CC) $(FLAGS) -o $@ $(SRCS) $(NCURSES_LIB)

clean:
	rm -f $(LIB_NAME)