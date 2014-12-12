#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 200
int a[N + 1];
struct levelArray
{
    struct node * forward;
};
typedef struct node
{
    int val;
    int level;
    struct levelArray *levels;
}SkipListNode;

typedef struct list
{
    int RealMaxLevel;
    int length;
    SkipListNode * head;
    SkipListNode * tail;
}SkipList;

int generateLevel()
{
    int l = 1;
    while (rand()%10 > 6)
       l ++; 
    return l;
}

SkipListNode * createNode(int level, int val)
{
    SkipListNode * s = (SkipListNode *)malloc(sizeof(SkipListNode)); 
    s->levels = (struct levelArray *) malloc(sizeof(struct levelArray) * (level + 10));
    s->val = val;
    s->level = level;
    return s;
}

SkipListNode * queryNode(SkipList * pSkipList, int val)
{
    SkipListNode * pNode = pSkipList->head;

    for (int i = pSkipList->RealMaxLevel - 1; i >= 0; i --)
    {
        while(pNode->levels[i].forward && pNode->levels[i].forward->val < val)
            pNode = pNode->levels[i].forward;
    }
    pNode = pNode->levels[0].forward; 
    if (!pNode)
        return NULL;
    if (pNode->val == val)
        return pNode;
    return NULL;
}

bool insertNode(SkipList * pSkipList, int val)
{
    SkipListNode * pNode = pSkipList->head;
    SkipListNode * update[N];
    
    for (int i = pSkipList->RealMaxLevel - 1; i >= 0; i--)
    {
        while(pNode->levels[i].forward && pNode->levels[i].forward->val < val)
            pNode = pNode->levels[i].forward;
        update[i] = pNode;
    }

    int level = generateLevel();
    SkipListNode * newNode = createNode(level, val);

    if (pSkipList->RealMaxLevel < level)
    {
        for (int i = pSkipList->RealMaxLevel; i < level; i++)
            update[i] = pSkipList->head;
        pSkipList->RealMaxLevel = level;
    }
    
    for (int i = pSkipList->RealMaxLevel - 1; i >= 0; i--)
    {
        newNode->levels[i].forward = update[i]->levels[i].forward;
        update[i]->levels[i].forward = newNode;
    }
    pSkipList->length ++;

    return true;
}

SkipList * createList()
{
    SkipList * s;
    s = (SkipList *)malloc(sizeof(SkipList));
    s->RealMaxLevel = 1;
    s->length = 0;
    s->head = createNode(N, 0);
    for (int i = 0; i < N; i++)
        s->head->levels[i].forward = NULL;
    s->tail = NULL;
    return s;
}

void print(SkipList * s)
{
    SkipListNode * pNode;
    for (int i = 0; i < s->RealMaxLevel; i++)
    {
        printf("LEVEL[%d]: ", i);
        pNode = s->head->levels[i].forward;
        while(pNode)
        {
            printf("%d-> ", pNode->val);
            pNode = pNode->levels[i].forward;
        }
        printf("NULL\n");
    }
    
}

void deleteNode(SkipList * pSkipList, SkipListNode * pNode, SkipListNode ** update)
{
    for (int i = 0; i < pSkipList->RealMaxLevel; i ++)
    {
        if (update[i]->levels[i].forward == pNode)
        {
            update[i]->levels[i].forward = pNode->levels[i].forward;
        }
    }
    while(pSkipList->RealMaxLevel > 1 && pSkipList->head->levels[pSkipList->RealMaxLevel - 1].forward == NULL)
        pSkipList->RealMaxLevel --;
    pSkipList->length --;
}

int deleteList(SkipList * pSkipList, int val)
{
    SkipListNode * update[N], * pNode;
    pNode = pSkipList->head;

    for (int i = pSkipList->RealMaxLevel - 1; i >= 0; i --)
    {
        while(pNode->levels[i].forward && pNode->levels[i].forward -> val < val)
            pNode = pNode->levels[i].forward;
        update[i] = pNode;
    }
    pNode = pNode->levels[0].forward;
    if (pNode && pNode->val == val)
    {
        deleteNode(pSkipList, pNode, update);
        free(pNode);
        return 1;
    }
    return 0;
}

int main()
{
    int n;
    srand(time(NULL));
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    SkipList * p = createList();
    for (int i = 0; i < n; i++)
        insertNode(p, a[i]);

    int val;
    print(p);
    printf("___________________________%d\n", p->RealMaxLevel);
    scanf("%d", &val);
    SkipListNode * ans = queryNode(p, val);
    if (ans != NULL)
        printf("%d\n", ans->val);
    
    scanf("%d", &val);
    printf("%d", deleteList(p, val));
    print(p);
    printf("___________________________%d\n", p->RealMaxLevel);
    getchar();
}

