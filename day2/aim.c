#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];
        int position = 0;
        int depth = 0;
        int aim = 0;

        while(fgets(line, sizeof(line), file))
        {
            char * token = strtok(line, " ");
            int value = atoi(strtok(NULL, " "));

            if(strcmp(token, "forward") == 0)
            {
                position += value;
                depth += aim * value;
            }
            else if(strcmp(token, "down") == 0)
                aim += value;
            else if(strcmp(token, "up") == 0)
                aim -= value;
        };

        printf("%d\n", position * depth);
        fclose(file);
    }

    return 0;
}
