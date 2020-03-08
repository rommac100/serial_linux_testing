#include "jpeg_writer.h"
int main()
{

	export_image("test.jpg");	
}

void export_image(char *path)
{
	XInfo_t xinfo = getXInfo(":0");
	XImage* screen_shot = takeScreenshot(xinfo,path);
}
