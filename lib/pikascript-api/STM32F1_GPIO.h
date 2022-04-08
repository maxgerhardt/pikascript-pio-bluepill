/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __STM32F1_GPIO__H
#define __STM32F1_GPIO__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_STM32F1_GPIO(Args *args);

void STM32F1_GPIO_platformDisable(PikaObj *self);
void STM32F1_GPIO_platformEnable(PikaObj *self);
void STM32F1_GPIO_platformHigh(PikaObj *self);
void STM32F1_GPIO_platformLow(PikaObj *self);
void STM32F1_GPIO_platformRead(PikaObj *self);
void STM32F1_GPIO_platformSetMode(PikaObj *self);

#endif
