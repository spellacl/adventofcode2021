#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

long int value_calculation(int OXY_OR_CO2, int num_lines, int num_bits, long int *entries)
{
    int * remaining = malloc(sizeof(int)*(num_lines+1));
    for(int i = 0; i < num_lines+1; i++)
        remaining[i] = i;

    int j, count, bit, kept;

    for(int i = 0; i < num_bits; i++) // for each bit
    {
        j = 0; count = 0;
        while( remaining[j] < num_lines )
        {
            count += (entries[remaining[j]] >> (num_bits - 1 - i) ) & 1;
            j++;
        };

        if(OXY_OR_CO2 == 1)
            bit = (count >= j - count) ? 1 : 0;
        else
            bit = (count < j - count) ? 1 : 0;

        kept = 0; j = 0;
        while( remaining[j] < num_lines )
        {
            if(((entries[remaining[j]] >> (num_bits - 1 - i) ) & 1) == bit)
            {
                remaining[kept] = remaining[j];
                kept ++;
            }
            j++;
        };
        remaining[kept] = num_lines;
        if(kept == 1)
          break;
    }
    if(kept != 1) printf("got here and something when wrong\n");
    long int answer = entries[remaining[0]];
    free(remaining);

    return answer;
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];
    int num_bits = atoi(argv[2]);
    int num_lines = atoi(argv[3]);

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];
        char *ptr, *ptr2;
        int lines = 0;

        long int *entries = malloc(sizeof(long int)*num_lines);


        while(fgets(line, sizeof(line), file))
        {
            entries[lines] = strtol(line, &ptr, 2);
            lines += 1;
        };
        fclose(file);

        long int oxy = value_calculation(1, num_lines, num_bits, entries);
        printf("--\n");
        long int co2 = value_calculation(0, num_lines, num_bits, entries);

        printf("%lu %lu %lu\n", oxy, co2, oxy * co2);
        free(entries);
    }

    return 0;
}
