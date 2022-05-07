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

int menu()
{
    int userInput;

    printf("Choose an option:\n");
    printf("1. List all events\n2. Add an event\n3. Exit\n\n");

    scanf("%d", &userInput);

    return userInput;
}

event createEvent()
{
    event* newEvent = malloc(sizeof(event));

    printf("Enter the name of the band:\n");
    scanf("%s", newEvent->name);

    printf("Enter the preffered hour and minute respectively(HH:MM format):\n");
    scanf("%d\n%d", &newEvent->hour, &newEvent->minute);

    printf("Enter the duration of the event(in minutes):\n");
    scanf("%d", &newEvent->duration);

    printf("Enter the priority of this event(1-3):\n");
    scanf("%d\n", &newEvent->priority);
    
    return *newEvent;
}


int main()
{
    int userInput;
    int eventCounter = 0;
    event events[50];

    printf("\e[1mWelcome to the event planner!\e[m\n\n");

    main:
        userInput = menu();

        if(userInput == 1)
        {
            return 1;
        }

        if(userInput == 2)
        {
            int i = 0;

            event newEvent = createEvent();
            events[eventCounter] = newEvent;
            eventCounter++;

            goto main;
        }
}
