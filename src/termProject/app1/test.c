#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    int count = 0;
    int i;
    int firstNum, id, age;
    int idPrev = 0;

    for(i = 0; i < 1000; i++)
    {
        firstNum = (rand() % (2+1-1) + 1);
        id = firstNum + idPrev;
        idPrev = id;
        age = (rand() % (31 - 18) +18 );
        count++;
        printf("The id number is %d and the age is %d\n", id, age);
    }

    return 0;
}