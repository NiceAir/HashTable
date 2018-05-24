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
    unsigned int capacity;  //��ɢ��������
    unsigned int count;     //��ЧԪ�صĸ���
    int _load_factor;       //��������
    Element *elements;      //��ϣ��
    int _PrimeNum;          //�������
    unsigned int (*Hashfunc)(unsigned int, DataType);   //��ϣ����
}CloseHash;

void CloseHasingInit(CloseHash *ClHash, unsigned int (*func)(unsigned int, DataType));//��ʼ��
int CloseHasingFindElement(const CloseHash *ClHash, DataType data);//����Ԫ�أ�����̽�⣩,���ҳɹ����ظ�Ԫ�صĽ���λ��,ʧ�ܷ���-1
void CloseHasingInsert(CloseHash *ClHash, DataType data);//����Ԫ��(�������ӡ�����̽��)
int CloseHasingDelete(CloseHash *ClHash, DataType data);//ɾ��Ԫ��,ɾ���ɹ�����1��ʧ�ܷ���-1
int CloseHasingCount(const CloseHash *ClHash);//ͳ����ЧԪ�ظ���
int CheckCloseHasingIsEmpty(const CloseHash *ClHash);//�жϹ�ϣ���Ƿ�Ϊ��,Ϊ�շ���1
void CloseHasingDestory(CloseHash *ClHash);//���ٹ�ϣ��
void CloseHasingTest();  //���Ա�ɢ��

#endif