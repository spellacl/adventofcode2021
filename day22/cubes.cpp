#include <iostream>
#include <string.h>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        std::vector<bool> matrix(100*100*100);

        int N = 0;
        bool on_off = false;
        int x0, x1, y0, y1, z0, z1;
        int count = 0;
        while(fgets(line, sizeof(line), file))
        {
            char * token = strtok(line, "=.,");
            on_off = (token[2] == 'f') ? on_off = false : on_off = true;
            token = strtok(NULL, "=.,");
            x0 = atoi(token);
            token = strtok(NULL, "=.,");
            x1 = atoi(token);
            
            token = strtok(NULL, "=.,");
            token = strtok(NULL, "=.,");
            y0 = atoi(token);
            token = strtok(NULL, "=.,");
            y1 = atoi(token);

            token = strtok(NULL, "=.,");
            token = strtok(NULL, "=.,");
            z0 = atoi(token);
            token = strtok(NULL, "=.,");
            z1 = atoi(token);

            if( x0 >= -50 && x1 <= 50 && 
                y0 >= -50 && y1 <= 50 && 
                z0 >= -50 && z1 <= 50)
            {
                printf("%d %d %d %d %d %d\n", x0, x1, y0, y1, z0, z1);

                for(int i = x0; i <= x1; i++)
                {
                    for(int j = y0; j <= y1; j++)
                    {
                        for(int k = z0; k <= z1; k++)
                        {
                             matrix[((i+50) * 100 + (j+50)) * 100 + (k+50)] = on_off;
                        }
                    }
                }
            }
            count = 0;
            count = std::count_if(matrix.begin(), matrix.end(), [](int i){ return i == true; });
            printf("count %d\n", count);
        };
        fclose(file);
    }

    return 0;
}
