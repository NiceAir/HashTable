#ifndef _OPEN_HASING_H
#define _OPEN_HASING_H
#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "commom.h"
typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node *Next;
}Node;

typedef struct HashBucket{
    Node *pNode;
}HashBucket;

typedef struct Hash{
    unsigned int capacity;
    HashBucket *_HashBucket;
    int (*fun)(unsigned int, DataType);
}OpenHash;

void OpenHasingInit(OpenHash *OpHash, int (*fun)(unsigned int , DataType), int _PrimeNum);//初始化
void OpenHasingAddElement(OpenHash *OpHash, int loc); //增加结点, 头插法
void OpenHasingInsert(OpenHash *OpHash, DataType data);//插入元素
int OpenHasingDelete(OpenHash *OpHash, DataType data);//删除元素
int OpenHasingFindElement(const OpenHash *OpHash, const DataType data);//查找元素
int OpenHasingElementCount(const OpenHash *OpHash); //获取开散列中所有元素的个数
int CheckOpenHasingIsEmpty(const OpenHash *OpHash); //判断开散列是否为空,若为空则返回0.
void OpenHasingDestory(OpenHash *OpHash); //销毁开散列

void OpenHasingTest(); //测试开散列


#endif
