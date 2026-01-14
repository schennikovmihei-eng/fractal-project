CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG
LDFLAGS = -lm

SRCDIR = src
BUILDDIR = build
BINDIR = bin

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(1)" mkdir "$(1)"
    RMDIR = rmdir /S /Q "$(1)" 2>nul
    RM = del "$(1)" 2>nul
    EXE_EXT = .exe
else
    MKDIR = mkdir -p "$(1)"
    RMDIR = rm -rf "$(1)"
    RM = rm -f "$(1)"
    EXE_EXT =
endif

SOURCES = $(wildcard $(SRCDIR)/*.c)
MAIN_SOURCES = $(filter-out $(SRCDIR)/test_main.c, $(SOURCES))
TEST_SOURCES = $(filter-out $(SRCDIR)/main.c, $(SOURCES))

MAIN_OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(MAIN_SOURCES))
TEST_OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(TEST_SOURCES))

TARGETS = $(BINDIR)/fractal$(EXE_EXT) $(BINDIR)/fractal_test$(EXE_EXT)

all: release

release: CFLAGS += $(RELEASE_FLAGS)
release: dirs $(BINDIR)/fractal$(EXE_EXT)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: dirs $(BINDIR)/fractal$(EXE_EXT) $(BINDIR)/fractal_test$(EXE_EXT)

dirs:
	@$(call MKDIR,$(BUILDDIR))
	@$(call MKDIR,$(BINDIR))

$(BINDIR)/fractal$(EXE_EXT): $(MAIN_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)/fractal_test$(EXE_EXT): $(TEST_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(call RMDIR,$(BUILDDIR))
	@$(call RMDIR,$(BINDIR))
	@$(call RM,*.pgm)

format:
	clang-format -i $(SRCDIR)/*.c $(SRCDIR)/*.h

test: debug
	$(BINDIR)/fractal_test$(EXE_EXT)

.PHONY: all release debug dirs clean format test