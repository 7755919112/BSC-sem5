#include <stdio.h>
#include <stdlib.h>
int cpuTime =0;
// pcb structure
typedef struct Process
{
    int pid, art, brt, pr, ct, tt, wt, status;
} Process;
// queue node structure
typedef struct queueNode
{
    Process *p;
    struct queueNode *next, *prev;
} queueNode;
// Queue structure
typedef struct Queue
{
    queueNode *front, *rear;
} Queue;
// func to accept arrival time from user
void acceptArrivalTimes(Process *p, int n);
// func to accept burst time from user
void acceptBurstTimes(Process *p, int n);
// func to accept priority of process from user
void acceptPriority(Process *p, int n);
// print pcb
void printPCB(Process *p, int n);
// completion time
void completionTime(Process *p, int n);
// init queue func
void init(Queue *q);
// fill ready queue func
void readyQueueFill(Queue *q, Process *p, int n);
// add in queue func
void addInQueue(Queue *q, Process *p);
// print queue function
void printQueue(Queue *q);
// high priority job
queueNode *shortestJob(Queue *q);
// delete from queue func
void deleteInQueue(Queue *Q);
// terminate i.e done with all processes
int terminate(Process *p, int n);
//not in queue func
int notInQueue(Queue *q, Process *p);
//turn around time
void turnAroundTime(Process *p,int n);
//wait time
void waitTime(Process *p,int n);
//avg turn around time
void avgturnaroundTime(Process *p,int n);
//avg wait time
void avgWaitTime(Process *p,int n);
//gant chart 
void gantChart(Process *p,int n);
int main(void)
{
    int n;
    Process *process = NULL;
    printf("\nEnter the number of process: ");
    scanf("%d", &n);
    process = (Process *)malloc(sizeof(Process) * n);
    acceptArrivalTimes(process, n);
    acceptBurstTimes(process, n);
    completionTime(process, n);
    turnAroundTime(process,n);
    waitTime(process,n);
    avgturnaroundTime(process,n);
    avgWaitTime(process,n);
    gantChart(process,n);
    //printPCB(process,n);
    return 0;
}

void acceptArrivalTimes(Process *p, int n)
{
    int i;
    printf("\nAccepting Arrival Time\nEnter %d values.\n", n);
    for (i = 0; i < n; i++)
    {
        p[i].pid = i;
        p[i].ct = 0;
        p[i].tt = 0;
        p[i].wt = 0;
        p[i].status = 0;
        printf("\n[%d]: ", i);
        scanf("%d", &p[i].art);
    }
    printf("\n");
}

void acceptBurstTimes(Process *p, int n)
{
    int i;
    printf("\nAccepting Burst Time\nEnter %d values.\n", n);
    for (i = 0; i < n; i++)
    {
        printf("\n[%d]: ", i);
        scanf("%d", &p[i].brt);
    }
    printf("\n");
}

void printPCB(Process *p, int n)
{
    int i;
    printf("\nPrinting PCB's\n");
    for (i = 0; i < n; i++)
    {
        printf("\n");
        printf("\nPID: %d", p[i].pid);
        printf("\nART: %d", p[i].art);
        printf("\nBT: %d", p[i].brt);
        printf("\nPRIORITY: %d", p[i].pr);
        printf("\nCOMPLETION: %d", p[i].ct);
        printf("\nTURNAROUND TIME: %d", p[i].tt);
        printf("\nWAIT TIME: %d", p[i].wt);
        printf("\nSTATUS: %d", p[i].status);
        printf("\n");
    }
}

void completionTime(Process *p, int n)
{
    Queue *readyq = NULL;
    queueNode *temp;
    readyq = (Queue *)malloc(sizeof(Queue));
    init(readyq);
    while (1)
    {
        if (terminate(p, n) == 1)
            break;
        readyQueueFill(readyq, p, n);
        temp = shortestJob(readyq);
        temp->p->ct = cpuTime + temp->p->brt;
        cpuTime = temp->p->ct;
        temp->p->status = 1;
        deleteInQueue(readyq);
    }
    return;
}

void init(Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

void readyQueueFill(Queue *q, Process *p, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if ((p[i]).art <= cpuTime && p[i].status == 0 && notInQueue(q,&p[i]))
        {
            addInQueue(q, &p[i]);
        }
    }
    // printf("\nready queue after fill: \n");
    // printQueue(q);
    // printf("\n\n");
}

void addInQueue(Queue *q, Process *p)
{
    queueNode *temp;
    if (q->front == NULL && q->rear == NULL)
    {
        q->front = q->rear = (queueNode *)malloc(sizeof(queueNode));
        q->front->p = p;
        q->front->next = NULL;
        q->front->prev = NULL;
    }
    else
    {
        temp = q->rear;
        q->rear->next = (queueNode *)malloc(sizeof(queueNode));
        q->rear->next->next = NULL;
        q->rear->next->prev = temp;
        q->rear = q->rear->next;
        q->rear->p = p;
    }
}

void printQueue(Queue *q)
{
    int i;
    queueNode *temp = q->front;
    while (temp != NULL)
    {
        printf("\n");
        printf("\nPID: %d", temp->p->pid);
        printf("\nART: %d", temp->p->art);
        printf("\nBT: %d", temp->p->brt);
        printf("\nPRIORITY: %d", temp->p->pr);
        printf("\nCOMPLETION: %d", temp->p->ct);
        printf("\nSTATUS: %d", temp->p->status);
        printf("\n");
        temp = temp->next;
    }
}
queueNode *shortestJob(Queue *q)
{
    queueNode *temp = q->front, *temp2 = NULL;
    int p;
    if (temp == NULL)
        return NULL;
    else
    {
        p = temp->p->brt;
        temp2 = temp;
        temp = temp->next;
        while (temp != NULL)
        {
            if (temp->p->brt < p)
            {
                p = temp->p->brt;
                temp2 = temp;
            }
            temp = temp->next;
        }
        return temp2;
    }
}

void deleteInQueue(Queue *Q)
{

    queueNode *highpri = shortestJob(Q), *temp = NULL;
    // printf("\nProcess having highest priority: %d", highpri->p->pid);
    temp = Q->front;
    if (temp == NULL)
    {
        printf("\nNULL queue cant delete.\n");
        return;
    }
    else
    {

        while (temp != NULL)
        {
            if (temp == highpri)
            {

                if (temp->prev == NULL && temp->next == NULL)
                {
                    free(temp);
                    Q->front = Q->rear = NULL;
                    return;
                }
                else if (temp->prev == NULL)
                {
                    Q->front = temp->next;
                    temp->next->prev = NULL;
                    free(temp);
                    return;
                }
                else if (temp->next == NULL)
                {
                    Q->rear = temp->prev;
                    temp->prev->next = NULL;
                    free(temp);
                    return;
                }
                else
                {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    free(temp);
                    return;
                }
            }
            else
                temp = temp->next;
        }
    }
}
int terminate(Process *p, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (p[i].status == 0)
        {
            return 0;
        }
    }
    return 1;
}
 
int notInQueue(Queue *q, Process *p){
    queueNode *temp=q->front;
    while(temp!=NULL){
        if(p->pid==temp->p->pid){
            return 0;
        }
        temp=temp->next;
    }
    return 1;
}

void turnAroundTime(Process *p,int n){
    int i;
    for(i=0;i<n;i++){
        p[i].tt=p[i].ct - p[i].art;
    }
}

void waitTime(Process *p,int n){
    int i;
    for(i=0;i<n;i++){
        p[i].wt=p[i].tt - p[i].brt;
    }
}

void avgturnaroundTime(Process *p,int n){
    int i,sum=0;
    float avg;
    for(i=0;i<n;i++){
        sum+=p[i].tt;
    }
    avg=(float)sum/n;
    printf("\nAverage TurnAround Time: %.2f",avg);
}

void avgWaitTime(Process *p,int n){
    int i,sum=0;
    float avg;
    for(i=0;i<n;i++){
        sum+=p[i].wt;
    }
    avg=(float)sum/n;
    printf("\nAverage Wait Time: %.2f",avg);
}

void gantChart(Process *p,int n){
    int i;
    printf("\n\nGanat Chart\n\n");
    printf("\nP\tAR\tBT\tCt\tTT\tWT");
    for(i=0;i<n;i++){
        printf("\nP[%d]\t%d\t%d\t%d\t%d\t%d",p[i].pid,p[i].art,p[i].brt,p[i].ct,p[i].tt,p[i].wt);
    }
    printf("\n");
}