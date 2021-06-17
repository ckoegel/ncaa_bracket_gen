CC = gcc
CFLAGS = -g -Wall
TARGET = bracket

all: $(TARGET) $(TARGET2)

 $(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

 clean:
	$(RM) $(TARGET)

