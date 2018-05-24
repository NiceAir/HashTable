#ifndef _COMMOM_H
#define _COMMOM_H
#pragma once
#include <stdio.h>
size_t BKDRHash1(const char * str); //字符串转无符号整型

// 使用素数表对齐做哈希表的容量，降低哈希冲突
#define _PrimeSize 30
static const unsigned long _PrimeList [_PrimeSize] =
{
    7ul,19ul,53ul, 97ul, 193ul, 389ul, 769ul,
    1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
    49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
    1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
    50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
    1610612741ul, 3221225473ul, 4294967291ul
};


#endif