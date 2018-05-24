#include "OpenHasing.h"

static int HashFunction(unsigned int capacity, DataType data) //哈希函数
{
    return data % capacity;
}

void OpenHasingInit(OpenHash *OpHash, int (*fun)(unsigned int, DataType), int _PrimeNum)//初始化
{
    unsigned int i;
    assert(OpHash);
    OpHash->capacity = _PrimeList[_PrimeNum];
    OpHash->fun = fun;
    OpHash->_HashBucket = (HashBucket *)malloc(sizeof(HashBucket)*OpHash->capacity);
    if (OpHash->_HashBucket == NULL)
    {
        perror("malloc");
        printf(" 初始化失败\n");
        exit(-1);
    }
    for (i = 0; i<OpHash->capacity; i++)
    {
        OpHash->_HashBucket[i].pNode = NULL;
    }  
}


void OpenHasingAddElement(OpenHash *OpHash, int loc) //增加结点, 头插法
{
    Node *cur = NULL;
    Node *cache = OpHash->_HashBucket[loc].pNode;
    assert(OpHash);
    cur = (Node *)malloc(sizeof(Node));
    if (cur == NULL)
    {
        perror("malloc");
        printf(" 增加结点失败\n");
        exit(-1);
    }
    OpHash->_HashBucket[loc].pNode = cur;
    cur->Next = cache;    
}

void OpenHasingInsert(OpenHash *OpHash, DataType data)//插入元素
{
    int loc = 0;
    assert(OpHash);
    loc  = OpHash->fun(OpHash->capacity,data);

    if (OpHash->_HashBucket[loc].pNode->data == data)
        return;
    
    OpenHasingAddElement(OpHash, loc);
    OpHash->_HashBucket[loc].pNode->data = data;
    
}

int  OpenHasingDelete(OpenHash *OpHash, DataType data)//删除元素, 删除成功返回1,失败返回-1
{
    Node *pre = NULL;
    Node *cur = NULL;
    int loc = OpHash->fun(OpHash->capacity, data); //找到元素所在桶的位置
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

int OpenHasingFindElement(const OpenHash *OpHash, const DataType data)//查找元素
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

int OpenHasingElementCount(const OpenHash *OpHash) //获取开散列中所有元素的个数
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

int CheckOpenHasingIsEmpty(const OpenHash *OpHash) //判断开散列是否为空,若为空则返回0.
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

void OpenHasingDestory(OpenHash *OpHash) //销毁开散列
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


void OpenHasingTest() //测试开散列
{
    int a[] = {37, 25, 14, 36, 49, 68, 57, 11};
    int i;
    OpenHash Ophash;
    OpenHasingInit(&Ophash, HashFunction, 0);
    for (i = 0; i<sizeof(a)/sizeof(int); i++)
    {
        printf("插入%d前，哈希表中有%d个元素\n", a[i], OpenHasingElementCount(&Ophash));
        OpenHasingInsert(&Ophash, a[i]);
        if (CheckOpenHasingIsEmpty(&Ophash))
        {
            int j = OpenHasingElementCount(&Ophash);
            printf("插入%d后，哈希表中有%d个元素\n\n", a[i], j);
        }     
    }

    for (i = 0; i<80; i++)
    {
        if (OpenHasingFindElement(&Ophash, i))
        {
            printf("%d在\n", i);
        }
    }
    
    printf("\n\n");
    for (i = 8; i<30; i++)
    {
        printf("准备删除%d， 此时有%d个元素\n", i, OpenHasingElementCount(&Ophash));
        if (OpenHasingDelete(&Ophash, i) == 1)
        {
            printf("删除%d成功， 此时哈希表中还剩%d个元素\n\n", i, OpenHasingElementCount(&Ophash));
        }
        else
        {
            printf("删除%d失败， 此时哈希表中还有%d个元素\n\n", i, OpenHasingElementCount(&Ophash));
        }
    }
    printf("销毁哈希表前，表中还有%d个元素\n", OpenHasingElementCount(&Ophash));
    OpenHasingDestory(&Ophash);
    printf("销毁后，还有%d个元素\n", OpenHasingElementCount(&Ophash));
}