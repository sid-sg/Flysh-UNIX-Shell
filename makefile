# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Define the target executable
TARGET = flysh

# Define the source and object files
SRCS = main.c
OBJS = main.o

# Default rule to build the target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile the source file into an object file
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

# Rule to clean up the build directory
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the shell
.PHONY: run
run: $(TARGET)
	./$(TARGET)
