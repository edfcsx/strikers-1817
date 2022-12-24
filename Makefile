# Made for the 'gcc' compiler
# =-=-=-= GAME CONFIG =-=-=-=
OUT_FILENAME := strikers1817

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

SRC_SUBDIRS := scenes images entity

# =-=-=-= COMPILE CONFIG =-=-=-=
CC       := arm-none-eabi-gcc
AS       := arm-none-eabi-as
OBJCOPY  := arm-none-eabi-objcopy
EMULATOR := mgba-qt

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -O3 -fomit-frame-pointer -marm -mcpu=arm7tdmi -Wall -pedantic
ASFLAGS  := -mcpu=arm7tdmi
LDFLAGS  := -Tlnkscript -nostartfiles
LDLIBS   :=

# =-=-=-= FOLDER CONFIG =-=-=-=
MKDIR       := mkdir
MKDIRFLAGS  := -p

RM      := rm
RMFLAGS := -rfv

# =-=-=-= Build Output =-=-=-=
SRC := $(wildcard $(SRC_DIR)/*.c)\
       $(foreach DIR,$(SRC_SUBDIRS),$(wildcard $(SRC_DIR)/$(DIR)/*.c))
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OUT_ELF := $(BIN_DIR)/$(OUT_FILENAME).elf
OUT     := $(BIN_DIR)/$(OUT_FILENAME).gba

OBJ_DIRECTORIES := $(OBJ_DIR) $(foreach DIR,$(SRC_SUBDIRS),$(OBJ_DIR)/$(DIR))

# === Target Scripts ===
.PHONY: all run build clean

all: build

run:
	$(EMULATOR) ./$(OUT)

build: $(OUT)

clean:
	@$(RM) $(RMFLAGS) $(BIN_DIR) $(OBJ_DIR)

$(OUT): $(OUT_ELF)
	$(OBJCOPY) -O binary $^ $@

$(OUT_ELF): $(OBJ_DIR)/crt0.o $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/crt0.o: $(SRC_DIR)/crt0.s | $(OBJ_DIRECTORIES)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIRECTORIES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIRECTORIES):
	$(MKDIR) $(MKDIRFLAGS) "$@"

-include $(OBJ:.o=.d)
