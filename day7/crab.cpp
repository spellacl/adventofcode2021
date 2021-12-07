#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>

int add_fuel(int value)
{
    int sum = 0;
    for(int i = 0; i < value; i++)
    {
        sum += i + 1;
    }
    return sum;
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[4096];
        std::vector<int> list;

        int count = 0;
        while(fgets(line, sizeof(line), file))
        {
            char * token = strtok(line, ",");
            while( token != NULL)
            {
                list.push_back(atoi(token));
                count += 1;
                token = strtok(NULL, ",");
            };
        };
        fclose(file);

        std::sort(list.begin(), list.end());
        int median;
        if(count%2 == 0)
        {
            printf("even\n");
            median = 0.5* (list.at((count/2)-1) + list.at(count/2));
        }
        else
        {
            printf("odd\n");
            median = list.at(floor(count/2));
        }

        int fuel = 0;
        int avg = 0;
        for(auto it = list.begin(); it != list.end(); it++)
        {
            avg += *it;
            fuel += abs(*it - median);
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        printf("count %d avg %d median %d fuel %d\n", count, avg, median, fuel);

        fuel = 0;
        avg = floor(avg / (double)count);
        for(auto it = list.begin(); it != list.end(); it++)
        {
            fuel += add_fuel( abs(*it - avg) );
        }

        printf("count %d avg %d median %d fuel %d\n", count, avg, median, fuel);
    }

    return 0;
}
