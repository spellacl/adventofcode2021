#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "limits.h"

bool compare( std::pair<char, int>& a, std::pair<char, int>&  b)
{
    return a.second < b.second;
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];
        fgets(line, sizeof(line), file);
        line[strlen(line)-1] = '\0';

        std::string input(line, strlen(line));
        std::cout << input << std::endl;

        fgets(line, sizeof(line), file);

        std::map<std::string, char> mapping;

        std::map<char, int> count;
        for(auto &c : input)
            count[c] += 1;

        while(fgets(line, sizeof(line), file))
        {
            char *token  = strtok(line, " ->");
            char *token2 = strtok(NULL, " ->");

            mapping[std::string(token,2)] = token2[0];

        };

        for(int steps = 0; steps < 10; steps ++)
        {
            std::string temp;

            for(int i = 0; i < input.size()-1; i++)
            {
                temp.push_back(input.at(i));
                char c = mapping[input.substr(i,2)];
                count[c] += 1;
                temp.push_back(c);
            }
            temp.push_back(*(input.end()-1));
//            std::cout << temp << std::endl;

            input = temp;
        }

        std::vector<std::pair<char, int> > temp_to_sort;
        for(auto &it : count)
        {
            temp_to_sort.push_back(it);
        }
        sort(temp_to_sort.begin(), temp_to_sort.end(), compare);

        for(auto [first, second] : temp_to_sort)
        {
            std::cout << first << " " << second << std::endl;
        }
        printf("Answer %d\n", (*(temp_to_sort.end()-1)).second - (*(temp_to_sort.begin())).second);

        fclose(file);

    }
    return 0;
}
