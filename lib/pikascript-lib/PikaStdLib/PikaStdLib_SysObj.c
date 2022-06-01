#include "BaseObj.h"
#include "PikaStdLib_RangeObj.h"
#include "PikaStdLib_StringObj.h"
#include "dataStrs.h"

void PikaStdLib_SysObj_remove(PikaObj* self, char* argPath) {
    obj_setErrorCode(self, 0);
    int32_t res = obj_removeArg(self, argPath);
    if (1 == res) {
        obj_setSysOut(self, "[error] del: object no found.");
        obj_setErrorCode(self, 1);
        return;
    }
    if (2 == res) {
        obj_setSysOut(self, "[error] del: arg not match.");
        obj_setErrorCode(self, 2);
        return;
    }
}

void PikaStdLib_SysObj_type(PikaObj* self, Arg* arg) {
    if (NULL == arg) {
        obj_setSysOut(self, "[error] type: arg no found.");
        obj_setErrorCode(self, 1);
        return;
    }
    ArgType type = arg_getType(arg);
    if (ARG_TYPE_INT == type) {
        obj_setSysOut(self, "<class 'int'>");
        return;
    }
    if (ARG_TYPE_FLOAT == type) {
        obj_setSysOut(self, "<class 'float'>");
        return;
    }
    if (ARG_TYPE_STRING == type) {
        obj_setSysOut(self, "<class 'str'>");
        return;
    }
    if (ARG_TYPE_OBJECT == type) {
        obj_setSysOut(self, "<class 'object'>");
        return;
    }
    if (ARG_TYPE_OBJECT_META == type) {
        obj_setSysOut(self, "<class 'meta object'>");
        return;
    }
    if (ARG_TYPE_BYTES == type) {
        obj_setSysOut(self, "<class 'bytes'>");
        return;
    }
    if (ARG_TYPE_METHOD_NATIVE == type) {
        obj_setSysOut(self, "<class 'buitin_function_or_method'>");
        return;
    }
    if (ARG_TYPE_METHOD_OBJECT == type) {
        obj_setSysOut(self, "<class 'method'>");
        return;
    }
    if (ARG_TYPE_METHOD_STATIC == type) {
        obj_setSysOut(self, "<class 'function'>");
        return;
    }
}

float PikaStdLib_SysObj_float(PikaObj* self, Arg* arg) {
    ArgType type = arg_getType(arg);
    if (ARG_TYPE_INT == type) {
        return (float)arg_getInt(arg);
    }
    if (ARG_TYPE_FLOAT == type) {
        return (float)arg_getFloat(arg);
    }
    obj_setSysOut(self, "[error] convert to float type faild.");
    obj_setErrorCode(self, 1);
    return -99999.99999;
}

int PikaStdLib_SysObj_int(PikaObj* self, Arg* arg) {
    ArgType type = arg_getType(arg);
    if (ARG_TYPE_INT == type) {
        return (int)arg_getInt(arg);
    }
    if (ARG_TYPE_FLOAT == type) {
        return (int)arg_getFloat(arg);
    }
    if (ARG_TYPE_STRING == type) {
        return (int)fast_atoi(arg_getStr(arg));
    }
    if (ARG_TYPE_BYTES == type) {
        size_t size = arg_getBytesSize(arg);
        if (size != 1) {
            obj_setSysOut(self, "ValueError: invalid literal for int()");
            obj_setErrorCode(self, 1);
            return -999999999;
        }
        uint8_t val = *arg_getBytes(arg);
        return val;
    }
    obj_setSysOut(self, "[error] convert to int type faild.");
    obj_setErrorCode(self, 1);
    return -999999999;
}

char* PikaStdLib_SysObj_str(PikaObj* self, Arg* arg) {
    ArgType type = arg_getType(arg);
    Args buffs = {0};
    char* res = NULL;
    if (ARG_TYPE_INT == type) {
        int val = arg_getInt(arg);
        res = strsFormat(&buffs, 11, "%d", val);
        goto exit;
    }
    if (ARG_TYPE_FLOAT == type) {
        float val = arg_getFloat(arg);
        res = strsFormat(&buffs, 11, "%f", val);
        goto exit;
    }
    if (ARG_TYPE_OBJECT == type) {
        res = obj_toStr(arg_getPtr(arg));
        if (NULL != res) {
            goto exit;
        }
    }
exit:
    obj_setStr(self, "__buf", res);
    strsDeinit(&buffs);
    return obj_getStr(self, "__buf");
}

Arg* PikaStdLib_SysObj_iter(PikaObj* self, Arg* arg) {
    /* a String, return a StringObj */
    if (ARG_TYPE_STRING == arg_getType(arg)) {
        obj_setStr(self, "_sobj", arg_getStr(arg));
        return arg_newMetaObj(New_PikaStdLib_StringObj);
    }
    /* a MATE object, return itself */
    if (ARG_TYPE_OBJECT_META == arg_getType(arg)) {
        return arg_copy(arg);
    }
    /* object */
    if (ARG_TYPE_OBJECT == arg_getType(arg)) {
        PikaObj* arg_obj = arg_getPtr(arg);
        // pikaVM_runAsm(arg_obj,
        //               "B0\n"
        //               "0 RUN __iter__\n"
        //               "0 OUT __res\n");
        const uint8_t bytes[] = {
            0x08, 0x00, /* instruct array size */
            0x00, 0x82, 0x01, 0x00, 0x00, 0x04, 0x0a, 0x00, /* instruct array */
            0x10, 0x00, /* const pool size */
            0x00, 0x5f, 0x5f, 0x69, 0x74, 0x65, 0x72, 0x5f,
            0x5f, 0x00, 0x5f, 0x5f, 0x72, 0x65, 0x73, 0x00, /* const pool */
        };
        pikaVM_runByteCode(arg_obj, (uint8_t*)bytes);
        Arg* res = arg_copy(args_getArg(arg_obj->list, "__res"));
        obj_removeArg(arg_obj, "__res");
        return res;
    }
    return arg_setNull(NULL);
}

Arg* PikaStdLib_SysObj_range(PikaObj* self, int a1, int a2) {
    /* set template arg to create rangeObj */
    obj_setInt(self, "_r1", a1);
    obj_setInt(self, "_r2", a2);
    return arg_newMetaObj(New_PikaStdLib_RangeObj);
}

Arg* PikaStdLib_SysObj___get__(PikaObj* self, Arg* key, Arg* obj) {
    ArgType obj_type = arg_getType(obj);
    int index = 0;
    if (ARG_TYPE_INT == arg_getType(key)) {
        index = arg_getInt(key);
    }
    if (ARG_TYPE_STRING == obj_type) {
        char* str_pyload = arg_getStr(obj);
        char char_buff[] = " ";
        if (index < 0) {
            index = strGetSize(str_pyload) + index;
        }
        char_buff[0] = str_pyload[index];
        return arg_setStr(NULL, "", char_buff);
    }
    if (ARG_TYPE_BYTES == obj_type) {
        uint8_t* bytes_pyload = arg_getBytes(obj);
        uint8_t byte_buff[] = " ";
        if (index < 0) {
            index = arg_getBytesSize(obj) + index;
        }
        byte_buff[0] = bytes_pyload[index];
        return arg_setBytes(NULL, "", byte_buff, 1);
    }
    if (ARG_TYPE_OBJECT == obj_type) {
        PikaObj* arg_obj = arg_getPtr(obj);
        obj_setArg(arg_obj, "__key", key);
        // pikaVM_runAsm(arg_obj,
        //               "B0\n"
        //               "1 REF __key\n"
        //               "0 RUN __get__\n"
        //               "0 OUT __res\n");
        const uint8_t bytes[] = {
            0x0c, 0x00, /* instruct array size */
            0x10, 0x81, 0x01, 0x00, 0x00, 0x02, 0x07, 0x00, 0x00, 0x04, 0x0f,
            0x00,
            /* instruct array */
            0x15, 0x00, /* const pool size */
            0x00, 0x5f, 0x5f, 0x6b, 0x65, 0x79, 0x00, 0x5f, 0x5f, 0x67, 0x65,
            0x74, 0x5f, 0x5f, 0x00, 0x5f, 0x5f, 0x72, 0x65, 0x73,
            0x00, /* const pool */
        };
        pikaVM_runByteCode(arg_obj, (uint8_t*)bytes);
        return arg_copy(args_getArg(arg_obj->list, "__res"));
    }
    return arg_setNull(NULL);
}

void PikaStdLib_SysObj___set__(PikaObj* self,
                               Arg* key,
                               Arg* obj,
                               char* obj_str,
                               Arg* val) {
    ArgType obj_type = arg_getType(obj);
    if (ARG_TYPE_STRING == obj_type) {
        int index = arg_getInt(key);
        char* str_val = arg_getStr(val);
        char* str_pyload = arg_getStr(obj);
        str_pyload[index] = str_val[0];
        obj_setStr(self, obj_str, str_pyload);
    }
    if (ARG_TYPE_BYTES == obj_type) {
        int index = arg_getInt(key);
        uint8_t* bytes_val = arg_getBytes(val);
        uint8_t* bytes_pyload = arg_getBytes(obj);
        size_t bytes_len = arg_getBytesSize(obj);
        bytes_pyload[index] = bytes_val[0];
        obj_setBytes(self, obj_str, bytes_pyload, bytes_len);
    }
    if (ARG_TYPE_OBJECT == obj_type) {
        PikaObj* arg_obj = arg_getPtr(obj);
        obj_setArg(arg_obj, "__key", key);
        obj_setArg(arg_obj, "__val", val);
        // pikaVM_runAsm(arg_obj,
        //               "B0\n"
        //               "1 REF __key\n"
        //               "1 REF __val\n"
        //               "0 RUN __set__\n");
        const uint8_t bytes[] = {
            0x0c, 0x00, /* instruct array size */
            0x10, 0x81, 0x01, 0x00, 0x10, 0x01, 0x07, 0x00, 0x00, 0x02, 0x0d,
            0x00,
            /* instruct array */
            0x15, 0x00, /* const pool size */
            0x00, 0x5f, 0x5f, 0x6b, 0x65, 0x79, 0x00, 0x5f, 0x5f, 0x76, 0x61,
            0x6c, 0x00, 0x5f, 0x5f, 0x73, 0x65, 0x74, 0x5f, 0x5f,
            0x00, /* const pool */
        };
        pikaVM_runByteCode(arg_obj, (uint8_t*)bytes);
    }
}

int PikaStdLib_SysObj_len(PikaObj* self, Arg* arg) {
    if (ARG_TYPE_STRING == arg_getType(arg)) {
        return strGetSize(arg_getStr(arg));
    }
    obj_setErrorCode(self, 1);
    __platform_printf("[Error] len: arg type not support\r\n");
    return -1;
}

Arg* PikaStdLib_SysObj_list(PikaObj* self) {
#if PIKA_BUILTIN_LIST_ENABLE
    PikaObj* New_PikaStdData_List(Args * args);
    return obj_newObjInPackage(New_PikaStdData_List);
#endif
    obj_setErrorCode(self, 1);
    __platform_printf("[Error] built-in list is not enabled.\r\n");
    return arg_setNull(NULL);
}

Arg* PikaStdLib_SysObj_dict(PikaObj* self) {
#if PIKA_BUILTIN_DICT_ENABLE
    PikaObj* New_PikaStdData_Dict(Args * args);
    return obj_newObjInPackage(New_PikaStdData_Dict);
#endif
    obj_setErrorCode(self, 1);
    __platform_printf("[Error] built-in dist is not enabled.\r\n");
    return arg_setNull(NULL);
}

char* PikaStdLib_SysObj_hex(PikaObj* self, int val) {
    char buff[PIKA_SPRINTF_BUFF_SIZE] = {0};
    if (val > 0) {
        __platform_sprintf(buff, "0x%02x", val);
    } else {
        __platform_sprintf(buff, "-0x%02x", -val);
    }
    /* load the string from stack to heap */
    obj_setStr(self, "__buf", buff);
    return obj_getStr(self, "__buf");
}

int PikaStdLib_SysObj_ord(PikaObj* self, char* val) {
    return (int)val[0];
}

char* PikaStdLib_SysObj_chr(PikaObj* self, int val) {
    char buff[PIKA_SPRINTF_BUFF_SIZE] = {0};
    char to_str[] = "0";
    to_str[0] = val;
    __platform_sprintf(buff, "%s", to_str);
    /* load the string from stack to heap */
    obj_setStr(self, "__buf", buff);
    return obj_getStr(self, "__buf");
}

Arg* PikaStdLib_SysObj_bytes(PikaObj* self, Arg* val) {
    ArgType type = arg_getType(val);
    if (ARG_TYPE_INT == type) {
        int size = arg_getInt(val);
        /* src is NULL so the bytes are all '\0' */
        Arg* bytes = arg_setBytes(NULL, "", NULL, size);
        return bytes;
    }
    if (ARG_TYPE_BYTES == type) {
        return arg_copy(val);
    }
    if (ARG_TYPE_STRING == type) {
        int size = strGetSize(arg_getStr(val));
        Arg* bytes = arg_setBytes(NULL, "", (uint8_t*)arg_getStr(val), size);
        return bytes;
    }
    obj_setErrorCode(self, 1);
    __platform_printf("Error: input arg type not supported.\r\n");
    return arg_setNull(NULL);
}

Arg* PikaStdLib_SysObj___slice__(PikaObj* self,
                                 Arg* end,
                                 Arg* obj,
                                 Arg* start,
                                 int step) {
#if PIKA_SYNTEX_ITEM_SLICE_ENABLE
    /* No interger index only support __get__ */
    if (!(arg_getType(start) == ARG_TYPE_INT &&
          arg_getType(end) == ARG_TYPE_INT)) {
        return PikaStdLib_SysObj___get__(self, start, obj);
    }

    int start_i = arg_getInt(start);
    int end_i = arg_getInt(end);

    /* __slice__ is equal to __get__ */
    if (end_i - start_i == 1) {
        return PikaStdLib_SysObj___get__(self, start, obj);
    }

    if (ARG_TYPE_STRING == arg_getType(obj)) {
        Arg* sliced_arg = arg_setStr(NULL, "", "");
        for (int i = start_i; i < end_i; i++) {
            Arg* i_arg = arg_setInt(NULL, "", i);
            Arg* item_arg = PikaStdLib_SysObj___get__(self, i_arg, obj);
            sliced_arg = arg_strAppend(sliced_arg, arg_getStr(item_arg));
            arg_deinit(item_arg);
            arg_deinit(i_arg);
        }
        return sliced_arg;
    }

    if (ARG_TYPE_BYTES == arg_getType(obj)) {
        Arg* sliced_arg = arg_setBytes(NULL, "", NULL, 0);
        for (int i = start_i; i < end_i; i++) {
            Arg* i_arg = arg_setInt(NULL, "", i);
            Arg* item_arg = PikaStdLib_SysObj___get__(self, i_arg, obj);
            uint8_t* bytes_origin = arg_getBytes(sliced_arg);
            size_t size_origin = arg_getBytesSize(sliced_arg);
            Arg* sliced_arg_new = arg_setBytes(NULL, "", NULL, size_origin + 1);
            __platform_memcpy(arg_getBytes(sliced_arg_new), bytes_origin,
                              size_origin);
            __platform_memcpy(arg_getBytes(sliced_arg_new) + size_origin,
                              arg_getBytes(item_arg), 1);
            arg_deinit(sliced_arg);
            sliced_arg = sliced_arg_new;
            arg_deinit(item_arg);
            arg_deinit(i_arg);
        }
        return sliced_arg;
    }
#endif

    return arg_setNull(NULL);
}
