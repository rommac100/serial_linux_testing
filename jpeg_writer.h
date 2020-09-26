#ifndef jpeg_writer
#define jpeg_writer
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

typedef struct jpg{
	unsigned long size;
	char *bytes;
} jpg_data;

void open_jpg(char *, jpg_data*);
void write_jpg(char *, jpg_data*);

#define TEST_FILE "test_serial_img.jpg"

#endif
