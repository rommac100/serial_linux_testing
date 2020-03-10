/*
 * Effectively a bit of code that acts as the camera end and listens for certain commands that pertain to submitting various bits of information.
 * In theory, this c program is independent of the architecture that is used but will be tested on both rpi1, Beagle bone black & and 64bit architecture.
 *
 *
 * Product of SDSL:
 * Author: Christopher McCormick
 */

#include "serial_command.h"

int main(int argc, char **argv)
{
	start_listener(argc==2? argv[1] :XBEE_PATH);

	return 0;
}
int start_listener(char *xbee_path)
{
	int fd = open(XBEE_PATH, O_RDWR | O_NOCTTY);

	if (fd ==-1)
	{
		printf("\nError when opening ttyUSB1\n");
		return 1;
	}

	struct termios port_config;
	setup_serial_struct(&port_config, &fd);
	if ((tcsetattr(fd,TCSANOW,&port_config)) !=0)
		printf("\n Error ! in setttings desired attributes\n");
	else	
		printf("\n BAUDRATE = B9600, \n Stop Bits = 1 \n Parity = none\n");
	tcflush(fd, TCIFLUSH); // Discards teh old data in the Rx Buffer

	char read_buffer[3];
	int bytes_read = 0;

	bytes_read  =read(fd,&read_buffer,3);
	while(atoi(read_buffer) != STOP_TRANS) 
	{
		printf("atoi value: %d\n",atoi(read_buffer));
		printf("\n\n Bytes Rxed - %d  - Byte Value: <%s> \n\n",bytes_read, read_buffer);
		parse_serial_command(atoi(read_buffer));

		bytes_read  =read(fd,&read_buffer,3);
	}
	close(fd);
}

void setup_serial_struct(struct termios* port_config, int* serial_port)
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
		
	/* Setting Time outs */
	port_config->c_cc[VMIN] = 10; /* Read at least 10 characters */
	port_config->c_cc[VTIME] = 0; /* Wait indefinetly   */
}

int send_buff_pic()
{
	return 0;
}

int take_pic(char * camera_serial)
{
	return 0;
}

void test_command()
{
	printf("Valid Command of %d Received\n",TEST_COMM);
}

int parse_serial_command(int command)
{
	switch (command)
	{
		case TAKE_PIC:
		take_pic(CAMERA_PATH);
		break;
		case REQ_PIC:
		send_buff_pic();
		break;
		case TEST_COMM:
		test_command();
		break;
		case STOP_TRANS:
		printf("STOP TRANSMISSION CAUGHT\n");
		break;
		default:
		printf("\n Invalid command. Please enter a valid command\n");
		break;
	}
	return 0;
}
