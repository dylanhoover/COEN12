#include <stdlib.h>
#include <stdio.h>


typedef struct node NODE;
typedef struct list LIST;

struct node
{
    *next;
    *prev;
    void *data;
};

struct list
{
    int count;
    NODE *head;
    int (*compare)();
};


LIST *createList(int (*compare)())
{
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->head->prev = lp->head;
    lp->head->next = lp->head;
    return lp;
}

void destroyList(LIST *lp)
{
    assert(lp != NULL);
    NODE *pDel, *pNext;
    pDel = lp->head;
    do
    {
        pNext = pDel->next;
        free(pDel);
        pDel = pNext;
    }while(pDel != lp->head);
    free(lp);
}