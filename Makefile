# Defining compiler variables and compilation options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread

# Defining a variable for the name of the executable file
TARGET = file_search_app

# Defining a list of object files
OBJS = main.o file_search_lib.o

# The main goal for building an application
$(TARGET):	$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rules for compiling each of the object files
main.o: main.c file_search_lib.h
	$(CC) $(CFLAGS) -c main.c

file_search_lib.o: file_search_lib.c file_search_lib.h
	$(CC) $(CFLAGS) -c file_search_lib.c

# Removal of object files and executable file
clean:
	rm -f $(OBJS) $(TARGET)