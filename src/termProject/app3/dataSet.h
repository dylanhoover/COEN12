#ifndef DATASET_H
#define DATASET_H


typedef struct set SET;
extern SET *createSet();
extern void destroy(SET *sp);
extern void *searchAge(SET *sp, int age);
extern void *searchID(SET *sp, int ID);
extern void insertElement(SET *sp, int age, int ID);
extern void deleteElement(SET *sp, int ID);
extern int maxAgeGap(SET *sp);
extern void studentSearch(SET *sp, int age, int ID);

#endif