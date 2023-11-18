#include <stdio.h>
#include <stdlib.h>

// global var
int PageFaultCount = 0;


typedef struct MemoryBlock
{
    int pageno;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct
{
    int size, len;
    MemoryBlock *head;
} Memory;

// init memory parameters(Memory pointer,no of frames)
void init(Memory *x, int n);
// access page
void accessPage(Memory *m, int p);
// add memory block(page) in memory
// search for a page
int pageSearch(Memory *m, int p);
// add page
void addPage(Memory *m, int pgno);
// demand paging
int FIFO(Memory *m);
void printll(Memory *m);
int main(void)
{
    int numberOfFrames, n, i;
    int refernceString[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
    printf("\nEnter the number of frames:  ");
    scanf("%d", &numberOfFrames);
    Memory *memory = (Memory *)malloc(sizeof(Memory));
    n = sizeof(refernceString) / sizeof(int);
    init(memory, numberOfFrames);
    for (i = 0; i < n; i++)
    {
        accessPage(memory, refernceString[i]);
        //printll(memory);
    }
    printf("\n\nTotal Page Fault count: %d\n",PageFaultCount);
    return 0;
}

void init(Memory *x, int n)
{
    x->len = 0;
    x->head = NULL;
    x->size = n;
}

void accessPage(Memory *m, int p)
{
    int result;
    result = pageSearch(m, p);
    if (result > 0)
    {
        printf("\npage[%d] found in the memory.\n\n", result);
    }
    else
    {
        printf("\npage[%d] not found in the memory.(PAGE FAULT)", p);
        PageFaultCount++;
        addPage(m, p);
    }
}

int pageSearch(Memory *m, int p)
{
    MemoryBlock *temp = m->head;
    while (temp != NULL)
    {
        if (temp->pageno == p)
            return temp->pageno;
        temp = temp->next;
    }
    return 0;
}

void addPage(Memory *m, int pgno)
{
    MemoryBlock *temp =m->head;;
    int r;
    if (m->len == m->size)
    {
        r = FIFO(m);
        printf("\nMemory is FULL.\nPage Replacement.\nRemoving the page [%d].\nLoading the page [%d] in the memory.\n\n", r, pgno);
        temp= m->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = (MemoryBlock *)malloc(sizeof(MemoryBlock));
        temp = temp->next;
        temp->pageno = pgno;
        temp->next = NULL;
        m->len++;
    }
    else if (m->head == NULL)
    {
        printf("\nMemory is Empty.\nLoading the page [%d] in the memory.\n\n", pgno);
        m->head = (MemoryBlock *)malloc(sizeof(MemoryBlock));
        m->head->pageno = pgno;
        m->head->next = NULL;
        m->len++;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = (MemoryBlock *)malloc(sizeof(MemoryBlock));
        temp = temp->next;
        temp->pageno = pgno;
        temp->next = NULL;
        m->len++;
        printf("\nLoading the page [%d] in the memory.\n\n", pgno);
    }
}

int FIFO(Memory *m)
{
    if (m->head != NULL)
    {
        int p = m->head->pageno;
        MemoryBlock *temp = m->head;
        m->head = m->head->next;
        free(temp);
        m->len--;
        return p;
    }
}

void printll(Memory *m){
    printf("\nprinting ll:  ");
    MemoryBlock *temp=m->head;
    while(temp!=NULL){
        printf("%d->",temp->pageno);
        temp=temp->next;
    }
    printf("\n");
}