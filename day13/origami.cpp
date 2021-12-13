#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "limits.h"

void print(std::vector<bool> matrix, int max_x, int max_y, int new_max_x, int new_max_y)
{
    int ind;
    for(int i = 0; i < new_max_x; i ++)
    {
        for(int j = 0; j < new_max_y; j++)
        {
            ind = i * max_y + j;
            if(matrix.at(ind) == true)
                printf("\e[1m#\e[0m");
            else
                printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

void update(std::vector<bool>& matrix, int max_x, int max_y, int& new_max_x, int& new_max_y, char rc, int rc_no)
{
    int ind, ind_old;
    if(rc == 'y')
    {
        for(int i = 0; i < rc_no; i ++)
        {
            for(int j = 0; j < max_y; j++)
            {
                ind     = i              * max_y + j;
                ind_old = (new_max_x - 1 - i)* max_y + j;
                matrix.at(ind) = matrix.at(ind) | matrix.at(ind_old);
                matrix.at(ind_old) = false;
            }
        }
        new_max_x = rc_no;
    }
    else if(rc == 'x')
    {
        for(int i = 0; i < max_x; i ++)
        {
            for(int j = 0; j < rc_no; j++)
            {
                ind     = i* max_y + j;
                ind_old = i* max_y + (new_max_y-1-j);
                matrix.at(ind) = matrix.at(ind) | matrix.at(ind_old);
                matrix.at(ind_old) = false;
            }
        }
        new_max_y = rc_no;
    }
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        int max_x = INT_MIN;
        int max_y = INT_MIN;

        while(fgets(line, sizeof(line), file) && line[0] != '\n')
        {
            std::cout << line;
            char *token = strtok(line, ",");
            char *token2 = strtok(NULL, ",");

            if(max_y < atoi(token)) max_y = atoi(token);
            if(max_x < atoi(token2)) max_x = atoi(token2);
        };
        rewind(file);
        max_x += 1;
        max_y += 1;

        std::vector<bool> matrix(max_x*max_y);
        while(fgets(line, sizeof(line), file) && line[0] != '\n')
        {
            char *token = strtok(line, ",");  //y
            char *token2 = strtok(NULL, ","); //x

            matrix.at(atoi(token2)*max_y + atoi(token)) = true;
        };

        int new_max_x = max_x;
        int new_max_y = max_y;
        //print(matrix, max_x, max_y, new_max_x, new_max_y);

        while(fgets(line, sizeof(line), file))
        {
            char *token = strtok(line, "=");
            token = strtok(NULL, "=");


            std::cout << line[11] << atoi(token) << " " << std::endl;
            update(matrix, max_x, max_y, new_max_x, new_max_y, line[11], atoi(token));

            int dots = std::count_if(matrix.begin(), matrix.end(),
                                     [](const auto &i){return i == true;});
            printf("dots %d %d %d\n", dots, new_max_x, new_max_y);
        };
        print(matrix, max_x, max_y, new_max_x, new_max_y);

        fclose(file);

    }
    return 0;
}
