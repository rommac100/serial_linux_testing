#include "serial_oper.h"
#include <stdio.h>
int main(int argc, char** argv)
{
	printf("testing\n");
	struct termios serial_settings;	
	struct serial_device device;
	device.serial_path = DEFAULT_SERIAL_PATH;
	int err_code = setup_serial(&device, &serial_settings);	
	write_byte_serial(&device, "b");
	write_string_serial(&device, "test", 4);
	char data[3];
	read_serial(&device,data, 3);
	close_port_serial(&device);
}
