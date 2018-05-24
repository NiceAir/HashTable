#ifndef _CLOSE_HASING_H
#define _CLOSE_HASING_H
#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "commom.h"

typedef int DataType;

typedef enum{
    EMPTY,
    DELETE,
    FULL
}ElementStatus;

typedef struct Element{
    DataType data;
    ElementStatus status;
}Element;

typedef struct CloseHash{
    unsigned int capacity;  //闭散列总容量
    unsigned int count;     //有效元素的个数
    int _load_factor;       //负载因子
    Element *elements;      //哈希表
    int _PrimeNum;          //质数标号
    unsigned int (*Hashfunc)(unsigned int, DataType);   //哈希函数
}CloseHash;

void CloseHasingInit(CloseHash *ClHash, unsigned int (*func)(unsigned int, DataType));//初始化
int CloseHasingFindElement(const CloseHash *ClHash, DataType data);//查找元素（二次探测）,查找成功返回该元素的结点的位置,失败返回-1
void CloseHasingInsert(CloseHash *ClHash, DataType data);//插入元素(负载因子、二次探测)
int CloseHasingDelete(CloseHash *ClHash, DataType data);//删除元素,删除成功返回1，失败返回-1
int CloseHasingCount(const CloseHash *ClHash);//统计有效元素个数
int CheckCloseHasingIsEmpty(const CloseHash *ClHash);//判断哈希表是否为空,为空返回1
void CloseHasingDestory(CloseHash *ClHash);//销毁哈希表
void CloseHasingTest();  //测试闭散列

#endif