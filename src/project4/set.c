#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "set.h"

struct set
{
    int count;
    int length;
    LIST **lists;
    int (*compare)();
    unsigned(*hash)();
};

/*
*Function: createSet
*allocates memory and creates a set that keeps track of the numbers of elements, length of the array and lists
*each spot in the set has a list for chaining
*Runtime: O(n)
*/
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    SET *sp;
    sp = malloc(sizeof(SET));

    assert(sp !=NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->lists = malloc(sizeof(void *)*sp->length);
    sp->compare = compare;
    sp->hash = hash;

    int i;
    for(i = 0; i < sp->length; i++)
    {
        sp->lists[i] = createList(compare);
    }

    assert(sp->lists != NULL);
    return sp;
}

/*
*Function: destroySet
*free the lists array and set itself
*Runtime: O(1)
*/
void destroySet(SET *sp)
{
    free(sp->lists);
    free(sp);
}

/*
*Function: numElements
*returns the count 
*Runtime: O(1)
*/
int numElements(SET *sp)
{
    assert(sp != NULL);
    return(sp->count);
}

/*
*Function: addElement
*the functions called to actually add is from list.c, this fuction hashes the index space in the array
*Runtime: O(n)
*/
void addElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int idx = (*sp->hash)(elt)%sp->length;
    if(findItem(sp->lists[idx],elt) == NULL)
    {
        addFirst(sp->lists[idx], elt);
        sp->count++;
    }
} 

/*
*Function: removeElement
*more or less the same as add element using find element using the hashed index but removing if found
*Runtime: O(n)
*/
void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int idx = (*sp->hash)(elt)%sp->length;
    if(findItem(sp->lists[idx], elt) != NULL)
    {
        removeItem(sp->lists[idx], elt);
        sp->count--;
    }
}

/*
*Function: findElement
*hashes an index then calls findItem from list.c
*Runtime: O(n)
*/
void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL && elt != NULL);
    int idx = (*sp->hash)(elt)%sp->length;
    return(findItem(sp->lists[idx], elt));
}
/*function: getElements
*returns a copy of the array, for each list inside of the original array the data from the list is copied into that array, then all of the data is copied into the array to be returned
*Runtime: O(n^2)
*/
void *getElements(SET *sp)
{

    assert(sp != NULL);
    void **arr;
    void **copy;
    int count = 0;
    int i, j;
    arr = malloc(sizeof(void*)*sp->count);
    for(i = 0; i < sp->length; i++)
    {
        copy = getItems(sp->lists[i]);

        for(j = 0; j< numItems(sp->lists[i]); j++)
        {
            arr[count] = copy[j];
            count++;
        }
    } 
    return arr;
}



