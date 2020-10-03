#ifndef picture_issuer
#define picture_issuer

#include "serial_oper.h"
#include "serial_commands.h"
#include "jpeg_writer.h"

#define DEFAULT_PICTURE "/home/rommac/serial_linux_testing/thumbnail.jpg"

int start_receiver(char*);

void transmit_picture(struct serial_device*, char*);
void take_picture(char*);

#endif
