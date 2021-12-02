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
        int i = 0;

        fgets(line, sizeof(line), file);
        int i_3 = atoi(line);
        fgets(line, sizeof(line), file);
        int i_2 = atoi(line);
        fgets(line, sizeof(line), file);
        int i_1 = atoi(line);

        while(fgets(line, sizeof(line), file))
        {
            i = atoi(line);
            if(i > i_3) count ++;

            i_3 = i_2;
            i_2 = i_1;
            i_1 = i;
        };

        printf("%d\n", count);
        fclose(file);
    }

    return 0;
}
