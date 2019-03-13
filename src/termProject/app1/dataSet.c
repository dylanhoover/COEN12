#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"
#include "list.h"

struct set
{
    LIST **list;
    int *age;
    int count;
    int length;
};

SET *createDataSet(int maxStudents)
{
    printf("creating set\n");
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxStudents;
    sp->age = malloc(sizeof(int*)*sp->length);
    sp->list = malloc(sizeof(void*)*sp->length);
    int i;
    for(i = 0; i < sp->length; i++)
    {
        sp->list[i] = createList();
    }
    assert(sp->list != NULL);
    printf("set created\n");
    return sp;
}

void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for(i = 0; i<sp->count; i++)
    {
        free(sp->list[i]);
    }
    free(sp->age);
    free(sp->list);
    free(sp);
}

int compare(int age, SET *sp, int mid)
{
    assert(sp != NULL);
    int test = sp->age[mid];
    if(test > age)
        return(-1);
    else if(test < age)
        return(1);
    else
        return(0);
}

static int search(SET *sp, int age, bool *found)
{
     int lo, hi, mid;
    int i;
    lo = 0;
    hi = (sp->count -1);
    *found = true;
    printf("Searching for a student aged %d\n", age);
    while(lo<=hi)
    {
        if(compare(age, sp, mid) < 0) //when compare is less than 1 the top half of the array doens't have the string
            hi = mid -1; //hi is now mid, begin again
        else if(compare(age, sp, mid) > 0) //when compare is greater than 0 the bottom half of the array doesn't have the string
            lo = mid +1; //lo is now mid
        else 
        {
            //when the string is found mid is the location
            *found = true;
            printf("Student found\n");
            return(mid);
        }
    }
    *found = false;
    printf("No student with that age\n");
    return(lo);
}



void insertElement(SET *sp, int age, int ID)
{
    assert(sp != NULL);
    bool found;
    int i;
    int idx = search(sp, age, &found);
    if(sp->count == sp->length)
        return;
    printf("Adding student aged %d with ID:%d\n", age, ID);
    for(i = sp->count; i > idx; i--)
        sp->age[i] = sp->age[i-1];
    sp->age[idx] = age;
    addLast(sp->list[idx], &ID);
    printf("student added\n");
    /*else
    {
        printf("Adding student aged %d with ID:%d\n", age, ID);
         for(i = sp->count; i > idx; i--)
            sp->age[i] = sp->age[i-1];
        sp->age[idx] = age;
        addLast(sp->list[idx], &ID);
    }*/
    sp->count++;
    return;
}

void deleteElement(SET *sp, int age)
{
    assert(sp != NULL);
    bool found;
    int idx = search(sp, age, &found);

    if(found == true)
    {
        printf("Attempting to remove student aged %d\n", age);
        removeItem(sp->list[idx]);
        sp->count--;
        printf("Student removed\n");
        return;
    }
}

int maxAgeGap(SET *sp)
{
    int maxAge = sp->age[sp->count];
    int minAge = sp->age[0];
    int gap = maxAge - minAge;
    printf("The largest age Gap is %d\n", gap);
    return(gap);
}


static void *getElements(SET *sp, int idx)
{
    assert(sp != NULL);
    int i, j;
    void *p = sp->list[idx];
    int elCount = numItems(p);
    int count = 0;
    void **copy;
    void **arr = malloc(sizeof(void*)*sp->count);
    for(i = 0; i < elCount; i++)
    {
        copy[i] = getItems(p);

        for(j = 0; j < elCount; j++)
        {
            arr[count] = copy[j];
            count++;
        }

    }
    return arr;
}

static void *findElement(SET *sp, int age)
{
    assert(sp != NULL);
    bool found;
    int idx = search(sp, age, &found);
    int i;
    void **arr;
    if(found == true)
    {
        arr = getElements(sp, idx);
        for(i = 0; i < numItems(sp->list[idx]); i++)
        {
            printf("%p\n", arr[i]);
        }
    }
}

int searchAge(SET *sp, int age)
{
   findElement(sp, age);
}