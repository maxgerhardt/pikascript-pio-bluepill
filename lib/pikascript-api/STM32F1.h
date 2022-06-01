/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __STM32F1__H
#define __STM32F1__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_STM32F1(Args *args);

Arg* STM32F1_ADC(PikaObj *self);
Arg* STM32F1_GPIO(PikaObj *self);
Arg* STM32F1_IIC(PikaObj *self);
Arg* STM32F1_PWM(PikaObj *self);
Arg* STM32F1_Time(PikaObj *self);
Arg* STM32F1_UART(PikaObj *self);
Arg* STM32F1_lowLevel(PikaObj *self);

#endif
