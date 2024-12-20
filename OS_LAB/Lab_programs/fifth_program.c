#include<stdio.h>
struct process {
    int all[6], max[6], need[6], finished, request[6];
} p[10];
int avail[6], sseq[10], ss = 0, check1 = 0, check2 = 0, n, pid, nor, nori, work[6];

int safeseq(void);

int main() {
    int ch, k, i = 0, j = 0, pid, ch1;
    int violationcheck = 0, waitcheck = 0;
    do {
        printf("\n1.Input\n2.New Request\n3.Safe State or Not\n4.Print\n5.Exit\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1: 
                printf("\nEnter the number of processes:");
                scanf("%d", &n);
                printf("\nEnter the number of resources:");
                scanf("%d", &nor);
                printf("\nEnter the available resources:");
                for (j = 0; j < n; j++) {
                    for (k = 0; k < nor; k++) {
                        if (j == 0) {
                            printf("\nFor Resource Type %d:", k);
                            scanf("%d", &avail[k]);
                        }
                        p[j].max[k] = 0;
                        p[j].all[k] = 0;
                        p[j].need[k] = 0;
                        p[j].finished = 0;
                        p[j].request[k] = 0;
                    }
                }
                for (i = 0; i < n; i++) {
                    printf("\nEnter Max and Allocated Resources for P %d :", i);
                    for (j = 0; j < nor; j++) {
                        printf("\nEnter the Max of Resources %d:", j);
                        scanf("%d", &p[i].max[j]);
                        printf("\nAllocation of Resources %d:", j);
                        scanf("%d", &p[i].all[j]);
                        if (p[i].all[j] > p[i].max[j]) {
                            printf("\nAllocation should be less than or equal to Max\n");
                            j--;
                        } else
                            p[i].need[j] = p[i].max[j] - p[i].all[j];
                    }
                }
                break;
            case 2:
                violationcheck = 0;
                waitcheck = 0;
                printf("\nRequesting Process ID:\n");
                scanf("%d", &pid);
                for (j = 0; j < nor; j++) {
                    printf("\nNumber of Request for Resource %d:", j);
                    scanf("%d", &p[pid].request[j]);
                    if (p[pid].request[j] > p[pid].need[j])
                        violationcheck = 1;
                    if (p[pid].request[j] > avail[j])
                        waitcheck = 1;
                }
                if (violationcheck == 1)
                    printf("\nThe Process Exceeds its Max needs: Terminated\n");
                else if (waitcheck == 1)
                    printf("\nLack of Resources: Process State - Wait\n");
                else {
                    for (j = 0; j < nor; j++) {
                        avail[j] = avail[j] - p[pid].request[j];
                        p[pid].all[j] = p[pid].all[j] + p[pid].request[j];
                        p[pid].need[j] = p[pid].need[j] - p[pid].request[j];
                    }
                    ch1 = safeseq();
                    if (ch1 == 0) {
                        for (j = 0; j < nor; j++) {
                            avail[j] = avail[j] + p[pid].request[j];
                            p[pid].all[j] = p[pid].all[j] - p[pid].request[j];
                            p[pid].need[j] = p[pid].need[j] + p[pid].request[j];
                        }
                    } else if (ch1 == 1)
                        printf("\nRequest committed.\n");
                }
                break;
            case 3:
                if (safeseq() == 1)
                    printf("\nThe System is in Safe State\n");
                else
                    printf("\nThe System is not in Safe State\n");
                break;
            case 4:
                printf("\nNumber of Process:%d\n", n);
                printf("\nNumber of Resources:%d\n", nor);
                printf("\nPid\tMax\tAllocated\tNeed\n");
                for (i = 0; i < n; i++) {
                    printf(" P%d :", i);
                    for (j = 0; j < nor; j++)
                        printf(" %d ", p[i].max[j]);
                    printf("\t");
                    for (j = 0; j < nor; j++)
                        printf(" %d ", p[i].all[j]);
                    printf("\t");
                    for (j = 0; j < nor; j++)
                        printf(" %d ", p[i].need[j]);
                    printf("\n");
                }
                printf("\nAvailable:\n");
                for (i = 0; i < nor; i++)
                    printf(" %d ", avail[i]);
                break;
            case 5: 
                break;
        }
    } while (ch != 5);
    return 0;
}

int safeseq() {
    int tj, tk, i, j, k;
    ss = 0;
    for (j = 0; j < nor; j++)
        work[j] = avail[j];
    for (j = 0; j < n; j++)
        p[j].finished = 0;
    for (tk = 0; tk < nor; tk++) {
        for (j = 0; j < n; j++) {
            if (p[j].finished == 0) {
                check1 = 0;
                for (k = 0; k < nor; k++)
                    if (p[j].need[k] <= work[k])
                        check1++;
                if (check1 == nor) {
                    for (k = 0; k < nor; k++) {
                        work[k] = work[k] + p[j].all[k];
                        p[j].finished = 1;
                    }
                    sseq[ss] = j;
                    ss++;
                }
            }
        }
    }
    check2 = 0;
    for (i = 0; i < n; i++)
        if (p[i].finished == 1)
            check2++;
    printf("\n");
    if (check2 >= n) {
        for (tj = 0; tj < n; tj++)
            printf("p%d", sseq[tj]);
        return 1;
    } else
        printf("\nThe System is not in Safe State\n");
    return 0;
}

/*
1.Input
2.New Request
3.Safe State or Not
4.Print
5.Exit
Enter your choice: 1

Enter the number of processes: 3
Enter the number of resources: 3

Enter the available resources:
For Resource Type 0: 3
For Resource Type 1: 3
For Resource Type 2: 2

Enter Max and Allocated Resources for P 0 :
Enter the Max of Resources 0: 7
Allocation of Resources 0: 0
Enter the Max of Resources 1: 5
Allocation of Resources 1: 1
Enter the Max of Resources 2: 3
Allocation of Resources 2: 0

Enter Max and Allocated Resources for P 1 :
Enter the Max of Resources 0: 3
Allocation of Resources 0: 2
Enter the Max of Resources 1: 2
Allocation of Resources 1: 0
Enter the Max of Resources 2: 2
Allocation of Resources 2: 0

Enter Max and Allocated Resources for P 2 :
Enter the Max of Resources 0: 9
Allocation of Resources 0: 3
Enter the Max of Resources 1: 0
Allocation of Resources 1: 0
Enter the Max of Resources 2: 2
Allocation of Resources 2: 2

1.Input
2.New Request
3.Safe State or Not
4.Print
5.Exit
Enter your choice: 3


The System is in Safe State
Safe Sequence: P1 P0 P2

1.Input
2.New Request
3.Safe State or Not
4.Print
5.Exit
Enter your choice: 2


Requesting Process ID: 1
Number of Request for Resource 0: 1
Number of Request for Resource 1: 0
Number of Request for Resource 2: 2

Request committed.
The System is in Safe State
Safe Sequence: P1 P0 P2

1.Input
2.New Request
3.Safe State or Not
4.Print
5.Exit
Enter your choice: 4

Number of Process: 3
Number of Resources: 3

Pid     Max         Allocated       Need
P0 :    7 5 3       0 1 0           7 4 3
P1 :    3 2 2       3 0 2           0 2 0
P2 :    9 0 2       3 0 2           6 0 0

Available:
2 3 0

1.Input
2.New Request
3.Safe State or Not
4.Print
5.Exit
Enter your choice: 5
*/
