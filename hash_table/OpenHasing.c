#include "OpenHasing.h"

static int HashFunction(unsigned int capacity, DataType data) //��ϣ����
{
    return data % capacity;
}

void OpenHasingInit(OpenHash *OpHash, int (*fun)(unsigned int, DataType), int _PrimeNum)//��ʼ��
{
    unsigned int i;
    assert(OpHash);
    OpHash->capacity = _PrimeList[_PrimeNum];
    OpHash->fun = fun;
    OpHash->_HashBucket = (HashBucket *)malloc(sizeof(HashBucket)*OpHash->capacity);
    if (OpHash->_HashBucket == NULL)
    {
        perror("malloc");
        printf(" ��ʼ��ʧ��\n");
        exit(-1);
    }
    for (i = 0; i<OpHash->capacity; i++)
    {
        OpHash->_HashBucket[i].pNode = NULL;
    }  
}


void OpenHasingAddElement(OpenHash *OpHash, int loc) //���ӽ��, ͷ�巨
{
    Node *cur = NULL;
    Node *cache = OpHash->_HashBucket[loc].pNode;
    assert(OpHash);
    cur = (Node *)malloc(sizeof(Node));
    if (cur == NULL)
    {
        perror("malloc");
        printf(" ���ӽ��ʧ��\n");
        exit(-1);
    }
    OpHash->_HashBucket[loc].pNode = cur;
    cur->Next = cache;    
}

void OpenHasingInsert(OpenHash *OpHash, DataType data)//����Ԫ��
{
    int loc = 0;
    assert(OpHash);
    loc  = OpHash->fun(OpHash->capacity,data);

    if (OpHash->_HashBucket[loc].pNode->data == data)
        return;
    
    OpenHasingAddElement(OpHash, loc);
    OpHash->_HashBucket[loc].pNode->data = data;
    
}

int  OpenHasingDelete(OpenHash *OpHash, DataType data)//ɾ��Ԫ��, ɾ���ɹ�����1,ʧ�ܷ���-1
{
    Node *pre = NULL;
    Node *cur = NULL;
    int loc = OpHash->fun(OpHash->capacity, data); //�ҵ�Ԫ������Ͱ��λ��
    assert(OpHash);
    pre = OpHash->_HashBucket[loc].pNode;
    cur = OpHash->_HashBucket[loc].pNode;
    while(cur)
    {
        if (cur->data == data)
        {
            break;
        }
        pre = cur;
        cur = cur->Next;
    }
    if (cur == OpHash->_HashBucket[loc].pNode)
    {
        OpHash->_HashBucket[loc].pNode = NULL;
    }
    else if (cur != NULL)
    {
        pre->Next = cur->Next;
        free(cur);
        
        return 1;
    }
   return -1;
}

int OpenHasingFindElement(const OpenHash *OpHash, const DataType data)//����Ԫ��
{
    Node *cur = NULL;
    int loc = OpHash->fun(OpHash->capacity, data);
    assert(OpHash);
    cur = OpHash->_HashBucket[loc].pNode;
    while(cur)
    {
        if (cur->data == data)
        {
            break;
        }
        cur = cur->Next;
    }
    if (cur != NULL)
        return 1;
    return 0;
}

int OpenHasingElementCount(const OpenHash *OpHash) //��ȡ��ɢ��������Ԫ�صĸ���
{
    int count = 0;
    unsigned int i = 0;
    assert(OpHash);
    for (i = 0; i<OpHash->capacity; i++)
    {
        Node *cur = OpHash->_HashBucket[i].pNode;
        while(cur)
        {
            count++;
            cur = cur->Next;
        }
    }
    return count;
}

int CheckOpenHasingIsEmpty(const OpenHash *OpHash) //�жϿ�ɢ���Ƿ�Ϊ��,��Ϊ���򷵻�0.
{
    unsigned int i = 0;
    for (i = 0; i<OpHash->capacity; i++)
    {
        if (OpHash->_HashBucket[i].pNode != NULL)
        {
            return 1;
        }
    }
    return 0;
}

void OpenHasingDestory(OpenHash *OpHash) //���ٿ�ɢ��
{
    Node *cur;
    Node *destory;
    unsigned int loc;
    for (loc = 0; loc<OpHash->capacity; loc++)
    {
        cur = OpHash->_HashBucket[loc].pNode;
        while(cur)
        {
            destory = cur;
            cur = cur->Next;
            free(destory);
        }
    }
    free(OpHash->_HashBucket);
    OpHash->capacity = 0;
}


void OpenHasingTest() //���Կ�ɢ��
{
    int a[] = {37, 25, 14, 36, 49, 68, 57, 11};
    int i;
    OpenHash Ophash;
    OpenHasingInit(&Ophash, HashFunction, 0);
    for (i = 0; i<sizeof(a)/sizeof(int); i++)
    {
        printf("����%dǰ����ϣ������%d��Ԫ��\n", a[i], OpenHasingElementCount(&Ophash));
        OpenHasingInsert(&Ophash, a[i]);
        if (CheckOpenHasingIsEmpty(&Ophash))
        {
            int j = OpenHasingElementCount(&Ophash);
            printf("����%d�󣬹�ϣ������%d��Ԫ��\n\n", a[i], j);
        }     
    }

    for (i = 0; i<80; i++)
    {
        if (OpenHasingFindElement(&Ophash, i))
        {
            printf("%d��\n", i);
        }
    }
    
    printf("\n\n");
    for (i = 8; i<30; i++)
    {
        printf("׼��ɾ��%d�� ��ʱ��%d��Ԫ��\n", i, OpenHasingElementCount(&Ophash));
        if (OpenHasingDelete(&Ophash, i) == 1)
        {
            printf("ɾ��%d�ɹ��� ��ʱ��ϣ���л�ʣ%d��Ԫ��\n\n", i, OpenHasingElementCount(&Ophash));
        }
        else
        {
            printf("ɾ��%dʧ�ܣ� ��ʱ��ϣ���л���%d��Ԫ��\n\n", i, OpenHasingElementCount(&Ophash));
        }
    }
    printf("���ٹ�ϣ��ǰ�����л���%d��Ԫ��\n", OpenHasingElementCount(&Ophash));
    OpenHasingDestory(&Ophash);
    printf("���ٺ󣬻���%d��Ԫ��\n", OpenHasingElementCount(&Ophash));
}