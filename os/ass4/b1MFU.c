#include <stdio.h>
#include <stdlib.h>

// global var
int PageFaultCount = 0;
int refernceString[] = {12, 15, 12, 18, 6, 8, 11, 12, 19, 12, 6, 8, 12, 15, 19, 8};
int *freq, ind;

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
int MFU(Memory *m);
MemoryBlock *highestFreq(Memory *m);
void printll(Memory *m);
void displayfreq(int *a,int n);
int main(void)
{
    int numberOfFrames, n, i;
    printf("\nEnter the number of frames:  ");
    scanf("%d", &numberOfFrames);
    Memory *memory = (Memory *)malloc(sizeof(Memory));
    n = sizeof(refernceString) / sizeof(int);
    freq = (int *)malloc(sizeof(int) * 20);
    for (i = 0; i < 20; i++)
    {
        freq[i] = 0;
    }
    init(memory, numberOfFrames);
    for (ind = 0; ind < n; ind++)
    {
        accessPage(memory, refernceString[ind]);
        //printll(memory);
        //displayfreq(freq,20);
    }
    printf("\n\nTotal Page Fault count: %d\n", PageFaultCount);
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
        freq[result]++;
    }
    else
    {
        printf("\npage[%d] not found in the memory.(PAGE FAULT)", p);
        PageFaultCount++;
        addPage(m, p);
        freq[p]++;
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
    MemoryBlock *temp = m->head;
    int r;
    if (m->len == m->size)
    {
        r = MFU(m);
        printf("\nMemory is FULL.\nPage Replacement.\nRemoving the page [%d].\nLoading the page [%d] in the memory.\n\n", r, pgno);
        temp = m->head;
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

int MFU(Memory *m)
{
    MemoryBlock *hf = highestFreq(m), *temp = m->head, *prev = NULL;
    int r;
    while (temp != hf)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp->next == NULL)
    {
        if (prev != NULL)
            prev->next = NULL;
        r = temp->pageno;
        free(temp);
        m->len--;
        return r;
    }
    else
    {
        if (prev != NULL)
        {
            prev->next = temp->next;
            r = temp->pageno;
            free(temp);
            m->len--;
            return r;
        }
        else
        {
            r = temp->pageno;
            prev = temp;
            temp = temp->next;
            m->head=temp; 
            free(prev);
            m->len--;
            return r;
        }
    }
}

MemoryBlock *highestFreq(Memory *m)
{
    MemoryBlock *temp = m->head, *h;
    int hf;
    if (temp != NULL)
    {
        hf = freq[temp->pageno];
        h = temp;
        temp = temp->next;
        while (temp != NULL)
        {
            if (freq[temp->pageno] > hf)
            {
                hf = freq[temp->pageno];
                h = temp;
            }
            temp = temp->next;
        }
        //printf("\npage:%d,hf:%d\n",h->pageno,freq[h->pageno]);
        return h;
    }
    
    return temp;
}

void printll(Memory *m)
{
    printf("\nprinting ll:  ");
    MemoryBlock *temp = m->head;
    while (temp != NULL)
    {
        printf("%d->", temp->pageno);
        temp = temp->next;
    }
    printf("\n");
}

void displayfreq(int *a,int n){
    int i;
    printf("\nprinting freq:  ");
    for(i=0;i<n;i++){
        printf("%d:%d ,",i,freq[i]);
    }
    printf("\n");
}