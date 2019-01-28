#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

struct set
{
    int count;
    int length;
    char* *data;
};
/*
 * Function: createSet
 *
 * Description: creates thei set that holds the  array
 *
 */
SET *createSet(int maxElts)
{
    SET *sp;
    sp = malloc(sizeof(SET)); //allocate for set
    assert(sp != NULL);
    //initialize the length and count
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char*)*maxElts); //allocate for the data array
    assert(sp->data != NULL);
    return(sp);
}

/*
 * Function: destroySet
 *
 * Description: destroys the array
 *
 * 	O(n)
 */
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    //iterate through the array first freeing the data individually then free the data array then the whole set
    for(i = 0; i < sp->count; i++) 
        free(sp->data[i]);
    free(sp->data);
    free(sp);  
}

/*
 *Function: search
 *
 * Description: find the needed element in the array
 * 	O(n)
 *
 */


int search(SET *sp, char *elt)
{
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->count; i++) //iterate through array
    {
        if(strcmp(sp->data[i], elt) == 0) //compare the strings
        {
            return(i);
        }
    }
    return(-1);
}
/*
 *Function: findElement
 *
 *Description: uses search to return the index
 *		O(n)
 */

char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    int i;
    i = search(sp, elt);
    if(i == -1)
        return(0);
    return(sp->data[i]); //return the index, this is used to delete
}
/*
 *Function: addElement
 *
 *Description: adds the elements to the array
 *	O(n)
 */

void addElement(SET *sp, char *elt)
{
    int i;
    assert(sp != NULL);
    assert(elt != NULL);
    if(sp->count == sp->length) //if the count is the same as the length the array is full
        return;
    if((search(sp, elt)) != -1) //pass to find elements
        return; //no dupliacting elements	
    sp->data[sp->count] = strdup(elt); //copy the elements into the data while incrementing the count up 
    sp->count++; 
}
/*
 *Function: removeElement
 *
 * Description: removes an element from the array if it is already there
 *		O(n)
 */
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    int i = 0;
    i = search(sp, elt); //pass the element to findElement to check for it
    if(i == -1)
        return; //not found
    if(sp->count == 1) //if there is only 1 element there is no need to shift the array
    {
        free(sp->data[i]); //frees that data
        (sp->count)--; //brings the count down
        return;
    }
    free(sp->data[i]);
    sp->data[i] = sp->data[(sp->count) -1]; //shift the data in the array up 1
    sp->count--;
    return;
}

/*
 *Function: numElements 
 *
 *Description: Returns the number of elements in the array
 *	O(1)
 *
 */
int numElements(SET *sp)
{
    return(sp->count);
}
/*
 *Function: getElements
 *
 * Description: creates new set of arrays for given words
 *	O(n)
 *
 */
char **getElements(SET *sp)
{
    char *elements; //pointer to elemtns
    assert(sp != NULL);
    SET *new; //create the new set
    new = (SET*)malloc(sizeof(SET)); //allocate for the new set
    assert(new !=NULL);
    //initialize new set length and count
    new->length = sp->length; 
    new->count = 0;
    new->data = malloc(sizeof(char*)*sp->length); //allocate space for data of new set
    assert(new->data != NULL);
    elements = strdup(*sp->data); //copy old data to new set
    new->data[(new->count)++] = elements; //place data into set
    return(new->data); //return the set
}

