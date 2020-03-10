/*
 * Effectively acts as the transmistter, the requester of photos to be streamed back to it.
 * Follows the same commands as listed in serial_command.h
 *
 *
 * Product of SDSL:
 * Author: Christopher McCormick
 */

#include "serial_trans.h"

int main(int argc, char **argv)
{
 	return start_transmitter(argc ==2 ? argv[1]:XBEE_PATH_TRANS);	
}

//returns 1 if an error occurs with either port_config or opening serial bus
int start_transmitter(char* xbee_path)
{
	fd = open(xbee_path, O_RDWR | O_NOCTTY);

	if (fd ==-1)
	{
		printf("\nError when opening ttyUSB1\n");
		return 1;
	}

	struct termios port_config;
	setup_serial_trans(&port_config, &fd);
	if ((tcsetattr(fd,TCSANOW,&port_config)) !=0)
	{
		printf("\n Error ! in setttings desired attributes\n");
		return 1;
	}
	else	
		printf("\n BAUDRATE = B9600, \n Stop Bits = 1 \n Parity = none\n");
	tcflush(fd, TCIFLUSH); // Discards teh old data in the Rx Buffer

	char read_buffer[10];
	int bytes_read = 0;

	scanf(" %s", read_buffer);
	while(strtol(read_buffer, NULL, 16) != STOP_TRANS) 
	{
		parse_input(strtol(read_buffer, NULL, 16));
		printf("\n Enter a command \n");
		scanf(" %s", read_buffer);
	}
	close(fd);
	return 0;
}

void parse_input(int input)
{
	switch(input)
	{
		case TAKE_PIC: 
			take_pic_trans();
		break;
		case TEST_COMM:
			test_comm_trans();	
		break;
		case REQ_PIC:
			req_pic_trans();
		break;
		default:
			printf("\nPlease enter a valid command. See header file serial_command.h for valid options \n");
		break;
	}
}

void req_pic_trans()
{
	serial_data data;
        data.com_int = REQ_PIC;
	send_4bit_command(&data);
}

void test_comm_trans()
{
	serial_data data;
	data.com_int = TEST_COMM;
	send_4bit_command(&data);
}

void send_4bit_command(serial_data * data)
{
	tcflush(fd, TCIFLUSH);
	int bytes_written = 0;

	bytes_written = write(fd,data->com_char, sizeof(data->com_char));

	printf("\n %s written to TTYUSB0", data->com_char);
	printf("\n %d Bytes written to ttyUSB0", bytes_written);
}

void take_pic_trans()
{
	serial_data data;
	data.com_int = TAKE_PIC;
	send_4bit_command(&data);
}

void setup_serial_trans(struct termios* port_config, int* serial_port)
{
	tcgetattr(*serial_port, port_config); // store current attributes of the serial port into the port_config struct
	cfsetispeed(port_config, B9600);
	cfsetospeed(port_config, B9600);

	port_config->c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
	port_config->c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	port_config->c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
	port_config->c_cflag |=  CS8;      /* Set the data bits = 8                                 */
	
	port_config->c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
	port_config->c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		
	port_config->c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
	port_config->c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

	port_config->c_oflag &= ~OPOST;/*No Output Processing*/
}

