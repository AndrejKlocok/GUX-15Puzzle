# author: 	Andrej Klocok
# login:  	xkloco00
# file:		Makefile

SRC_DIR  	= src
BUILD_DIR	= build
MAKEDIR  	= mkdir -p
SRC_FILES   = $(wildcard $(SRC_DIR)/*.c)
OBJ			= build/puzzleGUI.o build/puzzleGame.o build/main.o build/puzzleCss.o
TARGET 		= puzzle


CFLAGS = -std=c11 -Wall -pedantic -O2  `pkg-config --cflags gtk+-3.0` 
LDLIBS = `pkg-config --libs gtk+-3.0`
#/DLIBS = $(shell pkg-config --libs gtk+-3.0)
LDFLAGS =  -g
CC = gcc 


default: folder $(TARGET)

folder:
	$(MAKEDIR) $(BUILD_DIR)

#$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c 
#	$(CC) $(CFLAGS) -c -I$(SRC_DIR) $< -o $@

$(BUILD_DIR)/main.o:	
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $@

$(BUILD_DIR)/puzzleGUI.o:	
	$(CC) $(CFLAGS) -c  $(SRC_DIR)/puzzleGUI.c -o $@ 

$(BUILD_DIR)/puzzleGame.o: 
	$(CC) $(CFLAGS) -c  $(SRC_DIR)/puzzleGame.c	 -o $@ 

$(BUILD_DIR)/puzzleCss.o: 	
	$(CC) $(CFLAGS) -c  $(SRC_DIR)/puzzleCss.c -o $@ 

$(TARGET): $(OBJ)
	$(CC) $(OBJ)  $(CFLAGS) $(LDLIBS) -o $@ 


clean :
	rm -rf $(OBJ)
	rm -rf $(TARGET) 

run	:
	./$(TARGET)
