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

#ifndef _arg__H
#define _arg__H
#include "dataLink.h"
#include "dataMemory.h"

typedef uint32_t Hash;
typedef enum {
    ARG_TYPE_UNDEF = 0,
    ARG_TYPE_NONE,
    ARG_TYPE_VOID,
    ARG_TYPE_NULL,
    ARG_TYPE_INT,
    ARG_TYPE_FLOAT,
    ARG_TYPE_POINTER,
    ARG_TYPE_STRING,
    ARG_TYPE_OBJECT,
    ARG_TYPE_MATE_OBJECT,
    ARG_TYPE_FREE_OBJECT,
    ARG_TYPE_NATIVE_METHOD,
    ARG_TYPE_NATIVE_CONSTRUCTOR_METHOD,
    ARG_TYPE_CONSTRUCTOR_METHOD,
    ARG_TYPE_OBJECT_METHOD,
    ARG_TYPE_STATIC_METHOD,
    ARG_TYPE_STRUCT,
    ARG_TYPE_HEAP_STRUCT,
} ArgType;

typedef void (*StructDeinitFun)(void* struct_);

typedef struct __arg __arg;
struct __arg {
    __arg* next;
    uint16_t size;
    uint8_t type;
    uint8_t __rsvd;
    Hash name_hash;
    uint8_t content[];
};

typedef uint8_t Arg;

// uint32_t content_getNameHash(uint8_t* content);
#define content_getNameHash(__addr) (((__arg*)(__addr))->name_hash)

ArgType content_getType(uint8_t* self);

#define content_getNext(__addr) ((uint8_t*)(((__arg*)(__addr))->next))

#define content_getSize(__addr) ((uint16_t)(((__arg*)(__addr))->size))

#define content_getContent(__addr) (((__arg*)(__addr))->content)

uint16_t content_totleSize(uint8_t* self);

uint8_t* content_deinit(uint8_t* self);

uint8_t* content_setName(uint8_t* self, char* name);
uint8_t* content_setType(uint8_t* self, ArgType type);
uint8_t* content_setContent(uint8_t* self, uint8_t* content, uint16_t size);
// void content_setNext(uint8_t* self, uint8_t* next);

#define content_setNext(__addr, __next)                \
    do {                                               \
        (((__arg*)(__addr))->next) = (__arg*)(__next); \
    } while (0)

uint16_t arg_getTotleSize(Arg* self);
void arg_freeContent(Arg* self);

Arg* arg_setName(Arg* self, char* name);
Arg* arg_setContent(Arg* self, uint8_t* content, uint32_t size);
Arg* arg_newContent(Arg* self, uint32_t size);
Arg* arg_setType(Arg* self, ArgType type);
Hash arg_getNameHash(Arg* self);
ArgType arg_getType(Arg* self);
uint16_t arg_getContentSize(Arg* self);
Hash hash_time33(char* str);

Arg* arg_setInt(Arg* self, char* name, int64_t val);
Arg* arg_setFloat(Arg* self, char* name, float val);
Arg* arg_setPtr(Arg* self, char* name, ArgType type, void* pointer);
Arg* arg_setStr(Arg* self, char* name, char* string);
Arg* arg_setNull(Arg* self);

int64_t arg_getInt(Arg* self);
float arg_getFloat(Arg* self);
void* arg_getPtr(Arg* self);
char* arg_getStr(Arg* self);
Arg* arg_copy(Arg* argToBeCopy);

#define arg_getContent(self) ((uint8_t*)content_getContent((self)))

Arg* arg_init(Arg* self, void* voidPointer);
void arg_deinit(Arg* self);

Arg* New_arg(void* voidPointer);
Arg* arg_append(Arg* arg_in, void* new_content, size_t new_size);
Arg* arg_setStruct(Arg* self,
                   char* name,
                   void* struct_ptr,
                   uint32_t struct_size);
Arg* arg_setHeapStruct(Arg* self,
                       char* name,
                       void* struct_ptr,
                       uint32_t struct_size,
                       void* struct_deinit_fun);
void* arg_getHeapStruct(Arg* self);
void arg_deinitHeap(Arg* self);

#endif
