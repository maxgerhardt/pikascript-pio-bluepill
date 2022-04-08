/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __STM32F1_UART__H
#define __STM32F1_UART__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_STM32F1_UART(Args *args);

void STM32F1_UART_platformEnable(PikaObj *self);
void STM32F1_UART_platformRead(PikaObj *self);
void STM32F1_UART_platformWrite(PikaObj *self);

#endif
