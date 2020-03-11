/*
 *
 * Header file for the Transmitter/beagle requester of images side.
 * Most commands Macros will be located in the other header file serial_command.h
 * 
 * Product of SDSL:
 * Author: Christopher McCormick
 */ 
#ifndef serial_trans
#define serial_trans

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include "serial_command.h"

/*
 * Arbitrary Command Constants listed below
 * Note that these can be changed
*/

/*
 * Current Main Serial Device Paths
 */
#define XBEE_PATH_TRANS "/dev/ttyUSB0" //update this as needed. Eventually will add a manual way of passing the path

int fd; // global variable for serial buffer

int start_transmitter(char*);
void parse_input(int);


void req_pic_trans();
void take_pic_trans();
void test_comm_trans(); // A test communication function. Somewhat similar to just asking for a model number of a device.

void setup_serial_trans(struct termios*, int*);


void send_4bit_command(serial_data *);

#endif
