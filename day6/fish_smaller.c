#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char * argv[])
{
    const char * filename = argv[1];
    int num_days = atoi(argv[2]);

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[1024];
        unsigned long *num_fish = malloc(9*sizeof(unsigned long));
        unsigned long *temp_fish = malloc(9*sizeof(unsigned long));

        while(fgets(line, sizeof(line), file))
        {
            char * token = strtok(line, ",");
            while (token != NULL)
            {
                int val = atoi(token);

                num_fish[val] ++;

                token = strtok(NULL, ",");
            };
        };

        for(int i = 0; i < 9; i++)
            printf("%4lu ", num_fish[i]);
        printf("\n");

        unsigned long * temp;
        for(int i = 0; i < num_days; i++)
        {
            for(int i = 0; i < 8; i++)
            {
                // 1 -> 0
                // 2 -> 1
                // ...
                // 8 -> 7
                temp_fish[i] = num_fish[i+1];
            }
            temp_fish[8] = num_fish[0];
            temp_fish[6] += num_fish[0];

            temp = num_fish;
            num_fish = temp_fish;
            temp_fish = temp;

            for(int i = 0; i < 9; i++)
                printf("%4lu ", num_fish[i]);
            printf("\n");
        }

        unsigned long fish_count = 0;
        for(int i = 0; i < 9; i++)
        {
            fish_count += num_fish[i];
            printf("%4lu ", num_fish[i]);
        }
        printf("\n");
        printf("After %d days %lu fish\n", num_days, fish_count);

        free(temp_fish);
        free(num_fish);
        fclose(file);
    }

    return 0;
}
