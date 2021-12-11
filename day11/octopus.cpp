#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

void print(std::vector<int>& matrix)
{
    int ind;
    for(int i = 0; i < 10; i ++)
    {
        for(int j = 0; j < 10; j++)
        {
            ind = i * 10 + j;
            if(matrix.at(ind) == 0)
                printf("\e[0m%d  \e[0m", matrix.at(ind));
            else
                printf("%d  ", matrix.at(ind));
        }
        printf("\n");
    }
    printf("\n");
}

void update(std::vector<int>& matrix, int i, int j, int& flashes)
{
    int ind_00, ind_01, ind_02, ind_10, ind_11, ind_12, ind_20, ind_21, ind_22;
    if(matrix.at(i*10+j) > 9)
    {
        flashes += 1;

        ind_00 = (i-1) * 10 + (j-1);
        ind_10 =  i    * 10 + (j-1);
        ind_20 = (i+1) * 10 + (j-1);
        ind_01 = (i-1) * 10 +  j;
        ind_11 =  i    * 10 +  j;
        ind_21 = (i+1) * 10 +  j;
        ind_02 = (i-1) * 10 + (j+1);
        ind_12 =  i    * 10 + (j+1);
        ind_22 = (i+1) * 10 + (j+1);
        
        matrix.at(ind_11) = -1; //flashed

        if(i != 0)
        {
            if(j!=0 && matrix.at(ind_00) != -1)
            {
                matrix.at(ind_00 ) +=1;
                update(matrix, i-1, j-1, flashes);
            }
            if(matrix.at(ind_01) != -1)
            {
                matrix.at(ind_01 ) +=1;
                update(matrix, i-1, j, flashes);
            }
            if(j != 9 && matrix.at(ind_02) != -1)
            {
                matrix.at(ind_02 ) +=1;
                update(matrix, i-1, j+1, flashes);
            }
        }
        if(i != 9)
        {
            if(j!=0 && matrix.at(ind_20) != -1)
            {
                matrix.at(ind_20 ) +=1;
                update(matrix, i+1, j-1, flashes);
            }
            if(matrix.at(ind_21) != -1)
            {
                matrix.at(ind_21 ) +=1;
                update(matrix, i+1, j, flashes);
            }
            if(j!=9 && matrix.at(ind_22) != -1)
            {
                matrix.at(ind_22 ) +=1;
                update(matrix, i+1, j+1, flashes);
            }
        }
        if(j != 0 && matrix.at(ind_10) != -1)
        {
            matrix.at(ind_10 ) +=1;
            update(matrix, i, j-1, flashes);
        }
        if(j != 9 && matrix.at(ind_12) != -1)
        {
            matrix.at(ind_12 ) +=1;
            update(matrix, i, j+1, flashes);
        }
    }
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        std::vector<int> matrix;
        std::vector<int> temp_matrix;

        while(fgets(line, sizeof(line), file))
        {
            std::string str(line, 10);
            for(auto it = str.begin(); it != str.end(); it++)
            {
                matrix.push_back(int(*it - '0'));
            }
        };
        fclose(file);

        int flashes = 0;
        int count = 0;
        int steps = 0;
        while(count != 100)
        {
            steps += 1;
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    matrix.at(i*10+j) += 1;
                }
            }
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    update(matrix, i, j, flashes);
                }
            }
            count = 0;
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    if(matrix.at(i*10+j) == -1)
                    {
                        matrix.at(i*10+j) = 0;
                        count++;
                    }
                }
            }
            if(count == 100) printf("Step %d flashed simultaneously\n", steps);
            //print(matrix);
        };
        printf("Flashes %d\n", flashes);
    }
    return 0;
}
