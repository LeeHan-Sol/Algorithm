CC = gcc
SOURCES = Node.c Item.c List.c Tree.c main.c
OBJECTS = Node.o Item.o List.o Tree.o main.o
CFLAGS = -I -W -Wall -g
TARGET = countNodeOnTree

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS)

clean :
	rm -f *.o $(TARGET)
