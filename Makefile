SOURCES = $(patsubst src/%, %, $(wildcard src/*.c))
RESOURCES = frag.glsl vert.glsl comp.glsl
LIBS = glfw3 cglm

BUILD_DIR=build
SRC_DIR=src
OBJ_DIR=obj
RSC_DIR=resources

LDLIBS := $(shell pkg-config --libs   $(LIBS))
CFLAGS := $(shell pkg-config --cflags $(LIBS)) -Wall -g -Isrc -DDEBUG

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES)) $(patsubst %, $(OBJ_DIR)/$(RSC_DIR)/%.o, $(RESOURCES))

.PRECIOUS: $(OBJ_DIR)/$(RSC_DIR)/%.c
.PHONY: all build clean run

all: build

build: $(OBJS)
	$(CC) $(LDFLAGS) $? $(LDLIBS) -o  $(BUILD_DIR)/out
	chmod +x  $(BUILD_DIR)/out

clean:
	$(RM) $(BUILD_DIR)/*
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(OBJ_DIR)/$(RSC_DIR)/*.o
	$(RM) $(OBJ_DIR)/$(RSC_DIR)/*.c

run: build
	$(BUILD_DIR)/out

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(RSC_DIR)/%.o: $(OBJ_DIR)/$(RSC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(RSC_DIR)/%.c: $(RSC_DIR)/%
	xxd -i $< $@
