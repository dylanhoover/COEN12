#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STUDENTS 3000

int main()
{
    srand(time(NULL)); 

    int idCount, firstNum, id, age;
    int idPrev = 0;
    int i;

    SET *college;
    college = createDataSet(MAX_STUDENTS);

    for(i = 0; i < 1000; i++)
    {
        firstNum = (rand() % (2+1-1)+1);
        id = firstNum + idPrev;
        idPrev = id;
        age = (rand() % (30+1-18)+18);
        insertElement(college, age, id);
        idCount++;
    }

    int sAge = (rand() % 23);
    searchAge(college, sAge);

    int dAge = (rand() % 23);
    deleteElement(college, dAge);

    maxAgeGap(college);

    destroySet(college);

}