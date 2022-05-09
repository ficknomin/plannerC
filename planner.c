#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct event
{
    char name[50];
    int hour;
    int minute;
    int duration;
    int priority;
}event;

typedef struct node
{
    event event;
    struct node *next;
}node;

void append(node **head, event event)
{
    node *newNode = (node*) malloc(sizeof(node));
    node *last = *head;

    newNode->event = event;

    if(*head == NULL)
    {
        *head = newNode;
        return;
    }

    while(last->next != NULL)
    {
        last = last->next;
    }

    last->next = newNode;
    return;
}

int numElements(node* head)
{
    int num = 0;

    while(head != NULL)
    {
        head = head->next;
        num++;
    }

    return num;
}

int menu()
{
    int userInput;

    printf("\nChoose an option:\n");
    printf("1. List all events\n2. Add an event\n3. Exit\n\n");

    scanf("%d", &userInput);

    return userInput;
}

void createEvent(node** head)
{
    event* newEvent = malloc(sizeof(event));

    printf("Enter the name of the band:\n");
    scanf("%s[^\n]", newEvent->name);

    printf("Enter the preffered hour and minute respectively(HH:MM format):\n");
    scanf("%d\n%d", &newEvent->hour, &newEvent->minute);

    printf("Enter the duration of the event(in minutes):\n");
    scanf("%d", &newEvent->duration);

    printf("Enter the priority of this event(1-3):\n");
    scanf("%d", &newEvent->priority);

    append(head, *newEvent);
}


int main()
{
    int userInput;
    int eventCounter = 0;

    node *head = (node*) malloc(sizeof(node));
    head = NULL;

    printf("\e[1mWelcome to the event planner!\e[m\n\n");

    main:
        userInput = menu();

        if(userInput == 1)
        {
            node *buffer = (node*) malloc(sizeof(node));

            buffer = head;

            while(buffer != NULL)
            {
                printf("%s, %d, %d:%d\n", buffer->event.name, buffer->event.priority, buffer->event.hour, buffer->event.minute);
                buffer = buffer->next;
            }

            free(buffer);

            goto main;
        }

        if(userInput == 2)
        {
            createEvent(&head);

            goto main;
        }
}
