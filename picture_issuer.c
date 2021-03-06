#include "picture_issuer.h"
#include "jpeg_writer.h"

// argv: [1] = serial_path
int main (int argc, char** argv)
{
	char buffer;
	struct serial_device device;
	struct termios serial_settings;
	device.serial_path = argv[1];
	int failcode = setup_serial_baud(&device, &serial_settings, B38400);
	if (failcode !=0)
		return -1;

	while (buffer != EXIT)
	{
		read_serial(&device, &buffer, 1);
		printf("\nbuffer: %c\n", buffer);
		switch(buffer)
		{
			case SEND_PIC_BUFF:
				transmit_picture(&device, argc==3 ? argv[2] : DEFAULT_PICTURE);
			break;
			case TAKE_PIC:
				take_picture(DEFAULT_PICTURE);
			break;
		}
	}
	close_port_serial(&device);	
}

void transmit_picture(struct serial_device* device, char* img_path)
{
	printf("\n in transmit picture function\n");
	jpg_data jpg_file;
	open_jpg(DEFAULT_PICTURE, &jpg_file);
	char buff[8];
	printf("jpg_data size: %lu\n", jpg_file.size);
	sprintf(buff, "%lu",jpg_file.size);
	write_string_serial(device, buff,8);
	long i,j;
	long left_bytes = jpg_file.size-((jpg_file.size/MAX_SERIAL_TRANSFER)*MAX_SERIAL_TRANSFER);
	printf("\n left_bytes: %lu", left_bytes);
	char img_buff[MAX_SERIAL_TRANSFER];
	for (i=0; i < jpg_file.size/MAX_SERIAL_TRANSFER; i++)
	{
		for (j=0; j< MAX_SERIAL_TRANSFER; j++)
			img_buff[j] = jpg_file.bytes[(i*MAX_SERIAL_TRANSFER)+j];
	write_string_serial(device,img_buff,MAX_SERIAL_TRANSFER);
	}
	printf("\n printed bulk of the file\n");
	if (left_bytes != 0)
	{
	printf("bytes left, %d\n", left_bytes);
	for (i=0; i<left_bytes; i++)
	{
		printf("i in left_bytes: %d\n",i);
		img_buff[i] = jpg_file.bytes[((jpg_file.size/MAX_SERIAL_TRANSFER)*MAX_SERIAL_TRANSFER)+i];
	}
	write_string_serial(device,img_buff,left_bytes);
	}
}
void take_picture(char * path)
{
	printf("\n in take picture function\n");
}
