/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __STM32F1_IIC__H
#define __STM32F1_IIC__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_STM32F1_IIC(Args *args);

void STM32F1_IIC_platformEnable(PikaObj *self);
void STM32F1_IIC_platformRead(PikaObj *self);
void STM32F1_IIC_platformWrite(PikaObj *self);

#endif
