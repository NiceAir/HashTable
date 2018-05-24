哈希表

*****************闭散列*******************
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

*****************闭散列*******************


*****************开散列*******************
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

*****************开散列*******************