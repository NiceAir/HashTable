#include "CloseHasing.h"

static unsigned int Hashfunc(unsigned int capacity, DataType data)  //哈希函数
{
    return data % capacity;
}

void CloseHasingInit(CloseHash *ClHash, unsigned int (*func)(unsigned int, DataType))//初始化
{
    int i = 0;
    assert(ClHash); 
    ClHash->_PrimeNum = 0;
    ClHash->elements  = (Element *)malloc(sizeof(Element)*_PrimeList[ClHash->_PrimeNum]);
    if (ClHash->elements == NULL)
    {
        perror("malloc");
        printf("初始化失败\n");
        exit(-1);
    }
    ClHash->capacity = _PrimeList[ClHash->_PrimeNum];
    ClHash->count = 0;
    ClHash->_load_factor = 0;
    ClHash->Hashfunc = func;
    for (i = 0; i<_PrimeList[ClHash->_PrimeNum]; i++)
    {
        ClHash->elements[i].status = EMPTY;
    }
    
}

static void CloseHasingEnlargeCapacity(CloseHash *ClHash)    //扩容
{
    Element * cache = NULL;
    int i;
    int capacity = ClHash->capacity;
    assert(ClHash);
    cache = (Element *)realloc(ClHash->elements, sizeof(Element)*_PrimeList[ClHash->_PrimeNum+1]);
    if (cache == NULL)
    {
        perror("realloc");
        printf("扩容失败\n");
        exit(-1);
    }

    ClHash->elements = cache;
    ClHash->_PrimeNum++;
    ClHash->capacity = _PrimeList[ClHash->_PrimeNum];
    for (i = capacity; i<ClHash->capacity; i++)
    {
        ClHash->elements[i].status = EMPTY;
    }
}

static int ComputingLoadFactor(unsigned int all, unsigned int used) //求负载因子
{
    return used*10/all;
}

int CloseHasingFindElement(const CloseHash *ClHash, DataType data)//查找元素（二次探测）,查找成功返回该元素的结点的位置,失败返回-1
{
    int loc[4];
    int count = 0;
    loc[0] = ClHash->Hashfunc(ClHash->capacity, data); //local[0] 存放起始位置
    loc[1] = loc[0]; //loc[1]存放起始位置的右侧位置
    loc[2] = loc[0]; //loc[2]存放起始位置的左侧位置
    loc[3] = 1; //标记该loc[1]走还是该loc[2]走
    while(count <= (ClHash->capacity + 2))
    {
        if (loc[3] == 1)
        {
            if (ClHash->elements[loc[1]].status == FULL)
                if (ClHash->elements[loc[1]].data == data)
                    return loc[1]; 
            if (loc[1] == ClHash->capacity-1)
                loc[1] = 0;
            else
                loc[1]++;
            loc[3] = 2;
        }
        else
        {
            if (ClHash->elements[loc[2]].status == FULL)
                if (ClHash->elements[loc[2]].data == data)
                    return loc[2];
            if (loc[2] == 0)
                loc[2] = ClHash->capacity - 1;
            else
                loc[2]--;
            loc[3] = 1;
        }
        count++;
    }
    return -1;
}

void CloseHasingInsert(CloseHash *ClHash, DataType data)//插入元素
{
    int loc[4];
    assert(ClHash);
    if (CloseHasingFindElement(ClHash, data) != -1)    //先看这个哈希表中是否存在该元素（二次探测）
        return;

    if (ClHash->_load_factor >= 7)  //若需扩容，则扩容
        CloseHasingEnlargeCapacity(ClHash);
    
    //选择一个合适的位置插入（二次探测）
    loc[0] = ClHash->Hashfunc(ClHash->capacity, data); //local[0] 存放起始位置
    loc[1] = loc[0]; //loc[1]存放起始位置的右侧位置
    loc[2] = loc[0]; //loc[2]存放起始位置的左侧位置
    loc[3] = 1; //标记该loc[1]走还是该loc[2]走

    while(1)
    {
        if (loc[3] == 1)
        {
            if (ClHash->elements[loc[1]].status == EMPTY)
            {
                ClHash->elements[loc[1]].data = data;
                ClHash->elements[loc[1]].status = FULL;
                break;
            }
            else
            {
                if (loc[1] == ClHash->capacity-1)
                    loc[1] = 0;
                else
                    loc[1]++;
                loc[3] = 2;
            }
        }
        else
        {
            if (ClHash->elements[loc[2]].status == EMPTY)
            {
                ClHash->elements[loc[2]].data = data;
                ClHash->elements[loc[2]].status = FULL;
                break;
            }
            else
            {
                if (loc[2] == 0)
                    loc[2] = ClHash->capacity - 1;
                else
                    loc[2]--;
                loc[3] = 1;
            }
        }
    }
    ClHash->count++;
    ClHash->_load_factor = ComputingLoadFactor(ClHash->capacity, ClHash->count);
}

int CloseHasingDelete(CloseHash *ClHash, DataType data)//删除元素,删除成功返回1，失败返回-1
{
    int loc = CloseHasingFindElement(ClHash, data);
    if (loc != -1)
    {
        ClHash->elements[loc].status = DELETE;
        ClHash->count--;
        return 1;
    }
    return -1;
}

int CloseHasingCount(const CloseHash *ClHash)//统计有效元素个数
{
    return ClHash->count;
}

int CheckCloseHasingIsEmpty(const CloseHash *ClHash)//判断哈希表是否为空,为空返回1
{
    if (ClHash->count == 0)
    {
        return 1;
    }
    return 0;
}

void CloseHasingDestory(CloseHash *ClHash)//销毁哈希表
{
    assert(ClHash);
    free(ClHash->elements);
    ClHash->elements = NULL;
    ClHash->Hashfunc = NULL;
    ClHash->_load_factor = 0;
    ClHash->capacity = 0;
    ClHash->count = 0;
}

void CloseHasingTest()  //测试闭散列
{
    CloseHash ClHash;
    int i = 0;
    int a[] = {37, 25, 14, 36, 49, 68, 57, 11};
    CloseHasingInit(&ClHash, Hashfunc);
    for (i = 0; i<sizeof(a)/sizeof(int); i++)
    {
        int n = CloseHasingCount(&ClHash);
        printf("插入%d前，闭散列中有%d个元素\n", a[i], n);
        CloseHasingInsert(&ClHash, a[i]);
        n = CloseHasingCount(&ClHash);
        printf("插入%d后，闭散列中有%d个元素\n\n", a[i], n);
    }
    i = 1;
    for (i = 0; i<30; i++)
    {
        int n;
        if (CloseHasingDelete(&ClHash, i) == -1)
        {
            n = CloseHasingCount(&ClHash);
            printf("删除%d失败, 此时还有%d个元素\n", i, n);
        }
        else
        {
            n = CloseHasingCount(&ClHash);
            printf("删除%d成功，此时闭散列中有%d个元素\n", i, n);
        }
    }
    CloseHasingDestory(&ClHash);
}