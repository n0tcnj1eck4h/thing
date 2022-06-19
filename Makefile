CC=gcc
CFLAGS=-Wall -g -Isrc

BUILD_DIR=build
SRC_DIR=src
OBJ_DIR=obj
RSC_DIR=resources

SOURCES = main.c GL.c
RESOURCES = basic.vert
LIBS = glfw3

LDFLAGS = `pkg-config --libs $(LIBS)`
CFLAGS += `pkg-config --cflags $(LIBS)`

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))
OBJS += $(patsubst %.vert, $(OBJ_DIR)/$(RSC_DIR)/%.o, $(RESOURCES))

all: build

.PRECIOUS: $(OBJ_DIR)/$(RSC_DIR)/%.c

build: $(OBJS)
	$(CC) $(CFLAGS) $? $(LDFLAGS) -o $(BUILD_DIR)/out
	chmod +x $(BUILD_DIR)/out

clean:
	$(RM) $(BUILD_DIR)/*
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(OBJ_DIR)/$(RSC_DIR)/*.o
	$(RM) $(OBJ_DIR)/$(RSC_DIR)/*.c

run: build
	$(BUILD_DIR)/out

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)-o $@


$(OBJ_DIR)/$(RSC_DIR)/%.o: $(OBJ_DIR)/$(RSC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@

$(OBJ_DIR)/$(RSC_DIR)/%.c: $(RSC_DIR)/%.vert
	xxd -i $< $@
