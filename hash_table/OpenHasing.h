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

void OpenHasingInit(OpenHash *OpHash, int (*fun)(unsigned int , DataType), int _PrimeNum);//��ʼ��
void OpenHasingAddElement(OpenHash *OpHash, int loc); //���ӽ��, ͷ�巨
void OpenHasingInsert(OpenHash *OpHash, DataType data);//����Ԫ��
int OpenHasingDelete(OpenHash *OpHash, DataType data);//ɾ��Ԫ��
int OpenHasingFindElement(const OpenHash *OpHash, const DataType data);//����Ԫ��
int OpenHasingElementCount(const OpenHash *OpHash); //��ȡ��ɢ��������Ԫ�صĸ���
int CheckOpenHasingIsEmpty(const OpenHash *OpHash); //�жϿ�ɢ���Ƿ�Ϊ��,��Ϊ���򷵻�0.
void OpenHasingDestory(OpenHash *OpHash); //���ٿ�ɢ��

void OpenHasingTest(); //���Կ�ɢ��


#endif
