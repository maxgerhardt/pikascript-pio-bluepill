/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "STM32F1_Time.h"
#include "PikaStdDevice_Time.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void STM32F1_Time_sleep_msMethod(PikaObj *self, Args *args){
    int ms = args_getInt(args, "ms");
    STM32F1_Time_sleep_ms(self, ms);
}

void STM32F1_Time_sleep_sMethod(PikaObj *self, Args *args){
    int s = args_getInt(args, "s");
    STM32F1_Time_sleep_s(self, s);
}

PikaObj *New_STM32F1_Time(Args *args){
    PikaObj *self = New_PikaStdDevice_Time(args);
    class_defineMethod(self, "sleep_ms(ms:int)", STM32F1_Time_sleep_msMethod);
    class_defineMethod(self, "sleep_s(s:int)", STM32F1_Time_sleep_sMethod);
    return self;
}

Arg *STM32F1_Time(PikaObj *self){
    return obj_newObjInPackage(New_STM32F1_Time);
}
