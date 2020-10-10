#include "picture_receiv.h"

//argv[1] == serial_path
int main (int argc, char** argv)
{
	char buff;

	struct serial_device device;
	device.serial_path = argv[1];
	struct termios serial_settings;
	int error = setup_serial_baud(&device, &serial_settings, B38400);
	if (error != 0)
		return error;

	while (buff != EXIT)
	{
		scanf(" %c",&buff);
		printf("receive: %c\n", buff);
		switch(buff)
		{
			case SEND_PIC_BUFF:
				receive_pic_buff(&device, "");
			break;
			case TAKE_PIC:
				send_take_pic(&device);
			break;
		}
	}
	buff = 'E';
	write_byte_serial(&device, &buff); //used to shutdown the receiver
}


// Order for transmission:
// - send receive Command (ascii 'S')
// - receive picture size in (must be less than 4 bytes)
// - receive picture by MAX_SERIAL_TRANSFER bytes increments (until it is no longer MAX_SERIAL_TRANSFER bytes and then just receive the last proportion of bytes)
void receive_pic_buff(struct serial_device* device, char* path)
{
	jpg_data img_data;
	char t = 'S';
	char pic_size[8];
	write_byte_serial(device, &t);
	read_serial(device, pic_size,8);
	sscanf(pic_size, "%lu", &img_data.size);
	printf("\n size: %lu", img_data.size);
	img_data.bytes = (char *) malloc(sizeof(char)*img_data.size); 
	unsigned long i,j;
	unsigned long bytes_left = img_data.size-(img_data.size/MAX_SERIAL_TRANSFER)*MAX_SERIAL_TRANSFER;
	char buff_pic[MAX_SERIAL_TRANSFER];

	unsigned long div_size = img_data.size/MAX_SERIAL_TRANSFER;
	printf("\n div_size: %lu\n", div_size);

	for (i=0; i< img_data.size/MAX_SERIAL_TRANSFER; i++)
	{
		char buff_pic[MAX_SERIAL_TRANSFER];
		read_serial(device, buff_pic, MAX_SERIAL_TRANSFER);
		for (j= 0; j<MAX_SERIAL_TRANSFER; j++)
			img_data.bytes[j+(i*MAX_SERIAL_TRANSFER)] = buff_pic[j]; 
	}
	if (bytes_left !=0)
	{
		read_serial(device, buff_pic, bytes_left);
		for (j=0; j<bytes_left; j++)
			img_data.bytes[j+((img_data.size/MAX_SERIAL_TRANSFER)*MAX_SERIAL_TRANSFER)] = buff_pic[j];
	}

	write_jpg("/home/rommac/serial_linux_testing/output.jpg", &img_data);
	free(img_data.bytes);
}

void send_take_pic(struct serial_device* device)
{
	char t = 'T';
	write_byte_serial(device, &t);
}
