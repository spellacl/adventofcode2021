#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

void print(std::vector<char>& matrix, int N_X, int N_Y)
{
    int ind;
    for(int i = 0; i < N_X; i ++)
    {
        for(int j = 0; j < N_Y; j++)
        {
            ind = i * N_Y + j;
            printf("%c ", matrix.at(ind));
        }
        printf("\n");
    }
    printf("\n");
}

bool update(std::vector<char>& matrix, int N_X, int N_Y)
{
    bool moved = false;
    std::vector<char> temp_matrix(N_X * N_Y);
    int ind_me, ind_next;
    for(int i = 0; i < N_X; i++)
    {
        for(int j = 0; j < N_Y; j++)
        {
            ind_me = i * N_Y + j;
            ind_next = i * N_Y + ((j+1)%N_Y);

            if(matrix.at(ind_me) == '>' &&
                matrix.at(ind_next) == '.')
            {
                moved = true;
                temp_matrix[ind_me] = '.';
                temp_matrix[ind_next] = '>';
                j++;
            }
            else
            {
                temp_matrix[ind_me] = matrix.at(ind_me);
            }

        }
    }
    for(int j = 0; j < N_Y; j++)
    {
        for(int i = 0; i < N_X; i++)
        {
            ind_me = i * N_Y + j;
            ind_next = ((i+1) % N_X) * N_Y + j;

            if(temp_matrix.at(ind_me) == 'v' &&
                temp_matrix.at(ind_next) == '.')
            {
                moved = true;
                matrix[ind_me] = '.';
                matrix[ind_next] = 'v';
                i++;
            }
            else
            {
                matrix[ind_me] = temp_matrix.at(ind_me);
            }

        }
    }
    return moved;
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        std::vector<char> matrix;

        int N_X = 0, N_Y = 0;
        while(fgets(line, sizeof(line), file))
        {
            line[strlen(line)-1] = '\0';
            std::string str(line, strlen(line));

            N_Y = 0;
            for(auto it = str.begin(); it != str.end(); it++)
            {
                matrix.push_back(*it);
                N_Y++;
            }
            N_X++;
        };
        fclose(file);

        printf("%d %d\n", N_X, N_Y);
        print(matrix, N_X, N_Y);
       

        int step = 1;
        while(update(matrix, N_X, N_Y))
        {
            step ++;
            //print(matrix, N_X, N_Y);
        }
        printf("%d number of steps\n", step);
    }
    return 0;
}
