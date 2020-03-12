/*
 *
 * Header file for the host/camera operator in the serial camera exchange process. 
 * This file will contain various MACROS and defintions for the different commands that will be usable. When requesting information from the host end.
*/
#ifndef serial_command
#define serial_command

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

/*
 * Arbitrary Command Constants listed below
 * Note that these can be changed
*/

#define TAKE_PIC 0x05 
#define REQ_PIC 0x09
#define TEST_COMM 0x02 // A test protocol command
#define STOP_TRANS 0xFF
#define DEFAULT_BUFFER_SIZE 4 //effectively the size for 2'x00 8 bit hexadecimal number
/*
 * Current Main Serial Device Paths
 */
#define CAMERA_PATH "/dev/ttyS0"
#define XBEE_PATH "/dev/ttyUSB0"
#define BUFF_FILE "buff.jpg"

int take_pic(char*);

int send_buff_pic();

int parse_serial_command(int);

void test_command(); //simple test_command function will output simple printf stating received command for now

void setup_serial_struct(struct termios*, int*); 
void setup_serial_struct_write(struct termios*,int*);

int start_listener(char *); // takes serial_path as inpu

typedef union serialized_data{
	unsigned int com_int;
	char com_char[4];
} serial_data;



#endif
