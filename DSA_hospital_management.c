#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


struct Patient {
    char name[50];
    int age;
    int priority;  
};


struct Queue {
    struct Patient data[MAX];
    int front, rear;
};


struct PriorityQueue {
    struct Patient data[MAX];
    int size;
};

// Function prototypes
void initQueue(struct Queue *q);
int isQueueEmpty(struct Queue *q);
int isQueueFull(struct Queue *q);
void enqueue(struct Queue *q, struct Patient p);
struct Patient dequeue(struct Queue *q);

void initPriorityQueue(struct PriorityQueue *pq);
void insertPriority(struct PriorityQueue *pq, struct Patient p);
struct Patient removeHighestPriority(struct PriorityQueue *pq);

void displayPatients(struct Queue q, struct PriorityQueue pq);



int main() {
    struct Queue normalQueue;
    struct PriorityQueue emergencyQueue;
    struct Patient p;
    int choice;

    initQueue(&normalQueue);
    initPriorityQueue(&emergencyQueue);

    while (1) {
        printf("\n=== HOSPITAL MANAGEMENT SYSTEM ===\n");
        printf("1. Register Normal Patient\n");
        printf("2. Register Emergency Patient\n");
        printf("3. Attend Next Patient\n");
        printf("4. Display Waiting List\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                printf("Enter patient name: ");
                fgets(p.name, 50, stdin);
                p.name[strcspn(p.name, "\n")] = 0;
                printf("Enter age: ");
                scanf("%d", &p.age);
                p.priority = 2;
                enqueue(&normalQueue, p);
                printf("✅ %s added to normal queue.\n", p.name);
                break;

            case 2:
                printf("Enter patient name: ");
                fgets(p.name, 50, stdin);
                p.name[strcspn(p.name, "\n")] = 0;
                printf("Enter age: ");
                scanf("%d", &p.age);
                p.priority = 1;
                insertPriority(&emergencyQueue, p);
                printf("🚨 %s added to emergency queue.\n", p.name);
                break;

            case 3:
                if (emergencyQueue.size > 0) {
                    p = removeHighestPriority(&emergencyQueue);
                    printf("👨‍⚕️ Attending Emergency Patient: %s (Age %d)\n", p.name, p.age);
                } else if (!isQueueEmpty(&normalQueue)) {
                    p = dequeue(&normalQueue);
                    printf("👨‍⚕️ Attending Normal Patient: %s (Age %d)\n", p.name, p.age);
                } else {
                    printf("No patients waiting.\n");
                }
                break;

            case 4:
                displayPatients(normalQueue, emergencyQueue);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}



void initQueue(struct Queue *q) {
    q->front = q->rear = -1;
}

int isQueueEmpty(struct Queue *q) {
    return q->front == -1;
}

int isQueueFull(struct Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(struct Queue *q, struct Patient p) {
    if (isQueueFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isQueueEmpty(q)) q->front = 0;
    q->rear++;
    q->data[q->rear] = p;
}

struct Patient dequeue(struct Queue *q) {
    struct Patient temp = {"No Patient", 0, 0};
    if (isQueueEmpty(q)) {
        printf("Queue is empty!\n");
        return temp;
    }
    temp = q->data[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return temp;
}



void initPriorityQueue(struct PriorityQueue *pq) {
    pq->size = 0;
}

void insertPriority(struct PriorityQueue *pq, struct Patient p) {
    if (pq->size == MAX) {
        printf("Priority Queue full!\n");
        return;
    }
    int i = pq->size - 1;
    while (i >= 0 && pq->data[i].priority > p.priority) {
        pq->data[i + 1] = pq->data[i];
        i--;
    }
    pq->data[i + 1] = p;
    pq->size++;
}

struct Patient removeHighestPriority(struct PriorityQueue *pq) {
    struct Patient p = {"No Patient", 0, 0};
    if (pq->size == 0) {
        printf("No emergency patients.\n");
        return p;
    }
    p = pq->data[0];
    for (int i = 0; i < pq->size - 1; i++)
        pq->data[i] = pq->data[i + 1];
    pq->size--;
    return p;
}



void displayPatients(struct Queue q, struct PriorityQueue pq) {
    printf("\n--- Emergency Patients ---\n");
    if (pq.size == 0)
        printf("None\n");
    else {
        for (int i = 0; i < pq.size; i++)
            printf("%s (Age %d)\n", pq.data[i].name, pq.data[i].age);
    }

    printf("\n--- Normal Patients ---\n");
    if (isQueueEmpty(&q))
        printf("None\n");
    else {
        for (int i = q.front; i <= q.rear; i++)
            printf("%s (Age %d)\n", q.data[i].name, q.data[i].age);
    }
}