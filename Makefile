

CFLAGS = -g -pedantic -O2 -Wall ${DP} -DGTK_DISABLE_DEPRECATED=1 -DGDK_DISABLE_DEPRECATED=1 -DG_DISABLE_DEPRECATED=1 `pkg-config --cflags gtk+-3.0`
LDLIBS = `pkg-config --libs gtk+-3.0`
LDFLAGS = -g
CC = gcc -std=c11
NAME = puzzle

all : puzzle

main : 
	$(CC) $(LDFLAGS) -o $(NAME) $(LDLIBS)

clean :
	rm -f $(NAME) 

run	:
	./$(NAME)