/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "STM32F1_ADC.h"
#include "PikaStdDevice_ADC.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void STM32F1_ADC_platformEnableMethod(PikaObj *self, Args *args){
    STM32F1_ADC_platformEnable(self);
}

void STM32F1_ADC_platformReadMethod(PikaObj *self, Args *args){
    STM32F1_ADC_platformRead(self);
}

PikaObj *New_STM32F1_ADC(Args *args){
    PikaObj *self = New_PikaStdDevice_ADC(args);
    class_defineMethod(self, "platformEnable()", STM32F1_ADC_platformEnableMethod);
    class_defineMethod(self, "platformRead()", STM32F1_ADC_platformReadMethod);
    return self;
}

Arg *STM32F1_ADC(PikaObj *self){
    return obj_newObjInPackage(New_STM32F1_ADC);
}
