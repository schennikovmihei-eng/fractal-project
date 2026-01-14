CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG
LDFLAGS = -lm

SRCDIR = src
BUILDDIR = build
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
MAIN_SOURCES = $(filter-out $(SRCDIR)/test_main.c, $(SOURCES))
TEST_SOURCES = $(filter-out $(SRCDIR)/main.c, $(SOURCES))

MAIN_OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(MAIN_SOURCES))
TEST_OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(TEST_SOURCES))

all: release

release: CFLAGS += $(RELEASE_FLAGS)
release: dirs $(BINDIR)/fractal.exe

debug: CFLAGS += $(DEBUG_FLAGS)
debug: dirs $(BINDIR)/fractal.exe $(BINDIR)/fractal_test.exe

dirs:
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(BINDIR)/fractal.exe: $(MAIN_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BINDIR)/fractal_test.exe: $(TEST_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist $(BUILDDIR) rmdir /S /Q $(BUILDDIR)
	@if exist $(BINDIR) rmdir /S /Q $(BINDIR)
	@del *.pgm 2>nul

format:
	clang-format -i $(SRCDIR)/*.c $(SRCDIR)/*.h

test: debug
	$(BINDIR)/fractal_test.exe

.PHONY: all release debug dirs clean format test