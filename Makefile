# Specify compiler, most cases it should be gcc
CC = gcc

# Compiler Flags
CFLAGS = -g -Wall 

DEPENDENCIES = serial_oper.c jpeg_writer.c
SRC_TEST = test_port.c
SRC_ISSUER = picture_issuer.c
SRC_RECEIVER = picture_receiv.c

build_receiver:
	$(CC) $(CFLAGS) -o $(basename $(SRC_RECEIVER)) $(SRC_RECEIVER) $(DEPENDENCIES)

build_issuer:
	$(CC) $(CFLAGS) -o  $(basename $(SRC_ISSUER)) $(SRC_ISSUER) $(DEPENDENCIES)

build_test:
	$(CC) $(CFLAGS) -o $(basename $(SRC_TEST)) $(SRC_TEST) $(DEPENDENCIES)

clean:
	rm $(OUTNAME_TEST) $(OUTNAME_ISSUER)
