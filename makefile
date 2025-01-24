CFLAGS = -Iinclude -g

ifeq ($(OS),Windows_NT)
	CFLAGS += libs/*.dll -mwindows -Wl,--stack,167772160 -Ilua/win -mconsole
	RM_FORCE = powershell -NoProfile -Command rm -r -force
	CP = powershell -NoProfile -Command cp -Recurse -Force
else
	CFLAGS += -lSDL2 -lSDL2_image libs/liblua54.a -Ilua/linux -lm
	RM_FORCE = rm -rf
	CP = cp -r
endif

SRCS = $(wildcard src/*.c src/*/*.c src/*/*/*.c main.c)
OUT_FILE = pk_ul
OUT_DIR = out

all: linux

linux:
	mkdir -p out
	gcc $(SRCS) $(CFLAGS) -o $(OUT_DIR)/$(OUT_FILE)
	$(CP) assets out/
	$(CP) scripts out/

win:
	if not exist out mkdir out
	gcc $(SRCS) $(CFLAGS) -o $(OUT_DIR)/$(OUT_FILE)
	$(CP) libs/*.dll $(OUT_DIR)
	$(CP) assets out/
	$(CP) scripts out/

run:
	./$(OUT_DIR)/$(OUT_FILE)

debug:
	valgrind ./$(OUT_DIR)/$(OUT_FILE)

clean:
	$(RM_FORCE) out

linux_editor:
	mkdir -p out
	gcc $(SRCS) $(CFLAGS) -o $(OUT_DIR)/$(OUT_FILE)_editor -DWORLD_EDITOR
	$(CP) assets out/
	$(CP) scripts out/
	./$(OUT_DIR)/$(OUT_FILE)_editor

win_editor:
	if not exist out mkdir out
	gcc $(SRCS) $(CFLAGS) -o $(OUT_DIR)/$(OUT_FILE)_editor -DWORLD_EDITOR
	$(CP) libs/*.dll $(OUT_DIR)
	$(CP) assets out/
	$(CP) scripts out/
	./$(OUT_DIR)/$(OUT_FILE)_editor

editor_run:
	./$(OUT_DIR)/$(OUT_FILE)_editor

scripts:
	$(CP) scripts out/

.PHONY: all linux win run debug clean linux_editor win_editor editor_run scripts