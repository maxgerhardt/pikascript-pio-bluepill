/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __PikaStdDevice_UART__H
#define __PikaStdDevice_UART__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_PikaStdDevice_UART(Args *args);

void PikaStdDevice_UART___init__(PikaObj *self);
void PikaStdDevice_UART_disable(PikaObj *self);
void PikaStdDevice_UART_enable(PikaObj *self);
void PikaStdDevice_UART_init(PikaObj *self);
void PikaStdDevice_UART_platformDisable(PikaObj *self);
void PikaStdDevice_UART_platformEnable(PikaObj *self);
void PikaStdDevice_UART_platformRead(PikaObj *self);
void PikaStdDevice_UART_platformWrite(PikaObj *self);
char* PikaStdDevice_UART_read(PikaObj *self, int length);
void PikaStdDevice_UART_setBaudRate(PikaObj *self, int baudRate);
void PikaStdDevice_UART_setId(PikaObj *self, int id);
void PikaStdDevice_UART_write(PikaObj *self, char* data);

#endif
