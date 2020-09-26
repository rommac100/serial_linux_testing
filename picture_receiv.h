#ifndef picture_receiv
#define picture_receiv

#include "serial_oper.h"
#include "serial_commands.h"
#include <string.h>
#include "jpeg_writer.h"

void receive_pic_buff(struct serial_device*, char*);
void send_take_pic(struct serial_device*);

#endif
