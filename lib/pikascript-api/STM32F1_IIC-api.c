/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "STM32F1_IIC.h"
#include "PikaStdDevice_IIC.h"
#include "STM32F1_GPIO.h"
#include "STM32F1_GPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void STM32F1_IIC_platformEnableMethod(PikaObj *self, Args *args){
    STM32F1_IIC_platformEnable(self);
}

void STM32F1_IIC_platformReadMethod(PikaObj *self, Args *args){
    STM32F1_IIC_platformRead(self);
}

void STM32F1_IIC_platformWriteMethod(PikaObj *self, Args *args){
    STM32F1_IIC_platformWrite(self);
}

PikaObj *New_STM32F1_IIC(Args *args){
    PikaObj *self = New_PikaStdDevice_IIC(args);
    obj_newObj(self, "SCL", "STM32F1_GPIO", New_STM32F1_GPIO);
    obj_newObj(self, "SDA", "STM32F1_GPIO", New_STM32F1_GPIO);
    class_defineMethod(self, "platformEnable()", STM32F1_IIC_platformEnableMethod);
    class_defineMethod(self, "platformRead()", STM32F1_IIC_platformReadMethod);
    class_defineMethod(self, "platformWrite()", STM32F1_IIC_platformWriteMethod);
    return self;
}

Arg *STM32F1_IIC(PikaObj *self){
    return obj_newObjInPackage(New_STM32F1_IIC);
}
