/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __STM32F1_lowLevel__H
#define __STM32F1_lowLevel__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_STM32F1_lowLevel(Args *args);

int STM32F1_lowLevel_readPin(PikaObj *self, char* pin);

#endif
