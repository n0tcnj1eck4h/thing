SOURCES = $(patsubst src/%, %, $(wildcard src/*.c))
RESOURCES = frag.glsl vert.glsl
LIBS = glfw3 cglm

BUILD_DIR=build
SRC_DIR=src
OBJ_DIR=obj
RSC_DIR=resources

LDFLAGS := `pkg-config --libs   $(LIBS)`
CFLAGS  := `pkg-config --cflags $(LIBS)` -Wall -g -Isrc -O0 -DDEBUG

OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))
OBJS += $(patsubst %, $(OBJ_DIR)/$(RSC_DIR)/%.o, $(RESOURCES))

.PRECIOUS: $(OBJ_DIR)/$(RSC_DIR)/%.c
.PHONY: all build clean run

all: build

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

$(OBJ_DIR)/$(RSC_DIR)/%.c: $(RSC_DIR)/%
	xxd -i $< $@
