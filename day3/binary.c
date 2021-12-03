#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char * argv[])
{
    const char * filename = argv[1];
    int num_bits = atoi(argv[2]);

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];
        char *ptr, *ptr2;
        int lines = 0;
        int *count = malloc(num_bits*sizeof(int));
        for(int i = 0; i < num_bits; i++)
            count[i] = 0;

        while(fgets(line, sizeof(line), file))
        {
            long int val = strtol(line, &ptr, 2);

            for(int i = 0; i < num_bits; i++)
            {
                count[i] += (val >> (num_bits - 1 - i)) & 1;
            }
            lines += 1;
        };
        fclose(file);

        char *most =    malloc((num_bits+1)*sizeof(char));
        char *least =   malloc((num_bits+1)*sizeof(char));

        for(int i = 0; i < num_bits; i++)
        {
            most[i]  = (count[i] > (lines-count[i])) ? '1' : '0';
            least[i] = (count[i] < (lines-count[i])) ? '1' : '0';
        }
        most[num_bits] = '\0';
        least[num_bits] = '\0';
        for(int i = 0; i < num_bits+1; i++)
            printf("%c ", least[i]);
        printf("\n");

        int gamma =     strtol(most, &ptr, 2);
        int epsilon =   strtol(least, &ptr, 2);

        printf("%d %d\n", gamma, epsilon);
        printf("%d\n", gamma * epsilon);

        free(most);
        free(least);
        free(count);
    }

    return 0;
}
