/*
 * This file is part of the PikaScript project.
 * http://github.com/pikastech/pikascript
 *
 * MIT License
 *
 * Copyright (c) 2021 lyon 李昂 liang6516@outlook.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define __PIKA_OBJ_CLASS_IMPLEMENT
#include "PikaObj.h"
#include "BaseObj.h"
#include "PikaPlatform.h"
#include "dataArgs.h"
#include "dataMemory.h"
#include "dataString.h"
#include "dataStrs.h"

int fast_atoi(char* src) {
    const char* p = src;
    static const uint64_t a[][10] = {
        {0, 1e0, 2e0, 3e0, 4e0, 5e0, 6e0, 7e0, 8e0, 9e0},
        {0, 1e1, 2e1, 3e1, 4e1, 5e1, 6e1, 7e1, 8e1, 9e1},
        {0, 1e2, 2e2, 3e2, 4e2, 5e2, 6e2, 7e2, 8e2, 9e2},
        {0, 1e3, 2e3, 3e3, 4e3, 5e3, 6e3, 7e3, 8e3, 9e3},
        {0, 1e4, 2e4, 3e4, 4e4, 5e4, 6e4, 7e4, 8e4, 9e4},
        {0, 1e5, 2e5, 3e5, 4e5, 5e5, 6e5, 7e5, 8e5, 9e5},
        {0, 1e6, 2e6, 3e6, 4e6, 5e6, 6e6, 7e6, 8e6, 9e6},
        {0, 1e7, 2e7, 3e7, 4e7, 5e7, 6e7, 7e7, 8e7, 9e7},
        {0, 1e8, 2e8, 3e8, 4e8, 5e8, 6e8, 7e8, 8e8, 9e8},
        {0, 1e9, 2e9, 3e9, 4e9, 5e9, 6e9, 7e9, 8e9, 9e9},
    };
    uint16_t size = strGetSize(src);
    p = p + size - 1;
    if (*p) {
        int s = 0;
        const uint64_t* n = a[0];
        while (p != src) {
            s += n[(*p - '0')];
            n += 10;
            p--;
        }
        if (*p == '-') {
            return -s;
        }
        return s + n[(*p - '0')];
    }
    return 0;
}

static uint16_t const str100p[100] = {
    0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730, 0x3830,
    0x3930, 0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531, 0x3631, 0x3731,
    0x3831, 0x3931, 0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632,
    0x3732, 0x3832, 0x3932, 0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533,
    0x3633, 0x3733, 0x3833, 0x3933, 0x3034, 0x3134, 0x3234, 0x3334, 0x3434,
    0x3534, 0x3634, 0x3734, 0x3834, 0x3934, 0x3035, 0x3135, 0x3235, 0x3335,
    0x3435, 0x3535, 0x3635, 0x3735, 0x3835, 0x3935, 0x3036, 0x3136, 0x3236,
    0x3336, 0x3436, 0x3536, 0x3636, 0x3736, 0x3836, 0x3936, 0x3037, 0x3137,
    0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737, 0x3837, 0x3937, 0x3038,
    0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738, 0x3838, 0x3938,
    0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739, 0x3839,
    0x3939,
};

char* fast_itoa(char* buf, uint32_t val) {
    char* p = &buf[10];
    *p = '\0';
    while (val >= 100) {
        uint32_t const old = val;

        p -= 2;
        val /= 100;
        __platform_memcpy(p, &str100p[old - (val * 100)], sizeof(uint16_t));
    }
    p -= 2;
    __platform_memcpy(p, &str100p[val], sizeof(uint16_t));
    return &p[val < 10];
}

int32_t deinitEachSubObj(Arg* argEach, Args* handleArgs) {
    if (NULL != handleArgs) {
        /* error: tOhis handle not need handle args */
        return 1;
    }
    ArgType type = arg_getType(argEach);
    /* deinit sub object */
    if (type == ARG_TYPE_OBJECT) {
        PikaObj* subObj = arg_getPtr(argEach);
        obj_deinit(subObj);
    }
    return 0;
}

void deinitAllSubObj(PikaObj* self) {
    Args* args = self->list;
    args_foreach(args, deinitEachSubObj, NULL);
}

int32_t obj_deinit(PikaObj* self) {
    deinitAllSubObj(self);
    args_deinit(self->list);
    pikaFree(self, sizeof(PikaObj));
    self = NULL;
    return 0;
}

int32_t obj_enable(PikaObj* self) {
    obj_setInt(self, "isEnable", 1);
    return 0;
}

int32_t obj_disable(PikaObj* self) {
    obj_setInt(self, "isEnable", 0);
    return 0;
}

int32_t obj_setInt(PikaObj* self, char* argPath, int64_t val) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        /* [error] object no found */
        return 1;
    }
    char* name = strPointToLastToken(argPath, '.');
    args_setInt(obj->list, name, val);
    return 0;
}

int32_t obj_setPtr(PikaObj* self, char* argPath, void* pointer) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        return 1;
    }
    char* name = strPointToLastToken(argPath, '.');
    args_setPtr(obj->list, name, pointer);
    return 0;
}

int32_t obj_setFloat(PikaObj* self, char* argPath, float value) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        return 1;
    }
    char* name = strPointToLastToken(argPath, '.');
    args_setFloat(obj->list, name, value);
    return 0;
}

int32_t obj_setStr(PikaObj* self, char* argPath, char* str) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        return 1;
    }
    char* name = strPointToLastToken(argPath, '.');
    args_setStr(obj->list, name, str);
    return 0;
}

int64_t obj_getInt(PikaObj* self, char* argPath) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        return -999999999;
    }
    char* argName = strPointToLastToken(argPath, '.');
    int res = args_getInt(obj->list, argName);
    return res;
}

Arg* obj_getArg(PikaObj* self, char* argPath) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        return NULL;
    }
    char* argName = strPointToLastToken(argPath, '.');
    Arg* res = args_getArg(obj->list, argName);
    return res;
}

static int32_t __obj_setArg(PikaObj* self,
                            char* argPath,
                            Arg* arg,
                            uint8_t is_copy) {
    /* setArg would copy arg */
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        /* object no found */
        return 1;
    }
    char* argName = strPointToLastToken(argPath, '.');
    Arg* newArg;
    if (is_copy) {
        newArg = arg_copy(arg);
    } else {
        newArg = arg;
    }
    newArg = arg_setName(newArg, argName);
    args_setArg(obj->list, newArg);
    return 0;
}

int32_t obj_setArg(PikaObj* self, char* argPath, Arg* arg) {
    return __obj_setArg(self, argPath, arg, 1);
};

int32_t obj_setArg_noCopy(PikaObj* self, char* argPath, Arg* arg) {
    return __obj_setArg(self, argPath, arg, 0);
}

void* obj_getPtr(PikaObj* self, char* argPath) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        return NULL;
    }
    char* argName = strPointToLastToken(argPath, '.');
    void* res = args_getPtr(obj->list, argName);
    return res;
}

float obj_getFloat(PikaObj* self, char* argPath) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        return -999.999;
    }
    char* argName = strPointToLastToken(argPath, '.');
    float res = args_getFloat(obj->list, argName);
    return res;
}

char* obj_getStr(PikaObj* self, char* argPath) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    if (NULL == obj) {
        return NULL;
    }
    char* argName = strPointToLastToken(argPath, '.');
    char* res = args_getStr(obj->list, argName);
    return res;
}

int32_t obj_load(PikaObj* self, Args* args, char* name) {
    args_copyArgByName(args, name, self->list);
    return 0;
}

int32_t obj_addOther(PikaObj* self, char* subObjectName, void* new_ObjectFun) {
    Args initArgs = {0};
    void* (*new_Object)(Args * initArgs) = (void* (*)(Args*))new_ObjectFun;
    void* subObject = new_Object(&initArgs);
    obj_setPtr(self, subObjectName, subObject);
    args_deinit(&initArgs);
    return 0;
}

int32_t obj_freeObj(PikaObj* self, char* objPath) {
    PikaObj* obj = obj_getPtr(self, objPath);
    obj_deinit(obj);
    return 0;
}

char* obj_print(PikaObj* self, char* name) {
    if (NULL == self) {
        return NULL;
    }
    return args_print(self->list, name);
}

PikaObj* obj_getClassObjByNewFun(PikaObj* context,
                                 char* name,
                                 NewFun newClassFun) {
    Args* initArgs = New_args(NULL);
    PikaObj* thisClass = newClassFun(initArgs);
    obj_setPtr(thisClass, "_clsptr", (void*)newClassFun);
    args_deinit(initArgs);
    return thisClass;
}

Arg* obj_getMethodArg(PikaObj* obj, char* methodPath) {
    Arg* method = NULL;
    char* methodName = strPointToLastToken(methodPath, '.');
    method = obj_getArg(obj, methodName);
    PikaObj* methodHostClass;
    if (NULL != method) {
        method = arg_copy(method);
        goto exit;
    }
    methodHostClass = obj_getClassObj(obj);
    method = arg_copy(obj_getArg(methodHostClass, methodName));
    obj_deinit(methodHostClass);
exit:
    return method;
}

PikaObj* obj_getClassObj(PikaObj* obj) {
    NewFun classPtr = (NewFun)obj_getPtr(obj, "_clsptr");
    PikaObj* classObj = obj_getClassObjByNewFun(obj, "", classPtr);
    return classObj;
}

void* getNewClassObjFunByName(PikaObj* obj, char* name) {
    char* classPath = name;
    /* init the subprocess */
    void* newClassObjFun = args_getPtr(obj->list, classPath);
    return newClassObjFun;
}

int32_t __foreach_removeMethodInfo(Arg* argNow, Args* argList) {
    if (arg_getType(argNow) == ARG_TYPE_NATIVE_METHOD) {
        args_removeArg(argList, argNow);
        return 0;
    }
    return 0;
}

PikaObj* removeMethodInfo(PikaObj* thisClass) {
#if PIKA_METHOD_CACHE_ENABLE
#else
    args_foreach(thisClass->list, __foreach_removeMethodInfo, thisClass->list);
#endif
    return thisClass;
}

PikaObj* newObjFromFun(NewFun newObjFun) {
    PikaObj* thisClass = obj_getClassObjByNewFun(NULL, "", newObjFun);
    return removeMethodInfo(thisClass);
}

extern PikaObj* __pikaMain;
PikaObj* newRootObj(char* name, NewFun newObjFun) {
    PikaObj* newObj = newObjFromFun(newObjFun);
    __pikaMain = newObj;
    return newObj;
}

Arg* newFreeObjArg(NewFun newObjFun) {
    PikaObj* newObj = newObjFromFun(newObjFun);
    Arg* objArg = arg_setPtr(NULL, "", ARG_TYPE_FREE_OBJECT, newObj);
    return objArg;
}

Arg* obj_newObjInPackage(NewFun newObjFun) {
    return newFreeObjArg(newObjFun);
}

static PikaObj* __initObj(PikaObj* obj, char* name) {
    PikaObj* res = NULL;
    NewFun newObjFun = (NewFun)getNewClassObjFunByName(obj, name);
    Args buffs = {0};
    PikaObj* thisClass;
    PikaObj* newObj;
    if (NULL == newObjFun) {
        /* no such object */
        res = NULL;
        goto exit;
    }
    thisClass = obj_getClassObjByNewFun(obj, name, newObjFun);
    newObj = removeMethodInfo(thisClass);

    args_setPtrWithType(obj->list, name, ARG_TYPE_OBJECT, newObj);
    res = obj_getPtr(obj, name);
    goto exit;
exit:
    strsDeinit(&buffs);
    return res;
}

PikaObj* obj_getObjDirect(PikaObj* self, char* name) {
    if (NULL == self) {
        return NULL;
    }
    /* finded object, check type*/
    ArgType type = args_getType(self->list, name);
    /* found mate Object */
    if (type == ARG_TYPE_MATE_OBJECT) {
        return __initObj(self, name);
    }
    /* found Objcet */
    if (type == ARG_TYPE_OBJECT || type == ARG_TYPE_POINTER) {
        return args_getPtr(self->list, name);
    }
    return NULL;
}

PikaObj* obj_getObj(PikaObj* self, char* objPath, int32_t keepDeepth) {
    char objPath_buff[PIKA_PATH_BUFF_SIZE];
    __platform_memcpy(objPath_buff, objPath, strGetSize(objPath) + 1);
    char token_buff[PIKA_NAME_BUFF_SIZE] = {0};
    int32_t token_num = strGetTokenNum(objPath, '.');
    PikaObj* obj = self;
    for (int32_t i = 0; i < token_num - keepDeepth; i++) {
        char* token = strPopToken(token_buff, objPath_buff, '.');
        obj = obj_getObjDirect(obj, token);
        if (obj == NULL) {
            goto exit;
        }
    }
    goto exit;
exit:
    return obj;
}

Method methodArg_getPtr(Arg* method_arg) {
    uint32_t size_ptr = sizeof(void*);
    void* info = arg_getContent(method_arg);
    void* ptr = NULL;
    __platform_memcpy(&ptr, info, size_ptr);
    return (Method)ptr;
}

char* methodArg_getTypeList(Arg* method_arg, Args* buffs) {
    char* method_dec = strsCopy(buffs, methodArg_getDec(method_arg));
    return strsCut(buffs, method_dec, '(', ')');
}

Method obj_getNativeMethod(PikaObj* self, char* method_name) {
    Arg* method_arg = obj_getMethodArg(self, method_name);
    if (NULL == method_arg) {
        return NULL;
    }
    Method res = methodArg_getPtr(method_arg);
    arg_deinit(method_arg);
    return res;
}

ByteCodeFrame* methodArg_getBytecodeFrame(Arg* method_arg) {
    uint32_t size_ptr = sizeof(void*);
    void* info = arg_getContent(method_arg) + size_ptr;
    ByteCodeFrame* ptr = NULL;
    __platform_memcpy(&ptr, info, size_ptr);
    return ptr;
}

char* methodArg_getDec(Arg* method_arg) {
    uint32_t size_ptr = sizeof(void*);
    void* info = arg_getContent(method_arg);
    return (char*)((uintptr_t)info + 2 * size_ptr);
}

static void obj_saveMethodInfo(PikaObj* self, MethodInfo* method_info) {
    Args buffs = {0};
    char* pars = strsRemovePrefix(&buffs, method_info->dec, method_info->name);
    method_info->pars = pars;
    Arg* arg = New_arg(NULL);
    uint32_t size_pars = strGetSize(pars);
    uintptr_t method_info_bytecode_frame =
        (uintptr_t)method_info->bytecode_frame;
    arg =
        arg_setPtr(arg, method_info->name, method_info->type, method_info->ptr);
    arg = arg_append(arg, &(method_info_bytecode_frame),
                     sizeof(method_info_bytecode_frame));
    arg = arg_append(arg, method_info->pars, size_pars + 1);
    args_setArg(self->list, arg);
    strsDeinit(&buffs);
}
static int32_t __class_defineMethodWithType(PikaObj* self,
                                            char* declearation,
                                            Method methodPtr,
                                            ArgType method_type,
                                            ByteCodeFrame* bytecode_frame) {
    int32_t size = strGetSize(declearation);
    int32_t res = 0;
    Args buffs = {0};
    char* cleanDeclearation =
        strDeleteChar(args_getBuff(&buffs, size), declearation, ' ');
    char* methodPath =
        strGetFirstToken(args_getBuff(&buffs, size), cleanDeclearation, '(');

    PikaObj* methodHost = obj_getObj(self, methodPath, 1);
    MethodInfo method_info = {0};
    char* methodName;
    if (NULL == methodHost) {
        /* no found method object */
        res = 1;
        goto exit;
    }
    methodName = strPointToLastToken(methodPath, '.');
    method_info.dec = cleanDeclearation;
    method_info.name = methodName;
    method_info.ptr = (void*)methodPtr;
    method_info.type = method_type;
    method_info.bytecode_frame = bytecode_frame;
    obj_saveMethodInfo(methodHost, &method_info);
    res = 0;
    goto exit;
exit:
    strsDeinit(&buffs);
    return res;
}

/* define a constructor method */
int32_t class_defineConstructor(PikaObj* self,
                                char* declearation,
                                Method methodPtr) {
    return __class_defineMethodWithType(self, declearation, methodPtr,
                                        ARG_TYPE_NATIVE_CONSTRUCTOR_METHOD, NULL);
}

/* define a native method as default */
int32_t class_defineMethod(PikaObj* self,
                           char* declearation,
                           Method methodPtr) {
    return __class_defineMethodWithType(self, declearation, methodPtr,
                                        ARG_TYPE_NATIVE_METHOD, NULL);
}

/* define object method, object method is which startwith (self) */
int32_t class_defineRunTimeConstructor(PikaObj* self,
                                       char* declearation,
                                       Method methodPtr,
                                       ByteCodeFrame* bytecode_frame) {
    return __class_defineMethodWithType(self, declearation, methodPtr,
                                        ARG_TYPE_CONSTRUCTOR_METHOD,
                                        bytecode_frame);
}

/* define object method, object method is which startwith (self) */
int32_t class_defineObjectMethod(PikaObj* self,
                                 char* declearation,
                                 Method methodPtr,
                                 ByteCodeFrame* bytecode_frame) {
    return __class_defineMethodWithType(self, declearation, methodPtr,
                                        ARG_TYPE_OBJECT_METHOD, bytecode_frame);
}

/* define a static method as default */
int32_t class_defineStaticMethod(PikaObj* self,
                                 char* declearation,
                                 Method methodPtr,
                                 ByteCodeFrame* bytecode_frame) {
    return __class_defineMethodWithType(self, declearation, methodPtr,
                                        ARG_TYPE_STATIC_METHOD, bytecode_frame);
}

PIKA_WEAK int __runExtern_contral(PikaObj* self, char* cmd) {
    return 0;
}

VMParameters* obj_runDirect(PikaObj* self, char* cmd) {
    return pikaVM_run(self, cmd);
}

int32_t obj_removeArg(PikaObj* self, char* argPath) {
    PikaObj* objHost = obj_getObj(self, argPath, 1);
    Arg* obj_arg = obj_getArg(self, argPath);
    char* argName;
    int32_t res;
    if (ARG_TYPE_OBJECT == arg_getType(obj_arg)) {
        obj_deinit(arg_getPtr(obj_arg));
    }
    int32_t err = 0;
    if (NULL == objHost) {
        /* [error] object no found */
        err = 1;
        goto exit;
    }
    argName = strPointToLastToken(argPath, '.');
    res = args_removeArg(objHost->list, args_getArg(objHost->list, argName));
    if (1 == res) {
        /*[error] not found arg*/
        err = 2;
        goto exit;
    }
    goto exit;
exit:
    return err;
}

int32_t obj_isArgExist(PikaObj* self, char* argPath) {
    PikaObj* obj = obj_getObj(self, argPath, 1);
    int32_t res = 0;
    char* argName;
    Arg* arg;
    if (NULL == obj) {
        /* [error] object no found */
        res = 1;
        goto exit;
    }
    argName = strPointToLastToken(argPath, '.');
    arg = args_getArg(obj->list, argName);
    if (NULL == arg) {
        /* no found arg */
        res = 0;
        goto exit;
    }
    /* found arg */
    res = 1;
    goto exit;

exit:
    return res;
}

void obj_runNoRes(PikaObj* slef, char* cmd) {
    /* unsafe, nothing would happend when error occord */
    obj_runDirect(slef, cmd);
}

void obj_run(PikaObj* self, char* cmd) {
    obj_runDirect(self, cmd);
}

void obj_runNativeMethod(PikaObj* self, char* method_name, Args* args) {
    Method native_method = obj_getNativeMethod(self, method_name);
    if (NULL == native_method) {
        return;
    }
    native_method(self, args);
}

static void __clearBuff(char* buff, int size) {
    for (int i = 0; i < size; i++) {
        buff[i] = 0;
    }
}

void obj_shellLineProcess(PikaObj* self,
                          __obj_shellLineHandler_t __lineHandler_fun,
                          struct shell_config* cfg) {
    Args buffs = {0};
    char* rxBuff = args_getBuff(&buffs, PIKA_LINE_BUFF_SIZE);
    char* input_line = NULL;
    uint8_t is_in_block = 0;
    __platform_printf(cfg->prefix); fflush(stdout);
    while (1) {
        fflush(stdout); // flush anything that is buffered to the terminal before reading new char
        char inputChar = __platform_getchar();
#ifndef __linux
        if (inputChar == '\r')
            __platform_printf("\n");
        else
            __platform_printf("%c", inputChar);
        fflush(stdout); //actually flush character to terminal
#endif
        if ((inputChar == '\b') || (inputChar == 127)) {
            uint32_t size = strGetSize(rxBuff);
            if (size == 0) {
                __platform_printf(" ");
                continue;
            }
            __platform_printf(" \b");
            rxBuff[size - 1] = 0;
            continue;
        }
        if (inputChar != '\r' && inputChar != '\n') {
            strAppendWithSize(rxBuff, &inputChar, 1);
            continue;
        }
        if ((inputChar == '\r') || (inputChar == '\n')) {
#ifndef __linux
            //__platform_printf("\r\n");
#endif
            /* still in block */
            if (is_in_block) {
                /* load new line into buff */
                Args buffs = {0};
                char _n = '\n';
                strAppendWithSize(rxBuff, &_n, 1);
                char* shell_buff_new =
                    strsAppend(&buffs, obj_getStr(self, "shell_buff"), rxBuff);
                obj_setStr(self, "shell_buff", shell_buff_new);
                strsDeinit(&buffs);
                /* go out from block */
                if (rxBuff[0] != ' ') {
                    is_in_block = 0;
                    input_line = obj_getStr(self, "shell_buff");
                    if (SHELL_STATE_EXIT ==
                        __lineHandler_fun(self, input_line)) {
                        break;
                    }
                    __platform_printf(">>> ");
                } else {
                    __platform_printf("... ");
                }
                __clearBuff(rxBuff, PIKA_LINE_BUFF_SIZE);
                continue;
            }
            if (0 != strGetSize(rxBuff)) {
                /* go in block */
                if (rxBuff[strGetSize(rxBuff) - 1] == ':') {
                    is_in_block = 1;
                    char _n = '\n';
                    strAppendWithSize(rxBuff, &_n, 1);
                    obj_setStr(self, "shell_buff", rxBuff);
                    __clearBuff(rxBuff, PIKA_LINE_BUFF_SIZE);
                    __platform_printf("... ");
                    continue;
                }
            }
            input_line = rxBuff;
            if (SHELL_STATE_EXIT == __lineHandler_fun(self, input_line)) {
                break;
            }
            __platform_printf(cfg->prefix); fflush(stdout);

            __clearBuff(rxBuff, PIKA_LINE_BUFF_SIZE);
            continue;
        }
    }
    strsDeinit(&buffs);
}

static enum shell_state __obj_shellLineHandler_debuger(PikaObj* self,
                                                       char* input_line) {
    /* exit */
    if (strEqu("exit()", input_line)) {
        /* exit pika shell */
        return SHELL_STATE_EXIT;
    }
    /* run single line */
    obj_run(self, input_line);
    return SHELL_STATE_CONTINUE;
}

void pikaScriptShell(PikaObj* self) {
    struct shell_config cfg = {
        .prefix = ">>> ",
    };
    obj_shellLineProcess(self, __obj_shellLineHandler_debuger, &cfg);
}

void obj_setErrorCode(PikaObj* self, int32_t errCode) {
    obj_setInt(self, "__errCode", errCode);
}

int32_t obj_getErrorCode(PikaObj* self) {
    if (!obj_isArgExist(self, "__errCode")) {
        return 0;
    }
    return obj_getInt(self, "__errCode");
}

void args_setErrorCode(Args* args, int32_t errCode) {
    args_setInt(args, "__errCode", errCode);
}

int32_t args_getErrorCode(Args* args) {
    if (!args_isArgExist(args, "__errCode")) {
        return 0;
    }
    return args_getInt(args, "__errCode");
}

void obj_setSysOut(PikaObj* self, char* str) {
    // obj_setStr(self, "__sysOut", str);
    args_setSysOut(self->list, str);
}

char* obj_getSysOut(PikaObj* self) {
    return obj_getStr(self, "__sysOut");
}

char* args_getSysOut(Args* args) {
    return args_getStr(args, "__sysOut");
}

void args_setSysOut(Args* args, char* str) {
    // args_setStr(args, "__sysOut", str);
    if (NULL == str) {
        return;
    }
    if (strEqu("", str)) {
        return;
    }
    __platform_printf("%s\r\n", str);
}

void obj_sysPrintf(PikaObj* self, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char sysOut[128] = {0};
    __platform_vsprintf(sysOut, fmt, args);
    obj_setSysOut(self, sysOut);
    va_end(args);
}

void method_returnStr(Args* args, char* val) {
    args_setStr(args, "return", val);
}
void method_returnInt(Args* args, int32_t val) {
    args_setInt(args, "return", val);
}
void method_returnFloat(Args* args, float val) {
    args_setFloat(args, "return", val);
}
void method_returnPtr(Args* args, void* val) {
    args_setPtr(args, "return", val);
}
void method_returnArg(Args* args, Arg* arg) {
    arg = arg_setName(arg, "return");
    args_setArg(args, arg);
}

int32_t method_getInt(Args* args, char* argName) {
    return args_getInt(args, argName);
}
float method_getFloat(Args* args, char* argName) {
    return args_getFloat(args, argName);
}
char* method_getStr(Args* args, char* argName) {
    return args_getStr(args, argName);
}

PikaObj* New_PikaObj(void) {
    PikaObj* self = pikaMalloc(sizeof(PikaObj));
    /* List */
    self->list = New_args(NULL);
    return self;
}
