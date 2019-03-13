
#include "dataSet.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


int main()
{
    srand(time(NULL)); 

    int idCount, firstNum, id, age;
    int idPrev = 0;
    int i;

    SET *college;
    college = createSet();

    for(i = 0; i < 4; i++)
    {
        firstNum = (rand() % (2+1-1)+1);
        id = firstNum + idPrev;
        idPrev = id;
        age = (rand() % (30+1-18)+18);
        printf("new student aged %d, with ID: %d\n", age, id);
        insertElement(college, age, id);
        idCount++;
    }

    //int sAge = (rand() % 23);
   // searchAge(college, sAge);

    int dID = (rand() % (30+1-18)+18);
    deleteElement(college, dID);

   // maxAgeGap(college);

    destroy(college);

}