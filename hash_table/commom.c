#include "commom.h"
size_t BKDRHash1(const char * str) //字符串转无符号整型
{
    unsigned int seed = 131; // 31 131 1313 13131 131313
    unsigned int hash = 0;
    while (*str )
    {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
} 

