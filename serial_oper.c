#include "serial_oper.h"


int setup_serial_baud(struct serial_device* device, struct termios* serial_settings, unsigned int baud)
{
	device->serial_port = open(device->serial_path, O_RDWR);	

	if (device->serial_port < 0)
	{
		printf("Error %i from open: \n", errno);
		return errno;
	}

	// serial_settings are configured below and assigned into the serial_settings struct
	// More or less the config options are BAUD=9600, no parity, 1 stop bit, clear mask, data bits =8, no hardware flow control,
	// Enable receiving, disable XON/XOFF flow control on both in and out (rx, tx), and enable non cannonical mode
	// Additionally, I have the read parameters for reading to be Read at least 10 characters and waiting time does not have a fixed time.
	tcgetattr(device->serial_port, serial_settings); // grab the current serial_settings that are in the serial configurator
	cfsetispeed(serial_settings, baud);
	cfsetospeed(serial_settings, baud);

	serial_settings->c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
	serial_settings->c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	serial_settings->c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
	serial_settings->c_cflag |=  CS8;      /* Set the data bits = 8                                 */

	serial_settings->c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
	serial_settings->c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		
	serial_settings->c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
	serial_settings->c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

	serial_settings->c_oflag &= ~OPOST;/*No Output Processing*/
		
	/* Setting Time outs */
	serial_settings->c_cc[VMIN] = 105; /* Read at least 100  characters (or when the specified buffer in the read command is full)*/
	serial_settings->c_cc[VTIME] = 0; /* Wait 10 deciseconds   */

	// apply struct settings and see if an error occurs
	if ((tcsetattr(device->serial_port,TCSANOW,serial_settings)) !=0)
	{
		printf("\n Error ! in setttings desired attributes\n");
		return 1;
	}
	else	
		printf("\n BAUDRATE = %u, \n Stop Bits = 1 \n Parity = none\n", baud);
	tcflush(device->serial_port, TCIFLUSH); // Discards the old data in the Rx Buffer
	return 0;
}


//has BAUD just set to B9600
int setup_serial(struct serial_device* device, struct termios* serial_settings)
{
	return setup_serial_baud(device,serial_settings,B9600);
}

int write_byte_serial(struct serial_device* device, char* data)
{
	tcflush(device->serial_port, TCIFLUSH); //clean out the write buffer
	int bytes_written = 0;
	bytes_written = write(device->serial_port,data, 1);

	printf("\n %d Bytes written to %s", bytes_written, device->serial_path);

	return 0;
}

int write_string_serial(struct serial_device* device, char* data, int data_size)
{
	tcflush(device->serial_port, TCIFLUSH); //clean out the write buffer
	int bytes_written = 0;
	bytes_written = write(device->serial_port,data, data_size);

	printf("\n %d Bytes written to %s", bytes_written, device->serial_path);

	return 0;
}

int read_serial(struct serial_device* device, char* data, int buff_length)
{
	int bytes_read = read(device->serial_port, data, buff_length);
	printf("\n (%i bytes) read from %s", bytes_read, device->serial_path);
	return bytes_read;
}

void close_port_serial(struct serial_device* device) {close(device->serial_port);}

