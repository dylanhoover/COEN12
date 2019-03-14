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
   // NODE *tail;
    int count;
};


SET *createSet()
{
    printf("creating set\n");
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->head = malloc(sizeof(NODE));
    assert(sp->head != NULL);
    sp->head->next = sp->head;
    sp->head->prev = sp->head;
  
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
    printf("Set destroyed, goodbye\n");
    free(sp);
}

static void *searchA(SET *sp, int age,  bool *found)
{
    assert(sp != NULL);
   // printf("starting serachA\n");
    NODE *pSearch = sp->head->next;
    int i;
    //printf("pSearch created\n");
        for(i = 0; i < sp->count; i++)
        {
            if(pSearch->age == age)
            {
                
                *found = true;
                return(pSearch);
            }
            pSearch = pSearch->next;
        }
        
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
                *found = true;
                return(pSearch);
            }
            pSearch = pSearch->next;

    } while (pSearch != sp->head);

    *found = false;
}

void *searchAge(SET *sp, int age)
{
    assert(sp != NULL);
    bool found;
    NODE *fAge = searchA(sp, age, &found);
    return(fAge);
}

void *searchID(SET *sp, int ID)
{
    assert(sp != NULL);
    bool found;
    NODE *fID = searchB(sp, ID, &found);
    if(found == true)
        printf("Student with ID: %d found\n", ID);
    if(found == false)
        printf("Student with ID %d does not exist\n", ID);
    return(fID);
}

void insertElement(SET *sp, int age, int ID)
{
    assert(sp != NULL);
    bool found;
    NODE *new = malloc(sizeof(NODE));
    new->age = age;
    new->ID = ID;
    //printf("starting search\n");
    NODE *p = searchA(sp, age, &found);
    NODE *q;
    if(found == true)
    {
        printf("Student with age %d found\n", age);
        printf("Inserting student aged %d with ID: %d\n", age, ID);
        new->next = p->next;
        new->prev = p;
        p->next = new;
        printf("Student inserted\n");
        sp->count++;
        return;
    }
    else
    {
        printf("Student with age %d does not exist\n", age);
        printf("Inserting student aged %d with ID: %d\n", age, ID);
        q = sp->head->next;
        
        if(sp->count == 0)
        {
            sp->head->next = new;
            new->prev = sp->head;
            new->next = sp->head;
	    sp->head->prev = new;
            printf("Student inserted\n");
            sp->count++;
            return;
        }
        do
        {
            if(new->age <= q->age)
            {
                new->next = q;
                new->prev = q->prev;
                q->prev->next = new;
                q->prev = new;
                printf("Student inserted\n");
                sp->count++;
                return;
            }
            q = q->next;
        } while (q->next != sp->head);
	new->next = sp->head;
	new->prev = sp->head->prev;
	sp->head->prev->next = new;
	sp->head->prev = new;
	printf("Student insered\n");
	sp->count++;
	return;
    }
   
}

void deleteElement(SET *sp, int ID)
{
    assert(sp != NULL);
    bool found;
    printf("starting delete element\n");
    NODE *pDel = searchB(sp, ID, &found);
    if(found == true)
    {
        pDel->prev->next = pDel->next;
        pDel->next->prev = pDel->prev;
        free(pDel);
        printf("student deleted\n");
    }
    else
    {
        printf("no student with that ID\n");
    }
}

int maxAgeGap(SET *sp)
{
    assert(sp != NULL);
    int minAge = sp->head->next->age;
    int maxAge = sp->head->prev->age;
    int gap = (maxAge - minAge);
    printf("The max age gap is %d\n", gap);
}


void studentSearch(SET *sp, int age, int ID)
{
    assert(sp != NULL);
    bool found1;
    bool found2;
    printf("Searching for student aged: %d with ID: %d\n", age ,ID);
    searchB(sp, ID, &found1);
    if(found1 == true)
    {
        NODE *p = searchID(sp, ID);
        if(p->age != age)
            printf("Student with ID:%d and Age: %d does not exist\n", ID, age);
        else
            printf("Student found\n");
    }
    else
        printf("Student does not exist\n");
    
}