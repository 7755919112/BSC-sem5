#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
0->available
1->not available
*/
// def for Block of Memory
typedef struct block
{
    int blockNumber;
    struct block *next;
} block;
// def of Memory Unit
typedef struct memory
{
    int numberOfBlocks, *bitVector;

} memory;
// def of file entity
typedef struct file
{
    char name[20];
    // total number of blocks occupied by the file
    int blocksSize;
    block *head;
} file;
// def dirEntry
typedef struct dirEntry
{
    file *f;
    struct dirEntry *next;
} dirEntry;
// directory entity
typedef struct directory
{
    dirEntry *head;
} directory;
// memory init function
void init(memory *m, int n)
{
    int i;
    m->numberOfBlocks = n;
    m->bitVector = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
    {
        m->bitVector[i] = 0;
    }
}
// display bit vector
void showBitVector(memory *m)
{
    int i;
    printf("\nShowing Bit Vector.\n");
    for (i = 0; i < (m->numberOfBlocks); i++)
    {
        printf("%d:", m->bitVector[i]);
    }
    printf("\n");
}
// function to check if required blocks are availble
int blocksAvailable(memory *m, int reqbbloks)
{
    int i, count = 0;
    for (i = 0; i < m->numberOfBlocks; i++)
    {
        if (m->bitVector[i] == 0)
        {
            count++;
        }
    }
    printf("\nAvailable Blocks are : %d\n", count);
    if (reqbbloks <= count)
        return 1;
    return 0;
}
// function to allocate blocks to the memeory
void allocateBlocks(memory *m, file *f, int blocks)
{
    int i, bno = 1;
    block *b, *fh;
    f->head = NULL;
    fh = f->head;
    for (i = 0; i < m->numberOfBlocks; i++)
    {
        if (m->bitVector[i] == 0)
        {
            b = (block *)malloc(sizeof(block));
            b->blockNumber = i + 1;
            b->next = NULL;
            if (fh != NULL)
            {
                //printf("\n1.block allocated\n");
                while (fh->next != NULL)
                    fh = fh->next;
                fh->next = b;
               // printf("\nblock number %d\n", b->blockNumber);
                bno++;
                m->bitVector[i] = 1;
                if (bno > blocks)
                    return;
            }
            else
            {
                //printf("\n2.block allocated\n");
                fh = b;
                f->head=fh;
                //printf("\nblock number %d\n", b->blockNumber);
                bno++;
                m->bitVector[i] = 1;
                if (bno > blocks)
                    return;
            }
        }
    }
}
// creating a file
void createFile(memory *m, directory *d, char name[20], int size)
{
    dirEntry *de, *tp;
    if (blocksAvailable(m, size))
    {
        file *f = (file *)malloc(sizeof(file));
        // dirEntry *tp;
        de = d->head;
        strcpy(f->name, name);
        f->blocksSize = size;
        allocateBlocks(m, f, size);
        //printf("\nname:%s\tsize:%d\thead:\n%X", f->name, f->blocksSize);
        if (de == NULL)
        {
            tp = (dirEntry *)malloc(sizeof(dirEntry));
            tp->f = f;
            tp->next = NULL;
            d->head = tp;
            // de->next=de;
        }
        else
        {
            while (de->next != NULL)
            {
                de = de->next;
            }
            tp = (dirEntry *)malloc(sizeof(dirEntry));
            tp->f = f;
            tp->next = NULL;
            de->next = tp;
        }
    }
    else
    {
        printf("\nNot Enough Space Available.Cant Save the File.\n");
        return;
    }
}
// function for show directory
void showDirectory(directory *d)
{
    dirEntry *tp = d->head;
    printf("\nShowing Files In Directory\n");
    if (tp != NULL)
    {
        printf("\n++++++++++++++++++++++++++++++++++++++\n");
        while (tp != NULL)
        {

            printf("\nFile Name : %s", tp->f->name);
            printf("\nFile Size : %d", tp->f->blocksSize);
            printf("\n\n");
            tp = tp->next;
        }
        printf("\n++++++++++++++++++++++++++++++++++++++\n");
    }
    printf("\n");
}
// delete file function
void delete(memory *m, directory *d, char fname[20])
{
    int i;
    dirEntry *tp = d->head, *prev = NULL, *temp;
    block *b, *bprev;
    if (tp != NULL)
    {
        while (tp != NULL)
        {
            if (strcmp(fname, tp->f->name) == 0)
            {
                if (prev == NULL)
                {
                    temp = tp;
                    d->head = tp->next;
                    b = temp->f->head;
                    if(b==NULL)
                            printf("\nb toh nulla nikla\n");
                    while (b != NULL)
                    {
                        printf("\nfreeing:%d\n",b->blockNumber);
                        m->bitVector[b->blockNumber-1] = 0;
                        bprev = b;
                        b = b->next;
                        free(bprev);
                    }
                    free(temp->f);
                    free(temp);
                    return;
                }
                else
                {
                    if (tp->next == NULL)
                    {
                        b = tp->f->head;
                        if(b==NULL)
                            printf("\nb toh nulla nikla\n");
                        while (b != NULL)
                        {
                            printf("\nfreeing:%d\n",b->blockNumber);
                            m->bitVector[b->blockNumber-1] = 0;
                            bprev = b;
                            b = b->next;
                            free(bprev);
                        }
                        prev->next = NULL;
                        free(tp->f);
                        free(tp);
                        return;
                    }
                    else
                    {
                        temp = tp;
                        tp = tp->next;
                        prev->next = tp;
                        b = temp->f->head;
                        if(b==NULL)
                            printf("\nb toh nulla nikla\n");
                        while (b != NULL)
                        {
                            printf("\nfreeing:%d\n",b->blockNumber);
                            m->bitVector[b->blockNumber-1] = 0;
                            bprev = b;
                            b = b->next;
                            free(bprev);
                        }
                        free(temp->f);
                        free(temp);
                        return;
                    }
                }
            }
            prev = tp;
            tp = tp->next;
        }
        
    }
}
int main(void)
{
    int n, opt, reqblocks;
    char fname[20];
    memory m;
    directory d;
    d.head = NULL;
    printf("Enter the Number of Blocks:  ");
    scanf("%d", &n);
    init(&m, n);
    do
    {
        printf("\n\nChoose any of the following Operations:");
        printf("\n\t1.Show Bit Vector.");
        printf("\n\t2.Create New File.");
        printf("\n\t3.Show Directory.");
        printf("\n\t4.Delete File.");
        printf("\n\t5.Exit.");
        printf("\nEnter Your Operation:  ");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
        {
            showBitVector(&m);
            break;
        }
        case 2:
        {
            printf("\nEnter File Name:  ");
            scanf("%s", fname);
            printf("\nEnter Blocks Required:  ");
            scanf("%d", &reqblocks);
            createFile(&m, &d, fname, reqblocks);
            break;
        }
        case 3:
        {
            showDirectory(&d);
            break;
        }
        case 4:
        {
            printf("\nEnter File Name:  ");
            scanf("%s", fname);
            delete(&m,&d,fname);
            break;
        }
        case 5:
        {
            printf("\n\nExiting Application\n");
            break;
        }
        default:
        {
            printf("\nEnter an Valid Option.\n");
            break;
        }
        }
    } while (opt != 5);
    return 0;
}