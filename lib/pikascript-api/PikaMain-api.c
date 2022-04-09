/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "PikaMain.h"
#include "PikaStdLib_SysObj.h"
#include "PikaStdData.h"
#include "PikaStdLib.h"
#include "STM32F1.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_PikaMain(Args *args){
    PikaObj *self = New_PikaStdLib_SysObj(args);
    obj_newObj(self, "PikaStdData", "PikaStdData", New_PikaStdData);
    obj_newObj(self, "PikaStdLib", "PikaStdLib", New_PikaStdLib);
    obj_newObj(self, "STM32F1", "STM32F1", New_STM32F1);
    return self;
}

Arg *PikaMain(PikaObj *self){
    return obj_newObjInPackage(New_PikaMain);
}
