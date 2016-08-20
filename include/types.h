#ifndef __TYPES_H__
#define __TYPES_H__

#define PUBLIC  /* __attribute__((weak)) */
#define PRIVATE /* static                */

#define NULL ((void*)0)

typedef char* va_list;

#define __va_size(type) \
       (((sizeof(type) + sizeof(long) - 1) / sizeof (long)) * sizeof (long))

#define va_start(ap, last) \
       ((ap) = ((char*)&last) + __va_size(last))

#define va_arg(ap, type) \
       (*(type*)((ap)+= __va_size(type), (ap) - __va_size(type)))

#define va_end(va_list) ((void)0)

typedef signed   char s8;
typedef unsigned char u8;

typedef signed   short s16;
typedef unsigned short u16;

typedef signed   int s32;
typedef unsigned int u32;

typedef signed   long long s64;
typedef unsigned long long u64;

typedef s32 (*func_0)();
typedef s32 (*func_1)(u32 arg1);
typedef s32 (*func_2)(u32 arg1, u32 arg2);
typedef s32 (*func_3)(u32 arg1, u32 arg2, u32 arg3);
typedef s32 (*func_4)(u32 arg1, u32 arg2, u32 arg3, u32 arg4);
typedef s32 (*func_5)(u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5);

enum {
    OK = 0,
    ERROR,
    EINVAL, /* invalid parameter */
    ENOMEM, /* out of memory */
};

#endif /* __TYPES_H__ */
