#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd;
	
	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);

	if (fd ==-1)
	{
		printf("\nError when opening ttyUSB0\n");
		return 1;
	}
	else
	printf("\nTTYUSB0 Opened fine\n");
	struct termios port_config; // allocating the port_config struct for serial bus
	tcgetattr(fd, &port_config); // store current attributes of the serial port into the port_config struct
	cfsetispeed(&port_config, B9600);
	cfsetospeed(&port_config, B9600);

	port_config.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
	port_config.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	port_config.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
	port_config.c_cflag |=  CS8;      /* Set the data bits = 8                                 */
	
	port_config.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
	port_config.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		
	port_config.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
	port_config.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

	port_config.c_oflag &= ~OPOST;/*No Output Processing*/
		
	/* Setting Time outs */
	port_config.c_cc[VMIN] = 10; /* Read at least 10 characters */
	port_config.c_cc[VTIME] = 0; /* Wait indefinetly   */
	if ((tcsetattr(fd,TCSANOW,&port_config)) !=0)
		printf("\n Error ! in setttings desired attributes\n");
	else	
		printf("\n BAUDRATE = B9600, \n Stop Bits = 1 \n Parity = none\n");
	tcflush(fd, TCIFLUSH); // Discards teh old data in the Rx Buffer

	char read_buffer[32];
	int bytes_read = 0;

	bytes_read  =read(fd,&read_buffer,32);
	printf("\n\n Bytes Rxed - %d\n\n",bytes_read);

	int i;
	for (i=0; i< bytes_read; i++)
		printf("%c", read_buffer[i]);

	close(fd);
	return 0;
}
