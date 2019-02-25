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

/*
*Function: create list
*allocates memory and creates a list containng a dummy node
*Runtime: O(1)
*
*/

LIST *createList(int (*compare)())
{
    LIST *lp = malloc(sizeof(LIST)); //allocate the list
    assert(lp != NULL);
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(NODE)); //allocate the head pointers
    assert(lp->head != NULL);
    //make the dummy node, make the list ciruclar
    lp->head->prev = lp->head;
    lp->head->next = lp->head;
    return lp;
}

/*
*Function: destroy list
*function destroys the list by iteratively going through it up until the last element
* Runtime: O(n)
*/

void destroyList(LIST *lp)
{
    assert(lp != NULL);
    NODE *pDel, *pNext; //nodes to go down the list to delete
    pDel = lp->head; //start pDel at the head
    do
    {
        pNext = pDel->next; //keep track of the next 
        free(pDel);
        pDel = pNext; //go down the array
    }while(pDel != lp->head); //because the list is circular the list is empty when pDel reaches head again
    free(lp);
}

/*
*Function: numItems
*This function returns the number of items in the list by returning the count
*Runtime: O(1)
*/

int numItems(LIST *lp)
{
    assert(lp != NULL);
    return lp->count;
}

/*
*Function: addFirst
*Function inserts node into the begining of the list at the front-end queue. Creates a new node and points the new next to head and head next to new then new prev to head and next node
*Runtime: O(1)
*/

void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *new = malloc(sizeof(NODE)); //allocate the new node
    //place the information
    new->data = item; 
    //place the node into the  begining of the ciruclar list, there is only 1 case becasue of the dummy node; no empty list
    new->next = lp->head->next; //the next for the new node is the node after the dummy node
    lp->head->next = new; //head next should now point ot new
    new->prev = lp->head; //the previous node is head
    new->next->prev = new; //original head next, which is now new next points to new
    lp->count++; //increase the count
}

/*
*Function: addLast
*insert a node into the rear of the list, the actually implementation is commented next to the code
*Runtime: O(1)
*/
void addLast(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *new = malloc(sizeof(NODE)); //allocate the new node
    //place data into the node
    new->data = item;
    //place the node at the end of the circular list, there is only 1 case
    new->next = lp->head; //new next points to head because it is at the end of the list
    new->prev = lp->head->prev; //new previous is the same as head previous was
    lp->head->prev = new; //head previous is now new
    new->prev->next = new; //the past last node next now points to new
    lp->count++;
}

/*
*Function removeFirst
*removes the first element at the front of the list, the implementation is commented bellow
*Runtime O(1)
*/
void *removeFirst(LIST *lp)
{
    assert(lp != NULL);
    NODE *p = lp->head->next; //set the pointer to the actual first node not the dummy node
    void *firstData = p->data;
    //unlink the node from the circle by pasing the pointers around it
    lp->head->next = p->next; 
    p->next->prev = lp->head;
    free(p); //free the node
    lp->count--;
    return firstData;
}

/*
*Function: removeLast
*removes the last element at the end of the list, actual implementation is commented bellow
*Runtime: O(1)
*/
void *removeLast(LIST *lp)
{
    assert(lp != NULL);
    NODE *p = lp->head->prev; //set the pointer to the last node in the list
    void *lastData = p->data; 
    //unlink the node from the circle by passing the pointers around it
    p->prev->next = lp->head;
    lp->head->prev = p->prev;
    free(p); //free the node
    lp->count--;
    return lastData;
}

/*
*Function: getFirst
*returns the first element in front of the list
*Runtime: O(1)
*/
void *getFirst(LIST *lp)
{
    assert(lp != NULL);
    return(lp->head->next->data); //just return the first node in the list, just head next
}

/*
*Function: getLast
*retuns the last node, at the end, of the list
*Runtime: O(1)
*/
void *getLast(LIST *lp)
{
    assert(lp != NULL);
    return(lp->head->prev->data); //return the last node, head prev
}

/*
*Function: removeItem
*removes the node with that matches with the given data, implementation is commented down bellow next to code
*Runtime: O(n)
*/
void removeItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *pDel = lp->head->next; //set pDel to head to start at the begining
    int i;
    for(i =0; i<lp->count; i++) //iterate i up to the count of the array
    {
        if(lp->compare(item, pDel->data) == 0) //compare the item given with the data in the node
        {
            //if the two match then pass the pointers around the node to unlink it
            pDel->next->prev = pDel->prev;
            pDel->prev->next = pDel->next;
            free(pDel); //free the node
        }
        pDel = pDel->next; //if the item and data don't match go to the next node
    }
    lp->count--;
    
}

/*
*Function: findItem
*traverses through the list to find the node that matches the given data and returns that node
*Runtime: O(n)
*/
void *findItem(LIST *lp, void *item)
{
    assert(lp != NULL && item != NULL);
    NODE *pFind = lp->head->next; //set pFind to the head to start at the begining
    int i;
    for(i = 0; i<lp->count; i++) //iterate i up to the count of the array
    {
        //this is identical to removeItem except instead of removing the data is returned
        if(lp->compare(pFind->data, item) == 0) 
            return(pFind->data);
        pFind = pFind->next;
    }
return NULL; //if not found return NULL
}

/*
*Function: getItems
*returns an array with all the data from each node
*an array is created with enough space to store however many elements are in the list, the list is copied into the array through traversal
*Runtime: O(n)
*/
void *getItems(LIST *lp)
{
    void **copy; //create a copy array
    copy = malloc(sizeof(void*)*lp->count); //allocate the list
    int i;
    NODE *p = lp->head->next; //start at the begining
    for(i = 0; i<lp->count; i++) //go through the count
    {
        copy[i] = p->data; //copy all the data to the array
        p = p->next;
    }
    return copy;
}
