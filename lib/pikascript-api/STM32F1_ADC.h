/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __STM32F1_ADC__H
#define __STM32F1_ADC__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_STM32F1_ADC(Args *args);

void STM32F1_ADC_platformEnable(PikaObj *self);
void STM32F1_ADC_platformRead(PikaObj *self);

#endif
