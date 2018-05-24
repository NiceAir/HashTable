��ϣ��

*****************��ɢ��*******************
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

*****************��ɢ��*******************


*****************��ɢ��*******************
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

*****************��ɢ��*******************