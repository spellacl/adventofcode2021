#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct objFish
{
    int age;
    int fishNumber;

    struct objFish * next;
} Fish;

Fish* new_fish(Fish **head, int value)
{
    Fish * last = *head;

    Fish *b = malloc(sizeof(Fish));
    b->age = value;
    b->next = NULL;

    if(*head == NULL)
    {
        *head = b;
        b->fishNumber = 0;
    }
    else{
        while(last->next != NULL)
        {
            last = last->next;
        };

        last->next = b;
        b->fishNumber = last->fishNumber + 1;
    }
    return b;
}

void print_fish( Fish **HEAD)
{
    Fish *curr = *HEAD;
    while(curr != NULL)
    {
        printf("%d,", curr->age);
        curr = curr->next;
    }
    printf("\n");
}

void update_fish(Fish **head, Fish **tail, int* num_fish)
{
    Fish *curr = *head;
    int append = 0;
    while(curr != NULL)
    {
        if(curr->age == 0)
        {
            curr->age = 6;
            append++;
        }
        else
            curr->age--;

       curr = curr->next;
    }
    (*num_fish) += append;
    for(int i = 0; i < append; i++)
    {
        *tail = new_fish(tail, 8);
    }
}

void delete_fish(Fish **head)
{
    Fish *curr = *head;
    Fish *next = NULL;
    while(curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[1024];

        Fish * HEAD = NULL;
        Fish * TAIL = NULL;
        int fish_count = 0;
        while(fgets(line, sizeof(line), file))
        {
            char * token = strtok(line, ",");
            while (token != NULL)
            {
                int val = atoi(token);
                TAIL = new_fish(&HEAD, val);
                fish_count ++;

                token = strtok(NULL, ",");
            };
        };
        int initial_fish_count = fish_count;
        printf("Initial State: ");
        print_fish(&HEAD);

        for(int i = 0; i < 80; i++)
        {
            update_fish(&HEAD, &TAIL, &fish_count);
            //printf("After %2d days %2d fish\n", i+1, fish_count);
            //print_fish(&HEAD);
        }
        printf("After 80 days %d fish\n", fish_count);

        //exponential growth f(x) = f(0) e^(kt)
        double eightyith = 1.0/80.0;
        double rate = log(fish_count / (double)initial_fish_count) * eightyith;
        printf("rate: %.32lf\n", rate);

        printf("After 256 days: %lf\n", initial_fish_count * exp(rate * 256));

        delete_fish(&HEAD);

        fclose(file);
    }

    return 0;
}
