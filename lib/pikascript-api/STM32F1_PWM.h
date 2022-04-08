/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __STM32F1_PWM__H
#define __STM32F1_PWM__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_STM32F1_PWM(Args *args);

void STM32F1_PWM_platformEnable(PikaObj *self);
void STM32F1_PWM_platformSetDuty(PikaObj *self);
void STM32F1_PWM_platformSetFrequency(PikaObj *self);

#endif
