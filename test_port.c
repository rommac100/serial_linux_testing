#include "serial_oper.h"
#include <stdio.h>
int main(int argc, char** argv)
{
	printf("testing\n");
	struct termios serial_settings;	
	struct serial_device device;
	device.serial_path = DEFAULT_SERIAL_PATH;
	int err_code = setup_serial_baud(&device, &serial_settings, B57600);
	char buff[4] = {0x56, 0x00, 0x26, 0x00}; 
	write_string_serial(&device, buff,4);
	read_serial(&device, buff,4);

	close_port_serial(&device);
	
}
