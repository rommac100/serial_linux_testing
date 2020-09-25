# Specify compiler, most cases it should be gcc
CC = gcc

# Compiler Flags
CFLAGS = -g -Wall 

SRC = serial_oper.c test_port.c
OUTNAME = test_serial

build:
	$(CC) $(CFLAGS) -o $(OUTNAME) $(SRC)

clean:
	rm $(OUTNAME)
