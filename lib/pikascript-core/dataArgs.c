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

#include "dataArgs.h"
#include "PikaObj.h"
#include "PikaPlatform.h"
#include "dataLink.h"
#include "dataMemory.h"
#include "dataString.h"
#include "dataStrs.h"

void args_deinit(Args* self) {
    link_deinit(self);
}

void args_deinit_stack(Args* self) {
    link_deinit_stack(self);
}

int32_t args_setFloat(Args* self, char* name, float argFloat) {
    Arg* argNew = New_arg(NULL);
    argNew = arg_setFloat(argNew, name, argFloat);
    args_setArg(self, argNew);
    return 0;
}

void* args_getPtr(Args* self, char* name) {
    void* pointer = NULL;
    Arg* arg = args_getArg(self, name);
    if (NULL == arg) {
        return NULL;
    }

    pointer = arg_getPtr(arg);
    return pointer;
}

int32_t args_setPtr(Args* self, char* name, void* argPointer) {
    int32_t errCode = 0;
    Arg* argNew = New_arg(NULL);
    argNew = arg_setPtr(argNew, name, ARG_TYPE_POINTER, argPointer);
    args_setArg(self, argNew);
    return errCode;
}

int32_t args_setRef(Args* self, char* name, void* argPointer) {
    int32_t errCode = 0;
    Arg* argNew = New_arg(NULL);
    argNew = arg_setRef(argNew, name, argPointer);
    args_setArg(self, argNew);
    return errCode;
}

int32_t args_setStr(Args* self, char* name, char* strIn) {
    int32_t errCode = 0;
    Arg* argNew = New_arg(NULL);
    argNew = arg_setStr(argNew, name, strIn);
    args_setArg(self, argNew);
    return errCode;
}

int args_pushArg(Args* self, Arg* arg) {
    link_addNode(self, arg);
    return 0;
}

void args_setBytes(Args* self, char* name, uint8_t* src, size_t size) {
    Arg* argNew = arg_setBytes(NULL, name, src, size);
    args_setArg(self, argNew);
}

char* args_getBuff(Args* self, int32_t size) {
    Arg* argNew = New_arg(NULL);
    argNew = arg_newContent(argNew, size + 1);
    args_pushArg(self, argNew);
    return (char*)arg_getContent(argNew);
}

char* args_getStr(Args* self, char* name) {
    if (NULL == self) {
        return NULL;
    }
    Arg* arg = args_getArg(self, name);
    if (NULL == arg) {
        return NULL;
    }
    if (NULL == arg_getContent(arg)) {
        return NULL;
    }
    return (char*)arg_getContent(arg);
}

uint8_t* args_getBytes(Args* self, char* name) {
    if (NULL == self) {
        return NULL;
    }
    Arg* arg = args_getArg(self, name);
    if (NULL == arg) {
        return NULL;
    }
    if (NULL == arg_getContent(arg)) {
        return NULL;
    }
    return arg_getBytes(arg);
}

size_t args_getBytesSize(Args* self, char* name) {
    if (NULL == self) {
        return 0;
    }
    Arg* arg = args_getArg(self, name);
    if (NULL == arg) {
        return 0;
    }
    if (NULL == arg_getContent(arg)) {
        return 0;
    }
    return arg_getBytesSize(arg);
}

int32_t args_setInt(Args* self, char* name, int64_t int64In) {
    Arg* argNew = New_arg(NULL);
    argNew = arg_setInt(argNew, name, int64In);
    args_setArg(self, argNew);
    return 0;
}

int64_t args_getInt(Args* self, char* name) {
    Arg* arg = args_getArg(self, name);
    if (NULL == arg) {
        return -999999999;
    }
    ArgType arg_type = arg_getType(arg);
    if (arg_type == ARG_TYPE_INT) {
        return arg_getInt(arg);
    } else if (arg_type == ARG_TYPE_FLOAT) {
        return (int)arg_getFloat(arg);
    }
    return -999999999;
}

int32_t args_getSize(Args* self) {
    return link_getSize(self);
}

ArgType args_getType(Args* self, char* name) {
    Arg* arg = NULL;
    arg = args_getArg(self, name);
    if (NULL == arg) {
        return ARG_TYPE_NULL;
    }
    return arg_getType(arg);
}

float args_getFloat(Args* self, char* name) {
    Arg* arg = args_getArg(self, name);
    if (NULL == arg) {
        return -999999999.0;
    }
    ArgType arg_type = arg_getType(arg);
    if (arg_type == ARG_TYPE_FLOAT) {
        return arg_getFloat(arg);
    } else if (arg_type == ARG_TYPE_INT) {
        return (float)arg_getInt(arg);
    }
    return -999999999.0;
}

int32_t args_copyArg(Args* self, Arg* argToBeCopy) {
    if (NULL == argToBeCopy) {
        return 1;
    }
    Arg* argCopied = arg_copy(argToBeCopy);
    args_setArg(self, argCopied);

    return 0;
}

int32_t args_setStructWithSize(Args* self,
                               char* name,
                               void* struct_ptr,
                               uint32_t struct_size) {
    Arg* struct_arg = arg_setStruct(NULL, name, struct_ptr, struct_size);
    if (NULL == struct_arg) {
        /* faild */
        return 1;
    }
    args_setArg(self, struct_arg);
    return 0;
}

void* args_getStruct(Args* self, char* name) {
    Arg* struct_arg = args_getArg(self, name);
    return arg_getContent(struct_arg);
}

void* args_getHeapStruct(Args* self, char* name) {
    Arg* struct_arg = args_getArg(self, name);
    return arg_getHeapStruct(struct_arg);
}

int32_t args_setHeapStructWithSize(Args* self,
                                   char* name,
                                   void* struct_ptr,
                                   uint32_t struct_size,
                                   void* struct_deinit_fun) {
    Arg* struct_arg = arg_setHeapStruct(NULL, name, struct_ptr, struct_size,
                                        struct_deinit_fun);
    if (NULL == struct_arg) {
        /* faild */
        return 1;
    }
    args_setArg(self, struct_arg);
    return 0;
}

int32_t args_copyArgByName(Args* self, char* name, Args* directArgs) {
    Arg* argToBeCopy = args_getArg(self, name);
    args_copyArg(directArgs, argToBeCopy);
    return 0;
}

int32_t args_isArgExist_hash(Args* self, Hash nameHash) {
    if (NULL != args_getArg_hash(self, nameHash)) {
        return 1;
    }
    return 0;
}

int32_t args_isArgExist(Args* self, char* name) {
    if (NULL != args_getArg(self, name)) {
        return 1;
    }
    return 0;
}

int32_t __updateArg(Args* self, Arg* argNew) {
    LinkNode* nodeToUpdate = NULL;
    LinkNode* nodeNow = self->firstNode;
    LinkNode* priorNode = NULL;
    Hash nameHash = arg_getNameHash(argNew);
    while (1) {
        if (arg_getNameHash((Arg*)nodeNow) == nameHash) {
            nodeToUpdate = nodeNow;
            break;
        }
        if (arg_getNext((Arg*)nodeNow) == NULL) {
            // error, node no found
            goto exit;
        }
        priorNode = nodeNow;
        nodeNow = (LinkNode*)arg_getNext((Arg*)nodeNow);
    }

    arg_deinitHeap((Arg*)nodeToUpdate);

    nodeToUpdate = (LinkNode*)arg_setContent(
        (Arg*)nodeToUpdate, arg_getContent(argNew), arg_getContentSize(argNew));

    nodeToUpdate =
        (LinkNode*)arg_setType((Arg*)nodeToUpdate, arg_getType(argNew));
    // update privior link, because arg_getContent would free origin pointer
    if (NULL == priorNode) {
        self->firstNode = nodeToUpdate;
        goto exit;
    }

    arg_setNext((Arg*)priorNode, (Arg*)nodeToUpdate);
    goto exit;
exit:
    arg_freeContent(argNew);
    return 0;
}

int32_t args_setArg(Args* self, Arg* arg) {
    Hash nameHash = arg_getNameHash(arg);
    if (!args_isArgExist_hash(self, nameHash)) {
        args_pushArg(self, arg);
        return 0;
    }
    __updateArg(self, arg);
    return 0;
}

#ifndef __PIKA_CFG_HASH_LIST_CACHE_SIZE
#define __PIKA_CFG_HASH_LIST_CACHE_SIZE 4
#endif

LinkNode* args_getNode_hash(Args* self, Hash nameHash) {
    LinkNode* node = self->firstNode;
    int_fast8_t n = 0;
    while (NULL != node) {
        Arg* arg = (Arg*)node;
        Hash thisNameHash = arg_getNameHash(arg);
        if (thisNameHash == nameHash) {
            if (n > __PIKA_CFG_HASH_LIST_CACHE_SIZE) {
                /* the first __PIKA_CFG_HASH_LIST_CACHE_SIZE items in the list
                 * is considered as a cache.
                 * Don't make __PIKA_CFG_HASH_LIST_CACHE_SIZE too big, otherwise
                 * this optimisation is useless.
                 */

                /*! remove current node from the list */
                node = (LinkNode*)arg_getNext((Arg*)arg);

                /*! move the node to the cache */
                arg_setNext(arg, (Arg*)(self->firstNode));
                self->firstNode = (LinkNode*)arg;
            }
            return (LinkNode*)arg;
        }
        node = (LinkNode*)arg_getNext((Arg*)node);
    }
    return NULL;
}

LinkNode* args_getNode(Args* self, char* name) {
    return args_getNode_hash(self, hash_time33(name));
}

Arg* args_getArg_hash(Args* self, Hash nameHash) {
    LinkNode* node = args_getNode_hash(self, nameHash);
    if (NULL == node) {
        return NULL;
    }
    return (Arg*)node;
}

Arg* args_getArg(Args* self, char* name) {
    LinkNode* node = args_getNode(self, name);
    if (NULL == node) {
        return NULL;
    }
    return (Arg*)node;
}

Arg* args_getArg_index(Args* self, int index) {
    LinkNode* nodeNow = self->firstNode;
    if (NULL == nodeNow) {
        return NULL;
    }
    for (int i = 0; i < index; i++) {
        nodeNow = (LinkNode*)arg_getNext((Arg*)nodeNow);
    }
    return (Arg*)nodeNow;
}

char* getPrintSring(Args* self, char* name, char* valString) {
    Args buffs = {0};
    char* printName = strsFormat(&buffs, 128, "[printBuff]%s", name);
    char* printString = strsCopy(&buffs, valString);
    args_setStr(self, printName, printString);
    char* res = args_getStr(self, printName);
    strsDeinit(&buffs);
    return res;
}

char* getPrintStringFromInt(Args* self, char* name, int32_t val) {
    Args buffs = {0};
    char* res = NULL;
    char* valString = strsFormat(&buffs, 32, "%d", val);
    res = getPrintSring(self, name, valString);
    strsDeinit(&buffs);
    return res;
}

char* getPrintStringFromFloat(Args* self, char* name, float val) {
    Args buffs = {0};
    char* res = NULL;
    char* valString = strsFormat(&buffs, 32, "%f", val);
    res = getPrintSring(self, name, valString);
    strsDeinit(&buffs);
    return res;
}

char* getPrintStringFromPtr(Args* self, char* name, void* val) {
    Args buffs = {0};
    char* res = NULL;
    uint64_t intVal = (uintptr_t)val;
    char* valString = strsFormat(&buffs, 32, "0x%llx", intVal);
    res = getPrintSring(self, name, valString);
    strsDeinit(&buffs);
    return res;
}

char* args_print(Args* self, char* name) {
    char* res = NULL;
    ArgType type = args_getType(self, name);
    Args buffs = {0};
    if (ARG_TYPE_NONE == type) {
        /* can not get arg */
        res = NULL;
        goto exit;
    }

    if (type == ARG_TYPE_INT) {
        int32_t val = args_getInt(self, name);
        res = getPrintStringFromInt(self, name, val);
        goto exit;
    }

    if (type == ARG_TYPE_FLOAT) {
        float val = args_getFloat(self, name);
        res = getPrintStringFromFloat(self, name, val);
        goto exit;
    }

    if (type == ARG_TYPE_STRING) {
        res = args_getStr(self, name);
        goto exit;
    }

    if (type == ARG_TYPE_OBJECT) {
        void* val = args_getPtr(self, name);
        res = getPrintStringFromPtr(self, name, val);
        goto exit;
    }

    /* can not match type */
    res = NULL;
    goto exit;

exit:
    strsDeinit(&buffs);
    return res;
}

int32_t args_setPtrWithType(Args* self,
                            char* name,
                            ArgType type,
                            void* objPtr) {
    Arg* argNew = New_arg(NULL);
    argNew = arg_setPtr(argNew, name, type, objPtr);
    args_setArg(self, argNew);
    return 0;
}

int32_t args_foreach(Args* self,
                     int32_t (*eachHandle)(Arg* argEach, Args* context),
                     Args* context) {
    if (NULL == self->firstNode) {
        return 0;
    }
    LinkNode* nodeNow = self->firstNode;
    while (1) {
        Arg* argNow = (Arg*)nodeNow;
        if (NULL == argNow) {
            continue;
        }
        LinkNode* nextNode = (LinkNode*)arg_getNext((Arg*)nodeNow);
        eachHandle(argNow, context);

        if (NULL == nextNode) {
            break;
        }
        nodeNow = nextNode;
    }
    return 0;
}

int32_t args_removeArg(Args* self, Arg* argNow) {
    if (NULL == argNow) {
        /* can not found arg */
        return 1;
    }
    link_removeNode(self, argNow);
    return 0;
}

int32_t args_removeArg_notDeinitArg(Args* self, Arg* argNow) {
    if (NULL == argNow) {
        /* can not found arg */
        return 1;
    }
    link_removeNode_notDeinitNode(self, argNow);
    return 0;
}

int args_moveArg(Args* self, Args* dict, Arg* argNow) {
    if (NULL == argNow) {
        /* can not found arg */
        return 1;
    }
    link_removeNode_notDeinitNode(self, argNow);
    args_pushArg(dict, argNow);
    return 0;
}

Args* New_args(Args* args) {
    Args* self = New_link(NULL);
    return self;
}
