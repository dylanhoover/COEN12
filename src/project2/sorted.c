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

int search(SET *sp, char *elt, bool *found)
{
    int lo, hi, mid;
    lo = 0;
    hi = (sp->count -1);
    *found = true;
    int compare;
    while(lo<=hi)
    {
        mid = (lo+hi)/2; //set mid
        compare = strcmp(sp->data[mid], elt); //set the compare variable up
        if(compare < 0) //when compare is less than 1 the top half of the array doens't have the string
            hi = mid -1; //hi is now mid, begin again
        else if(compare > 0) //when compare is greater than 0 the bottom half of the array doesn't have the string
            lo = mid +1; //lo is now mid
        else 
        {
            //when the string is found mid is the location
            *found = true;
            return mid;
        }
    }
    *found = false;
    return(lo);
}

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

char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    int i;
    bool found;
    i = search(sp, elt, &found);
    if(i == 0)
        return(-1);
    return(sp->data[i]); //return the index, this is used to delete
}


void addElement(SET *sp, char *elt)
{
    int i;
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = false;
    if(sp->count == sp->length) //if the count is the same as the length the array is full
        return;
    int idx = search(sp, elt, &found); //pass to find elements
    if(found == true)
        return;
    else
    {
        for(i = sp->count; i > idx; i--)
            sp->data[i] = sp->data[i-1]; //moves the elements into the set
        //copy elements into array
        sp->data[idx] = strdup(elt);
        (sp->count)++;
        return;
    }
}

void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    assert(elt != NULL);
    int idx;
    int i;
    bool found;
    idx = search(sp, elt, &found); //pass the element to findElement to check for it
    if(found == false)
        return; //not found
    if(sp->count == 1) //if there is only 1 element there is no need to shift the array
    {
        free(sp->data[idx]); //frees that data
        (sp->count)--; //brings the count down
        return;
    }
    free(sp->data[idx]);
    for(i = idx; i < (sp->count) -1; i++) //shift the element down
        sp->data[i] = sp->data[i+1];
    (sp->count)--;
}


int numElements(SET *sp)
{
    return(sp->count);
}

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