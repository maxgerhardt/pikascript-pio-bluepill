/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "STM32F1_GPIO.h"
#include "PikaStdDevice_GPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void STM32F1_GPIO_platformDisableMethod(PikaObj *self, Args *args){
    STM32F1_GPIO_platformDisable(self);
}

void STM32F1_GPIO_platformEnableMethod(PikaObj *self, Args *args){
    STM32F1_GPIO_platformEnable(self);
}

void STM32F1_GPIO_platformHighMethod(PikaObj *self, Args *args){
    STM32F1_GPIO_platformHigh(self);
}

void STM32F1_GPIO_platformLowMethod(PikaObj *self, Args *args){
    STM32F1_GPIO_platformLow(self);
}

void STM32F1_GPIO_platformReadMethod(PikaObj *self, Args *args){
    STM32F1_GPIO_platformRead(self);
}

void STM32F1_GPIO_platformSetModeMethod(PikaObj *self, Args *args){
    STM32F1_GPIO_platformSetMode(self);
}

PikaObj *New_STM32F1_GPIO(Args *args){
    PikaObj *self = New_PikaStdDevice_GPIO(args);
    class_defineMethod(self, "platformDisable()", STM32F1_GPIO_platformDisableMethod);
    class_defineMethod(self, "platformEnable()", STM32F1_GPIO_platformEnableMethod);
    class_defineMethod(self, "platformHigh()", STM32F1_GPIO_platformHighMethod);
    class_defineMethod(self, "platformLow()", STM32F1_GPIO_platformLowMethod);
    class_defineMethod(self, "platformRead()", STM32F1_GPIO_platformReadMethod);
    class_defineMethod(self, "platformSetMode()", STM32F1_GPIO_platformSetModeMethod);
    return self;
}

Arg *STM32F1_GPIO(PikaObj *self){
    return obj_newObjInPackage(New_STM32F1_GPIO);
}
