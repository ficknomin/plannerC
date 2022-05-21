#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PREP 20

typedef struct event
{
    char name[50];
    int hour;
    int minute;
    int duration;
    int endHour;
    int endMin;
    int stage;
    int priority;
}event;

typedef struct node
{
    event event;
    struct node *next;
}node;


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

/*
*   sortPriority function takes the pointer to the list as a parameter.
*   Sorts the bands according to their priority (1-3).
*/

void sortPriority(node *head)
{
    node *pointer = head;
    event temp;

    while(pointer != NULL)
    {
        node *buffer = pointer;
        while(buffer->next != NULL)
        {
            if(buffer->event.priority > buffer->next->event.priority)
            {
                temp = buffer->event;
                buffer->event = buffer->next->event;
                buffer->next->event = temp;
            }
            buffer = buffer->next;
        }
        pointer = pointer->next;
    }
}

/*
* sortTime function sorts the events
* takes the head pointer as a parameter
*
*/

void sortTime(node *head)
{
    node *pointer = head;
    node *buffer = head;
    int gap;

    for(int i = 0; i < numElements(head); i++)
    {
        for(int y = 0; y < numElements(head); y++)
        {
            if((strcmp(buffer->event.name, pointer->event.name) != 0) && (pointer->event.hour == buffer->event.endHour) && ((pointer->event.minute == buffer->event.endMin) || (pointer->event.minute < buffer->event.endMin)) && (pointer->event.priority>=buffer->event.priority) && (pointer->event.stage == buffer->event.stage))
            {
                printf("Pointer:%s\n", pointer->event.name);
                printf("Buffer:%s\n", buffer->event.name);
                gap = buffer->event.endMin - pointer->event.minute;

                pointer->event.minute += (gap + PREP);
                pointer->event.endMin += (gap + PREP);

                if(pointer->event.minute >= 60)
                {
                    pointer->event.hour++;
                    pointer->event.minute -= 60;
                }

                if(pointer->event.endMin >= 60)
                {
                    pointer->event.endHour++;
                    pointer->event.endMin -= 60;
                }
            }

            if((strcmp(buffer->event.name, pointer->event.name) != 0) && (pointer->event.endHour == buffer->event.hour) && ((pointer->event.endMin == buffer->event.minute) || (pointer->event.endMin > buffer->event.minute)) && (pointer->event.priority>=buffer->event.priority) && (pointer->event.stage == buffer->event.stage))
            {
                
                gap = pointer->event.endMin - buffer->event.minute;

                pointer->event.endMin -= (gap + PREP);
                pointer->event.minute -= (gap + PREP);

                if(pointer->event.endMin < 0)
                {
                    pointer->event.endHour--;
                    pointer->event.endMin = 60 + pointer->event.endMin;
                }

                if(pointer->event.minute < 0)
                {
                    pointer->event.hour--;
                    pointer->event.minute = 60 + pointer->event.minute;
                }

            }

            buffer = buffer->next;
        }
        
        buffer = head;
        pointer = pointer->next;
    }
}

void validate(node *head)
{
    while(head != NULL)
    {
        if(head->event.minute >= 60)
        {
            head->event.hour++;
            head->event.minute -= 60;
        }
        if(head->event.endMin >= 60)
        {
            head->event.endHour++;
            head->event.endMin -= 60;
        }
        head = head->next;
    }
}

/*
*   menu function takes no parameters.
*   prints possible choices, takes user input and returns it as an integer.
*/

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
    scanf(" %[^\n]s", newEvent->name);


    time:
        printf("Enter the preffered hour and minute respectively(HH:MM format):\n");
        scanf("%d", &newEvent->hour);
        while ((getchar()) != '\n'); // cleans the scanf buffer in case the loop repeats
        scanf("%d", &newEvent->minute);
        while ((getchar()) != '\n');
        if((newEvent->hour > 24 || newEvent->hour < 0) || (newEvent->minute > 60 || newEvent->minute < 0) || newEvent->hour == 0 || newEvent->minute == 0)
        {
            printf("Please, enter a valid hour/min!\n");
            goto time;
        }

    duration:
        printf("Enter the duration of the event(in minutes):\n");
        scanf("%d", &newEvent->duration);
        while ((getchar()) != '\n');
        if(newEvent->duration == 0)
        {
            printf("Please, enter valid duration!\n");
            goto duration;
        }

    if((newEvent->minute + newEvent->duration) > 60)
    {
        newEvent->endHour = newEvent->hour + 1;
        newEvent->endMin = (newEvent->minute + newEvent->duration) - 60;
    }
    else
    {
        newEvent->endHour = newEvent->hour;
        newEvent->endMin = newEvent->minute + newEvent->duration;
    }

    stage:

        printf("Enter the preffered stage(1-3):\n");
        scanf("%d", &newEvent->stage);
        while ((getchar()) != '\n');
        if(newEvent->stage > 3 || newEvent->stage < 1 || newEvent->stage == 0)
        {
            printf("Sorry, enter a valid stage number!\n");
            goto stage;
        }

    priority:

        printf("Enter the priority of this event(1-3):\n");
        scanf("%d", &newEvent->priority);
        while ((getchar()) != '\n');
        if(newEvent->priority > 3 || newEvent->priority < 1 || newEvent->priority == 0)
        {
            printf("Sorry, enter valid priority!\n");
            goto priority;
        }

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
            if(head == NULL)
            {
                printf("There are no entries, please add an event!\n");
                goto main;
            }

            sortPriority(head);
            sortTime(head);
            sortTime(head);
            validate(head);
            sortPriority(head);

            node *buffer = (node*) malloc(sizeof(node));

            buffer = head;

            while(buffer != NULL)
            {
                printf("%s, %d, %d:%d \t%d:%d\n", buffer->event.name, buffer->event.priority, buffer->event.hour, buffer->event.minute, buffer->event.endHour, buffer->event.endMin);
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