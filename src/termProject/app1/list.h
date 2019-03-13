# ifndef LIST_H
# define LIST_H

typedef struct list LIST;

typedef struct node
{
    struct node *next;
    struct node *prev;
    void *ID;
}NODE;

struct list
{
    int count;
    NODE *head;
};

extern LIST *createList();
extern void destroyList(LIST *lp);
extern void addFirst(LIST *lp, void *ID);
extern void addLast(LIST *lp, void *ID);
extern int numItems(LIST *lp);
extern void removeItem(LIST *lp);
extern void *getItems(LIST *lp);

# endif /* LIST_H */
