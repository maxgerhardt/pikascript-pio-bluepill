/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "PikaStdDevice_CAN.h"
#include "TinyObj.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void PikaStdDevice_CAN___init__Method(PikaObj *self, Args *args){
    PikaStdDevice_CAN___init__(self);
}

void PikaStdDevice_CAN_addFilterMethod(PikaObj *self, Args *args){
    int hdr = args_getInt(args, "hdr");
    int id = args_getInt(args, "id");
    int ide = args_getInt(args, "ide");
    int mask = args_getInt(args, "mask");
    int mode = args_getInt(args, "mode");
    int rtr = args_getInt(args, "rtr");
    PikaStdDevice_CAN_addFilter(self, hdr, id, ide, mask, mode, rtr);
}

void PikaStdDevice_CAN_disableMethod(PikaObj *self, Args *args){
    PikaStdDevice_CAN_disable(self);
}

void PikaStdDevice_CAN_enableMethod(PikaObj *self, Args *args){
    PikaStdDevice_CAN_enable(self);
}

void PikaStdDevice_CAN_platformDisableMethod(PikaObj *self, Args *args){
    PikaStdDevice_CAN_platformDisable(self);
}

void PikaStdDevice_CAN_platformEnableMethod(PikaObj *self, Args *args){
    PikaStdDevice_CAN_platformEnable(self);
}

void PikaStdDevice_CAN_platformReadMethod(PikaObj *self, Args *args){
    PikaStdDevice_CAN_platformRead(self);
}

void PikaStdDevice_CAN_platformWriteMethod(PikaObj *self, Args *args){
    PikaStdDevice_CAN_platformWrite(self);
}

void PikaStdDevice_CAN_readMethod(PikaObj *self, Args *args){
    int length = args_getInt(args, "length");
    char* res = PikaStdDevice_CAN_read(self, length);
    method_returnStr(args, res);
}

void PikaStdDevice_CAN_setBaudRateMethod(PikaObj *self, Args *args){
    int baudRate = args_getInt(args, "baudRate");
    PikaStdDevice_CAN_setBaudRate(self, baudRate);
}

void PikaStdDevice_CAN_setIdMethod(PikaObj *self, Args *args){
    int id = args_getInt(args, "id");
    PikaStdDevice_CAN_setId(self, id);
}

void PikaStdDevice_CAN_setModeMethod(PikaObj *self, Args *args){
    char* mode = args_getStr(args, "mode");
    PikaStdDevice_CAN_setMode(self, mode);
}

void PikaStdDevice_CAN_setNameMethod(PikaObj *self, Args *args){
    char* name = args_getStr(args, "name");
    PikaStdDevice_CAN_setName(self, name);
}

void PikaStdDevice_CAN_writeMethod(PikaObj *self, Args *args){
    char* data = args_getStr(args, "data");
    PikaStdDevice_CAN_write(self, data);
}

PikaObj *New_PikaStdDevice_CAN(Args *args){
    PikaObj *self = New_TinyObj(args);
    class_defineMethod(self, "__init__()", PikaStdDevice_CAN___init__Method);
    class_defineMethod(self, "addFilter(id:int,ide:int,rtr:int,mode:int,mask:int,hdr:int)", PikaStdDevice_CAN_addFilterMethod);
    class_defineMethod(self, "disable()", PikaStdDevice_CAN_disableMethod);
    class_defineMethod(self, "enable()", PikaStdDevice_CAN_enableMethod);
    class_defineMethod(self, "platformDisable()", PikaStdDevice_CAN_platformDisableMethod);
    class_defineMethod(self, "platformEnable()", PikaStdDevice_CAN_platformEnableMethod);
    class_defineMethod(self, "platformRead()", PikaStdDevice_CAN_platformReadMethod);
    class_defineMethod(self, "platformWrite()", PikaStdDevice_CAN_platformWriteMethod);
    class_defineMethod(self, "read(length:int)->str", PikaStdDevice_CAN_readMethod);
    class_defineMethod(self, "setBaudRate(baudRate:int)", PikaStdDevice_CAN_setBaudRateMethod);
    class_defineMethod(self, "setId(id:int)", PikaStdDevice_CAN_setIdMethod);
    class_defineMethod(self, "setMode(mode:str)", PikaStdDevice_CAN_setModeMethod);
    class_defineMethod(self, "setName(name:str)", PikaStdDevice_CAN_setNameMethod);
    class_defineMethod(self, "write(data:str)", PikaStdDevice_CAN_writeMethod);
    return self;
}

Arg *PikaStdDevice_CAN(PikaObj *self){
    return obj_newObjInPackage(New_PikaStdDevice_CAN);
}
