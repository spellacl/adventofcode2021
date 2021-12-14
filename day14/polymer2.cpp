#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "limits.h"

bool compare( std::pair<char, unsigned long long>& a, std::pair<char, unsigned long long>&  b)
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
        std::map<std::string, unsigned long long> pair_count;

        std::map<char, unsigned long long> count;
        for(auto &c : input)
            count[c] += 1;

        while(fgets(line, sizeof(line), file))
        {
            char *token  = strtok(line, " ->");
            char *token2 = strtok(NULL, " ->");

            mapping[std::string(token,2)] = token2[0];
        };

        for(int i = 0; i < input.size() - 1; i++)
        {
            pair_count[input.substr(i,2)] += 1;
        }

        for(int steps = 0; steps < 40; steps ++)
        {
            std::map<std::string, unsigned long long> temp_pair_count;

            for(auto &[key, val] : pair_count)
            {
                std::cout << key << " " << val << " ";
                char c = mapping[key];
                std::string str;
                str.push_back(key.at(0));
                str.push_back(c);

                std::string str2;
                str2.push_back(c);
                str2.push_back(key.at(1));

                temp_pair_count[str] += val;
                temp_pair_count[str2] += val;
                count[c] += val;
            }
            std::cout << std::endl;
            pair_count = temp_pair_count;
        }

        std::vector<std::pair<char, unsigned long long> > temp_to_sort;
        for(auto &it : count)
        {
            temp_to_sort.push_back(it);
        }
        sort(temp_to_sort.begin(), temp_to_sort.end(), compare);

        for(auto [first, second] : temp_to_sort)
        {
            std::cout << first << " " << second << std::endl;
        }
        printf("Answer %llu\n", (*(temp_to_sort.end()-1)).second - (*(temp_to_sort.begin())).second);

        fclose(file);

    }
    return 0;
}
