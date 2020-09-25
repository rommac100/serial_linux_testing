#ifndef serial_oper
#define serial_oper

//libraries needed for basic serial manipulation
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

#define DEFAULT_SERIAL_PATH "/dev/ttyUSB0"
struct serial_device
{
	int serial_port;
	char* serial_path;
};

// sets up serial to allow for the given port to read and write
// param: char* = char * for the path to the serial port, int* for the serial_port, struct termios* for the serial_settings
// return: the error code that it exited on
int setup_serial(struct serial_device*, struct termios*);

// writes a byte to the data_line
// param: int* for the serial_port int pointer (address), char* for the data pointer
// return: error code from writing process
int write_byte_serial(struct serial_device*, char*);
char read_byte_serial(struct serial_device*, char);
void close_port_serial(struct serial_device*);



#endif