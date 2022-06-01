/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "STM32F1.h"
#include "TinyObj.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void STM32F1_ADCMethod(PikaObj *self, Args *args){
    Arg* res = STM32F1_ADC(self);
    method_returnArg(args, res);
}

void STM32F1_GPIOMethod(PikaObj *self, Args *args){
    Arg* res = STM32F1_GPIO(self);
    method_returnArg(args, res);
}

void STM32F1_IICMethod(PikaObj *self, Args *args){
    Arg* res = STM32F1_IIC(self);
    method_returnArg(args, res);
}

void STM32F1_PWMMethod(PikaObj *self, Args *args){
    Arg* res = STM32F1_PWM(self);
    method_returnArg(args, res);
}

void STM32F1_TimeMethod(PikaObj *self, Args *args){
    Arg* res = STM32F1_Time(self);
    method_returnArg(args, res);
}

void STM32F1_UARTMethod(PikaObj *self, Args *args){
    Arg* res = STM32F1_UART(self);
    method_returnArg(args, res);
}

void STM32F1_lowLevelMethod(PikaObj *self, Args *args){
    Arg* res = STM32F1_lowLevel(self);
    method_returnArg(args, res);
}

PikaObj *New_STM32F1(Args *args){
    PikaObj *self = New_TinyObj(args);
    class_defineConstructor(self, "ADC()->any", STM32F1_ADCMethod);
    class_defineConstructor(self, "GPIO()->any", STM32F1_GPIOMethod);
    class_defineConstructor(self, "IIC()->any", STM32F1_IICMethod);
    class_defineConstructor(self, "PWM()->any", STM32F1_PWMMethod);
    class_defineConstructor(self, "Time()->any", STM32F1_TimeMethod);
    class_defineConstructor(self, "UART()->any", STM32F1_UARTMethod);
    class_defineConstructor(self, "lowLevel()->any", STM32F1_lowLevelMethod);
    return self;
}

