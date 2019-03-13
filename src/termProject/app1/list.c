#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"


LIST *createList()
{
    LIST *lp = malloc(sizeof(LIST)); //allocate the list
    assert(lp != NULL);
    lp->count = 0;
    lp->head = malloc(sizeof(NODE)); //allocate the head pointers
    assert(lp->head != NULL);
    //make the dummy node, make the list ciruclar
    lp->head->prev = lp->head;
    lp->head->next = lp->head;
    return lp;
}

int listCompare(int test, int ID)
{
    if(test != ID)
        return(1);
    return(0);
}

void addFirst(LIST *lp, void *ID)
{
    assert(lp != NULL);
    NODE *new = malloc(sizeof(NODE)); //allocate the new node
    //place the information
    new->ID = ID;
    //place the node into the  begining of the ciruclar list, there is only 1 case becasue of the dummy node; no empty list
    new->next = lp->head->next; //the next for the new node is the node after the dummy node
    lp->head->next = new; //head next should now point ot new
    new->prev = lp->head; //the previous node is head
    new->next->prev = new; //original head next, which is now new next points to new
    lp->count++; //increase the count
}

void addLast(LIST *lp, void *ID)
{
    assert(lp != NULL);
    printf("adding student\n");
    NODE *new = malloc(sizeof(NODE)); //allocate the new node
    //place data into the node
    new->ID = ID;
    //place the node at the end of the circular list, there is only 1 case
    new->next = lp->head; //new next points to head because it is at the end of the list
    new->prev = lp->head->prev; //new previous is the same as head previous was
    lp->head->prev = new; //head previous is now new
    new->prev->next = new; //the past last node next now points to new
    lp->count++;
}

void removeItem(LIST *lp)
{
    assert(lp != NULL);
    NODE *pDel = lp->head->next; //set pDel to head to start at the begining
    NODE *qDel;
    while(pDel->next != lp->head)
    {  
        qDel = pDel;
        pDel = pDel->next;
        free(qDel);
    }
}

void *getItems(LIST *lp)
{
    void **copy; //create a copy array
    copy = malloc(sizeof(void*)*lp->count); //allocate the list
    int i;
    NODE *p = lp->head->next; //start at the begining
    for(i = 0; i<lp->count; i++) //go through the count
    {
        copy[i] = p->ID; //copy all the data to the array
        p = p->next;
    }
    return copy;
}

int numItems(LIST *lp)
{
    assert(lp != NULL);
    return lp->count;
}

