CC = g++
CFLAGS = -g -Wall 
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp -l sqlite3

clean: 
	$(RM) $(TARGET) 