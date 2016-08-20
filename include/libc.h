#ifndef __LIBC_H__
#define __LIBC_H__

#include <types.h>

/* __aeabi_ldiv0 will call raise */
s32 raise(s32 signum);
u32 strlen(const char *str);
s32 strcmp(char *s1, char *s2);
u32 atoi(char *str);
void *memset(void *s, s32 c, u32 size);
void *memcpy(void *dst, void *src, u32 size);
char * itoa(char *buf, u32 x, u32 radix);
int vsnprintf(char *buf, u32 size, const char *fmt, va_list args);
int snprintf(char *buf, u32 size, const char *fmt, ...);
u16 cyg_crc16(unsigned char *buf, int len);

#endif /* __LIBC_H__ */
