#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

typedef struct node
{
    struct node *next;
    struct node *prev;
    void *data;
}NODE;

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

int numItems(LIST *lp)
{
    assert(lp != NULL);
    return lp->count;
}

void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;
    new->next = lp->head->next;
    new->prev = lp->head;
    lp->head->next = new;
    new->next->prev = new;
    lp->count++;
}

void addLast(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;
    new->next = lp->head;
    new->prev = lp->head->prev;
    lp->head->prev = new;
    new->prev->next = new;
    lp->count++;
}

void *removeFirst(LIST *lp)
{
    assert(lp != NULL);
    NODE *p = lp->head->next;
    void *firstData = p->data;
    lp->head->next = p->next;
    p->next->prev = lp->head;
    free(p);
    lp->count--;
    return firstData;
}

void *removeLast(LIST *lp)
{
    assert(lp != NULL);
    NODE *p = lp->head->prev;
    void *lastData = p->data;
    p->prev->next = lp->head;
    lp->head->prev = p->prev;
    free(p);
    lp->count--;
    return lastData;
}

void *getFirst(LIST *lp)
{
    assert(lp != NULL);
    return(lp->head->next->data);
}

void *getLast(LIST *lp)
{
    assert(lp != NULL);
    return(lp->head->prev->data);
}

void removeItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *pDel = lp->head;
    int i;
    for(i =0; i<lp->count; i++)
    {
        if(lp->compare(item, pDel->data) == 0)
        {
            pDel->next->prev = pDel->prev;
            pDel->prev->next = pDel->next;
            free(pDel);
        }
        pDel = pDel->next;
    }
    lp->count--;
    
}

void *findItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *pFind = lp->head;
    int i;
    for(i = 0; i<lp->count; i++)
    {
        if(lp->compare(item, pFind->data) == 0)
            return(pFind->data);
        pFind = pFind->next;
    }
return NULL;
}

void *getItems(LIST *lp)
{
    void **copy;
    copy = malloc(sizeof(void*)*lp->count);
    int i;
    NODE *p = lp->head->next;
    for(i = 0; i<lp->count; i++)
    {
        copy[i] = p->data;
        p = p->next;
    }
    return copy;
}