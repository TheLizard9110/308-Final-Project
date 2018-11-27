CC		= gcc
TARGET		= program
SRCDIR		= src

SRC		= $(wildcard $(SRCDIR)/*.c)

OBJ		= $(SRC:.c=.o)
LIB		= -lncurses


build: clean $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIB)

-PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
