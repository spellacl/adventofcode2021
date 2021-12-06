#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        int max_grid = INT_MIN, min_grid = INT_MAX;
        while(fgets(line, sizeof(line), file))
        {
            char * token = strtok(line, ",-> ");
            while( token != NULL)
            {
                max_grid = max(max_grid, atoi(token));
                min_grid = min(min_grid, atoi(token));
	            token = strtok(NULL, ",-> "); 
            };
        };
        rewind(file);
        max_grid += 1;
        int * grid = malloc(max_grid * max_grid * sizeof(int));

        while(fgets(line, sizeof(line), file))
        {
            int x1 = atoi(strtok(line, ",-> "));
	        int y1 = atoi(strtok(NULL, ",-> ")); 
            
            int x2 = atoi(strtok(NULL, ",-> "));
	        int y2 = atoi(strtok(NULL, ",-> "));

            if( (x1 == x2) || (y1 == y2) )
            {
                for(int i = x1; 
                    (x1 < x2) ? i <= x2 : i >= x2; 
                    (x1 < x2) ? i++ : i--)
                {
                    for(int j = y1; 
                    (y1 < y2) ? j <= y2 : j >= y2; 
                    (y1 < y2) ? j++ : j--)
                    {
                        grid[j * max_grid + i] += 1;
                    }
                }
            }
        };

        int overlap = 0;
        for(int i = 0; i < max_grid; i++)
        {
            for(int j = 0; j < max_grid; j++)
            {
                int val = grid[i * max_grid + j];
                if(val)
                    printf("%d", val);
                else
                    printf(".");
                if(val >= 2) overlap ++;
            }
            printf("\n");
        }

        printf("\n\noverlap %d\n", overlap);

    
        free(grid);
        fclose(file);
    }

    return 0;
}
