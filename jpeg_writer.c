#include "jpeg_writer.h"

void write_jpg(char * filename, jpg_data * data)
{
	if (data->size > 0)
	{
	FILE *fp;
	fp = fopen(filename, "w+");
	if (fp)
	{
	int bytes_written = fwrite(data->bytes, sizeof(char), data->size,fp);
	fclose(fp);
	printf("\n Wrote %d bytes\n", bytes_written);
	}
	else
	{
		printf("\nunable to write file\n");
	}	
	}
}

void open_jpg(char * filename, jpg_data *data)
{
	FILE * fp;
	long size;
	fp = fopen(filename, "r");
	if (fp)
	{
		printf("open file successfully\n");
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		printf("size of file: %d\n", size);
		data->bytes = malloc(sizeof(char)*size);
		data->size = fread(data->bytes, sizeof(char), size, fp);
		printf("size of data written to struct: %d\n", data->size);
		fclose(fp);
	}
	else
		printf("failed to open file");
}
