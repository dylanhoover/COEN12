#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dataSet.h"

typedef struct node
{
    struct node *next;
    struct node *prev;
    int age;
    int ID;
}NODE;

struct set
{
    NODE *head;
    NODE *tail;
    int count;
};


SET *createSet()
{
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->head = malloc(sizeof(NODE));
    assert(sp->head != NULL);
    sp->head->next = sp->head;
    sp->head->prev = sp->head;
    sp->tail = sp->head;
    return sp;
}

void destroy(SET *sp)
{
    assert(sp != NULL);
    NODE *pDel, *pNext;
    pDel = sp->head;
    do
    {
        pNext = pDel->next;
        free(pDel);
        pDel = pNext;
    } while (pDel != sp->head);
    free(sp);
}

static void *searchA(SET *sp, int age,  bool *found)
{
    assert(sp != NULL);
    printf("starting serachA\n");
    NODE *pSearch = sp->head->next;
    printf("pSearch created\n");
        do
        {
            pSearch = pSearch->next;
            if(pSearch->age == age)
            {
                printf("Student with age %d found\n", age);
                *found = true;
                return(pSearch);
            }
        } while (pSearch->next != sp->head);
        printf("Student with age %d does not exist\n", age);
        *found = false;
        return NULL;
}

static void *searchB(SET *sp, int ID, bool *found)
{
    assert(sp != NULL);
    
    NODE *pSearch = sp->head->next;
      do
        {
            if(pSearch->ID == ID)
            {
                printf("Student with ID %d found\n", ID);
                *found = true;
                return(pSearch);
            }
            pSearch = pSearch->next;
        } while (pSearch->next != sp->head);
        printf("Student with ID %d does not exist\n", ID);
        return NULL;
}

void *searchAge(SET *sp, int age)
{
    printf("starting search 2\n");
    assert(sp != NULL);
    bool found;
    NODE *fAge = searchA(sp, age, &found);
    printf("end of search2\n");
    return(fAge);
}

void *searchID(SET *sp, int ID)
{
    assert(sp != NULL);
    bool found;
    NODE *fID = searchB(sp, ID, &found);
    return(fID);
}

void insertElement(SET *sp, int age, int ID)
{
    assert(sp != NULL);
    bool found;
    NODE *new = malloc(sizeof(NODE));
    new->age = age;
    new->ID = ID;
    printf("starting search\n");
    NODE *p = searchA(sp, age, &found);
    NODE *q;
    if(found == true)
    {
        printf("Inserting student aged %d with ID: %d\n", age, ID);
        new->next = p->next;
        new->prev = p;
        p->next = new;
    }
    else
    {
        printf("Inserting student aged %d with ID: %d\n", age, ID);
        q = sp->head->next;
        if(sp->count == 0)
        {
            sp->head->next = new;
            new->prev = sp->head;
            new->next = sp->tail;
            sp->tail = sp->tail;
        }
        do
        {
            q = q->next;
        } while (new->age > q->age);
        if(q == sp->head)
        {
            new->next = q;
            new->prev = q->prev;
            q->prev = new;
        }
        else if(q == sp->tail)
        {
            new->prev = sp->tail->prev;
            sp->tail->prev->next = new;
            new->next = sp->tail->next;
            sp->tail = new;
        }
        else
        {
            new->next = q;
            new->prev = q->prev;
            new->prev->next = new;
            q->prev = new;
        }        
    }
    printf("Student inserted\n");
    sp->count++;
    return;
}

void deleteElement(SET *sp, int ID)
{
    assert(sp != NULL);
    bool found;
    NODE *pDel = searchB(sp, ID, &found);
    pDel->prev->next = pDel->next;
    pDel->next->prev = pDel->prev;
    if(pDel == sp->tail)
        sp->tail = pDel->prev;
    free(pDel);

}

int maxAgeGap(SET *sp);