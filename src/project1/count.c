/*********************************************/
/*	Dylan Hoover	COEN 12              */
/*	Project 1       1/10/19              */
/*Reads the amount of words from a text file */
/*********************************************/


#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 30
//main function
int main(int argc, char* argv[])
{
    FILE *fp; //file pointer
    char word[MAXLENGTH]; //word to read into
    int wordCount = 0; //word count
    if(argc < 2) //need to have both arguments
    {
        printf("Not enough arguments\n");
        exit(1);
    }

    
    fp = fopen(argv[1], "r"); //open file
    if(fp == NULL) //no file exit program
    {
        printf("File does not exist\n");
        exit(1);
    }
    while(fscanf(fp, "%s", word) != EOF) //scan in word by word until end of the file, increment word amount
    {
       wordCount++; 
    }

    fclose(fp); //close file

    printf("%d total words\n", wordCount);

   

return 0;
}
