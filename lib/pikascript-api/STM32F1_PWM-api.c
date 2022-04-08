/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "STM32F1_PWM.h"
#include "PikaStdDevice_PWM.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void STM32F1_PWM_platformEnableMethod(PikaObj *self, Args *args){
    STM32F1_PWM_platformEnable(self);
}

void STM32F1_PWM_platformSetDutyMethod(PikaObj *self, Args *args){
    STM32F1_PWM_platformSetDuty(self);
}

void STM32F1_PWM_platformSetFrequencyMethod(PikaObj *self, Args *args){
    STM32F1_PWM_platformSetFrequency(self);
}

PikaObj *New_STM32F1_PWM(Args *args){
    PikaObj *self = New_PikaStdDevice_PWM(args);
    class_defineMethod(self, "platformEnable()", STM32F1_PWM_platformEnableMethod);
    class_defineMethod(self, "platformSetDuty()", STM32F1_PWM_platformSetDutyMethod);
    class_defineMethod(self, "platformSetFrequency()", STM32F1_PWM_platformSetFrequencyMethod);
    return self;
}

Arg *STM32F1_PWM(PikaObj *self){
    return obj_newObjInPackage(New_STM32F1_PWM);
}
