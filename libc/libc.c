#include <libc.h>
#include <types.h>

/* Table of CRC constants - implements x^16+x^12+x^5+1 */
static const u16 crc16_tab[] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
    0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
    0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
    0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
    0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
    0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
    0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
    0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
    0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
    0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
    0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
    0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
    0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
    0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
    0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
    0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
    0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
    0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
    0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0,
};

/* __aeabi_ldiv0 will call raise */
s32 raise(s32 signum)
{
    while(1);
    return 0;
}

u32 strlen(const char *str)
{
    u32 i = 0;
    while(str[i] != '\0') {
        i++;
    }
    return i;
}

s32 strcmp(char *s1, char *s2)
{
    u32 i;
    s32 delta;

    if (s1 == NULL && s2 == NULL) {
        return 0;
    }

    if (s1 == NULL && s2 != NULL) {
        return 1;
    }

    if (s1 != NULL && s2 == NULL) {
        return -1;
    }

    /* s1 != NULL && s2 != NULL */
    for(i=0; s1[i]!= '\0' && s2[i] != '\0'; i++) {
        delta = s1[i] - s2[i];
        if (delta != 0) {
            return delta;
        }
    }

    return s1[i] - s2[i];
}

u32 atoi(char *str)
{
    u32 i;
    u32 len;
    u32 sum = 0;

    len = strlen(str);
    if (len == 0) {
        return 0;
    }

    if (len >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {    /* hex */
        i = 2;
        while(i < len) {
            switch(str[i]) {

                case ('a'): case ('b'): case ('c'): case ('d'): case ('e'): case ('f'):
                    sum = sum*16 + (str[i] - 'a' + 10);
                    break;

                case ('A'): case ('B'): case ('C'): case ('D'): case ('E'): case ('F'):
                    sum = sum*16 + (str[i] - 'A' + 10);
                    break;

                case ('0'): case ('1'): case ('2'): case ('3'): case ('4'):
                case ('5'): case ('6'): case ('7'): case ('8'): case ('9'):
                    sum = sum*16 + (str[i] - '0');
                    break;

                default:
                    return 0;

            }
            i++;
        }
    } else {    /* dec */
        i = 0;
        while(i < len) {
            switch(str[i]) {

                case ('0'): case ('1'): case ('2'): case ('3'): case ('4'):
                case ('5'): case ('6'): case ('7'): case ('8'): case ('9'):
                    sum = sum*10 + (str[i] - '0');
                    break;

                default:
                    return 0;

            }
            i++;
        }

    }
    return sum;
}

void *memset(void *s, s32 c, u32 size)
{
    u32 i;
    char *_s = (char*)s;
    for(i=0;i<size;i++) {
        _s[i] = c;
    }
    return s;
}

void *memcpy(void *dst, void *src, u32 size)
{
    u32 i;
    u8 *_dst, *_src;

    _dst = (u8 *)dst;
    _src = (u8 *)src;
    for(i=0;i<size;i++) {
        _dst[i] = _src[i];
    }
    return dst;
}

PRIVATE u32 buf_putc(char *buf, u32 size, u32 *offset, u8 c)
{
    u32 off = *offset;
    if (off < size) {
        buf[off] = c;
        *offset = off + 1;
    }
    return 0;
}

PRIVATE u32 buf_puts(char *buf, u32 size, u32 *offset, char *s)
{
    u32 i;
    for(i=0;s[i]!='\0';i++) {
        buf_putc(buf, size, offset, s[i]);
    }
    return 0;
}

/* buf size: 10 if radix == 10; 8 if radix == 16 */
PUBLIC char * itoa(char *buf, u32 x, u32 radix)
{
    s32 i;
    memset(buf, 0, 10);

    for(i=9;i>=0;i--) {
        switch (radix) {
            case (10):
                buf[i] =(x % radix) + '0';
                x = x / radix ;
                break;
            case (16):
                if ((x % radix) < 10) {
                    buf[i] = (x % radix) + '0';
                } else {
                    buf[i] = (x % radix) - 10 + 'A';
                }
                x = x / radix ;
                break;
            default:
                return NULL;
        }
    }
    for(i=0;i<9;i++) {
        if (buf[i] != '0') {
            break;
        }
    }


    return &buf[i];

}

/* as simple as possible, only support %c %d %x %X(not omit the high '0') %s, and don't care the negative num */
/* of course, I don't care the efficiency as well */
/* return: the strlen(string), that is, not include the '\0' */
PUBLIC int vsnprintf(char *buf, u32 size, const char *fmt, va_list args)
{
    u32 i, offset, len;
    u8  c;
    u32 d, x;
    char *s, *b;

    char num[11]; /* 2^32 = 4294967296 + '\0' */

    offset = 0;
    memset(buf, 0, size);
    memset(num, 0, sizeof(num));
    len = strlen(fmt);

    for(i=0;i<len;i++) {
        if (fmt[i] == '%') {
            if ((i+1) == len) { /* % is the last char of the string */
                buf_putc(buf, size, &offset, fmt[i]);
                break;
            } else {
                switch (fmt[i+1]) {
                    case ('c'):
                        c = va_arg(args, u32);
                        buf_putc(buf, size, &offset, c);
                        i++;
                        break;
                    case ('d'):
                        d = va_arg(args, u32);
                        b = itoa(num, d, 10);
                        buf_puts(buf, size, &offset, b);
                        i++;
                        break;
                    case ('x'):
                    case ('X'):
                        x = va_arg(args, u32);
                        b = itoa(num, x, 16);
                        if (fmt[i+1] == 'X') { b = &num[2]; };
                        buf_puts(buf, size, &offset, b);
                        i++;
                        break;
                    case ('s'):
                        s = va_arg(args, char *);
                        b = s;
                        if (b == NULL) {
                            buf_puts(buf, size, &offset, "(null)");
                        } else {
                            buf_puts(buf, size, &offset, b);
                        }
                        i++;
                        break;
                    default:
                        buf_putc(buf, size, &offset, fmt[i]);   /* the '%' */
                        break;
                }
            }
        } else {
            /*  ordinary character */
            buf_putc(buf, size, &offset, fmt[i]);
        }
    }

    buf[size-1] = '\0';
    return offset; /* FIXME: return the length of c string (strlen(string), not include the '\0') */
}


PUBLIC int snprintf(char *buf, u32 size, const char *fmt, ...)
{
    u32 len;
    va_list args;

    va_start(args, fmt);
    len = vsnprintf(buf, size, fmt, args);
    va_end(args);

    return len;
}

PUBLIC u16 cyg_crc16(unsigned char *buf, int len)
{
    int i;
    u16 cksum;

    cksum = 0;
    for (i = 0;  i < len;  i++) {
	cksum = crc16_tab[((cksum>>8) ^ *buf++) & 0xFF] ^ (cksum << 8);
    }
    return cksum;
}
