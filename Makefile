

SRC_DIR  = src
BUILD_DIR = build
MAKEDIR  = mkdir -p
SRC_FILES   = $(wildcard $(SRC_DIR)/*.c)
OBJ		= build/puzzleGUI.o build/puzzleGame.o build/main.o build/puzzleCss.o
#OBJ_BUILDED = $(addprefix build/,$(OBJ))

TARGET = puzzle


CFLAGS = -g -pedantic -O2 -Wall ${DP} -DGTK_DISABLE_DEPRECATED=1 -DGDK_DISABLE_DEPRECATED=1 -DG_DISABLE_DEPRECATED=1 `pkg-config --cflags gtk+-3.0`
#LDLIBS = `pkg-config --libs gtk+-3.0`
LDLIBS = $(shell pkg-config --libs gtk+-3.0)
LDFLAGS = -std=c11 -g
CC = gcc 


default: folder $(TARGET)

folder:
	$(MAKEDIR) $(BUILD_DIR)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -c -I$(SRC_DIR) $< -o $@  $(LDLIBS)
	

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDLIBS)


#main : 
#	$(CC) $(LDFLAGS) $(SRC_FILES) main.c -o $(NAME) $(LDLIBS)

clean :
	rm -rf $(OBJ)
	rm --force $(TARGET) 

run	:
	./$(TARGET)