#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];
        int count = 0;
        fgets(line, sizeof(line), file);
        int prev = atoi(line);
        int curr = 0;

        while(fgets(line, sizeof(line), file))
        {
            curr = atoi(line);
            if(curr > prev) count ++;
            else if( curr == prev)
                printf("There is a trap here\n");
            prev = curr;
        };

        printf("%d\n", count);
        fclose(file);
    }

    return 0;
}
