#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define EMPTY 0
#define FILLED 1
#define DELETED 2
#include "set.h"

struct set
{
    int count;
    int length;
    char* *data;
    char *flags;
    int (*compare)();
    unsigned(*hash)();
};
/*
* Function: createSet
* creates the set 
*   O(n)
*
*/
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    SET *sp;
    sp = malloc(sizeof(SET));
    int i;
    assert(sp != NULL);
    sp->compare = (*compare);
    sp->hash = (*hash);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(void*)*maxElts);
    assert(sp->data != NULL);
    sp->flags = malloc(sizeof(void*)*maxElts);
    for(i = 0; i < maxElts; i++)
        sp->flags[i] = EMPTY;
    assert(sp->flags != NULL);
    return(sp);
}

/*
*Function: destroySet
*Frees the set fully
*   O(n)
*
*/


void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->count; i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp->flags);
    free(sp);
}

/*
*Function: numElements
*Returns the number of elements in the given set
* O(1)
*/

int numElements(SET *sp)
{
    return(sp->count);
}

/*
*Function: search
*searches for the given element using the hash function to search
*
*/

static int search(SET *sp, void *elt, bool *found)
{
    assert(sp != NULL);
    int idx = (((*sp->hash)(elt))%(sp->length)); //set the index to the hash of the string modulo the length because the hash key would be to large if not
    if(sp->flags[idx] == EMPTY) //if the index is empty in the flag array then return the index
    {
        *found = false;
        return idx;
    }
    int firstDeleted = -1; //first deleted is set to NULL so that it can be assigned later

    while(sp->flags[idx] != EMPTY) //go through the flag array until an empty flag is found
    {
        if(((*sp->compare)(sp->data[idx], elt)) == 0 && sp->flags[idx] != DELETED) //if the given element is found in the index spot and the flag index isn't marked deleted the element has been found
        {
            *found = true;
            return idx;
        }
        if(sp->flags[idx] == DELETED && firstDeleted == -1) //if the index is marked as deleted and first delted is still NULL then set the firstDeleted to that index
            firstDeleted = idx;
        
        idx = (idx + 1) % (sp->length); //increment the index for the while loop
    }

    *found = false; 
    //if firstDeleted is not NULL then set the index to the first deleted spot to reuse the space
    if(firstDeleted != -1)
        idx = firstDeleted;
    return idx;
}

void addElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = true;
    if(sp->count == sp->length)
        return;
    int idx = search(sp, elt, &found);
    if(found == false)
    {
        sp->data[idx] = elt;
        sp->flags[idx] = FILLED; //set the flag array index to filled
        sp->count++;
        return;
    }
    else
        return;
    

}

void removeElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = true;
    int idx = search(sp, elt, &found);
    if(found == true)
    {
        
        sp->flags[idx] = DELETED; //when the element is removed the flag array is set to deleted not empty to reuse the space
        sp->count--;
    }
    else
        return;
}

void *findElement(SET *sp, void *elt)
{
    assert(sp != NULL);
    bool found;
    int idx;
    idx = search(sp, elt, &found); //set the index to the hash key, more so to get the bool returned
    if(found == false) //if the element is not found then nothing needs to be returnec
        return(NULL);
    return(sp->data[idx]); //if found then return the element itself
}

void *getElements(SET *sp)
{
    assert(sp != NULL);
    int i, j;
    j = 0;
    void **copy = malloc(sizeof(void*)*sp->count);
    for(i = 0; i<sp->length; i++) 
    {
        if(sp->flags[i] == FILLED)
        {
            copy[j] = sp->data[i];
            j++;
        }
    }
    return copy;
}