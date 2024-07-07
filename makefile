# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -g -Iinclude

# Define the directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Define the target executable
TARGET = $(BINDIR)/flysh

# Define the source and object files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Default rule to build the target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each source file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the build directory
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Rule to run the shell
.PHONY: run
run: $(TARGET)
	./$(TARGET)
