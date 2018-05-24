#include "CloseHasing.h"

static unsigned int Hashfunc(unsigned int capacity, DataType data)  //��ϣ����
{
    return data % capacity;
}

void CloseHasingInit(CloseHash *ClHash, unsigned int (*func)(unsigned int, DataType))//��ʼ��
{
    int i = 0;
    assert(ClHash); 
    ClHash->_PrimeNum = 0;
    ClHash->elements  = (Element *)malloc(sizeof(Element)*_PrimeList[ClHash->_PrimeNum]);
    if (ClHash->elements == NULL)
    {
        perror("malloc");
        printf("��ʼ��ʧ��\n");
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

static void CloseHasingEnlargeCapacity(CloseHash *ClHash)    //����
{
    Element * cache = NULL;
    int i;
    int capacity = ClHash->capacity;
    assert(ClHash);
    cache = (Element *)realloc(ClHash->elements, sizeof(Element)*_PrimeList[ClHash->_PrimeNum+1]);
    if (cache == NULL)
    {
        perror("realloc");
        printf("����ʧ��\n");
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

static int ComputingLoadFactor(unsigned int all, unsigned int used) //��������
{
    return used*10/all;
}

int CloseHasingFindElement(const CloseHash *ClHash, DataType data)//����Ԫ�أ�����̽�⣩,���ҳɹ����ظ�Ԫ�صĽ���λ��,ʧ�ܷ���-1
{
    int loc[4];
    int count = 0;
    loc[0] = ClHash->Hashfunc(ClHash->capacity, data); //local[0] �����ʼλ��
    loc[1] = loc[0]; //loc[1]�����ʼλ�õ��Ҳ�λ��
    loc[2] = loc[0]; //loc[2]�����ʼλ�õ����λ��
    loc[3] = 1; //��Ǹ�loc[1]�߻��Ǹ�loc[2]��
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

void CloseHasingInsert(CloseHash *ClHash, DataType data)//����Ԫ��
{
    int loc[4];
    assert(ClHash);
    if (CloseHasingFindElement(ClHash, data) != -1)    //�ȿ������ϣ�����Ƿ���ڸ�Ԫ�أ�����̽�⣩
        return;

    if (ClHash->_load_factor >= 7)  //�������ݣ�������
        CloseHasingEnlargeCapacity(ClHash);
    
    //ѡ��һ�����ʵ�λ�ò��루����̽�⣩
    loc[0] = ClHash->Hashfunc(ClHash->capacity, data); //local[0] �����ʼλ��
    loc[1] = loc[0]; //loc[1]�����ʼλ�õ��Ҳ�λ��
    loc[2] = loc[0]; //loc[2]�����ʼλ�õ����λ��
    loc[3] = 1; //��Ǹ�loc[1]�߻��Ǹ�loc[2]��

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

int CloseHasingDelete(CloseHash *ClHash, DataType data)//ɾ��Ԫ��,ɾ���ɹ�����1��ʧ�ܷ���-1
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

int CloseHasingCount(const CloseHash *ClHash)//ͳ����ЧԪ�ظ���
{
    return ClHash->count;
}

int CheckCloseHasingIsEmpty(const CloseHash *ClHash)//�жϹ�ϣ���Ƿ�Ϊ��,Ϊ�շ���1
{
    if (ClHash->count == 0)
    {
        return 1;
    }
    return 0;
}

void CloseHasingDestory(CloseHash *ClHash)//���ٹ�ϣ��
{
    assert(ClHash);
    free(ClHash->elements);
    ClHash->elements = NULL;
    ClHash->Hashfunc = NULL;
    ClHash->_load_factor = 0;
    ClHash->capacity = 0;
    ClHash->count = 0;
}

void CloseHasingTest()  //���Ա�ɢ��
{
    CloseHash ClHash;
    int i = 0;
    int a[] = {37, 25, 14, 36, 49, 68, 57, 11};
    CloseHasingInit(&ClHash, Hashfunc);
    for (i = 0; i<sizeof(a)/sizeof(int); i++)
    {
        int n = CloseHasingCount(&ClHash);
        printf("����%dǰ����ɢ������%d��Ԫ��\n", a[i], n);
        CloseHasingInsert(&ClHash, a[i]);
        n = CloseHasingCount(&ClHash);
        printf("����%d�󣬱�ɢ������%d��Ԫ��\n\n", a[i], n);
    }
    i = 1;
    for (i = 0; i<30; i++)
    {
        int n;
        if (CloseHasingDelete(&ClHash, i) == -1)
        {
            n = CloseHasingCount(&ClHash);
            printf("ɾ��%dʧ��, ��ʱ����%d��Ԫ��\n", i, n);
        }
        else
        {
            n = CloseHasingCount(&ClHash);
            printf("ɾ��%d�ɹ�����ʱ��ɢ������%d��Ԫ��\n", i, n);
        }
    }
    CloseHasingDestory(&ClHash);
}