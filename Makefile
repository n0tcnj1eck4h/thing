CC=gcc
CFLAGS=-Wall -g -Isrc

BUILD_DIR=build
SRC_DIR=src
OBJ_DIR=obj

SOURCES = main.c GL.c
LIBS = glfw3

LDFLAGS = `pkg-config --libs $(LIBS)`
CFLAGS += `pkg-config --cflags $(LIBS)`

all: build

build: $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))
	$(CC) $(CFLAGS) $? $(LDFLAGS) -o $(BUILD_DIR)/out
	chmod +x $(BUILD_DIR)/out

clean:
	$(RM) $(BUILD_DIR)/*
	$(RM) $(OBJ_DIR)/*

run: build
	$(BUILD_DIR)/out

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
