/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "STM32F1_UART.h"
#include "PikaStdDevice_UART.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void STM32F1_UART_platformEnableMethod(PikaObj *self, Args *args){
    STM32F1_UART_platformEnable(self);
}

void STM32F1_UART_platformReadMethod(PikaObj *self, Args *args){
    STM32F1_UART_platformRead(self);
}

void STM32F1_UART_platformWriteMethod(PikaObj *self, Args *args){
    STM32F1_UART_platformWrite(self);
}

PikaObj *New_STM32F1_UART(Args *args){
    PikaObj *self = New_PikaStdDevice_UART(args);
    class_defineMethod(self, "platformEnable()", STM32F1_UART_platformEnableMethod);
    class_defineMethod(self, "platformRead()", STM32F1_UART_platformReadMethod);
    class_defineMethod(self, "platformWrite()", STM32F1_UART_platformWriteMethod);
    return self;
}

Arg *STM32F1_UART(PikaObj *self){
    return obj_newObjInPackage(New_STM32F1_UART);
}
