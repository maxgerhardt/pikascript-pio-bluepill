/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "STM32F1_lowLevel.h"
#include "TinyObj.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void STM32F1_lowLevel_readPinMethod(PikaObj *self, Args *args){
    char* pin = args_getStr(args, "pin");
    int res = STM32F1_lowLevel_readPin(self, pin);
    method_returnInt(args, res);
}

PikaObj *New_STM32F1_lowLevel(Args *args){
    PikaObj *self = New_TinyObj(args);
    class_defineMethod(self, "readPin(pin:str)->int", STM32F1_lowLevel_readPinMethod);
    return self;
}

Arg *STM32F1_lowLevel(PikaObj *self){
    return obj_newObjInPackage(New_STM32F1_lowLevel);
}
