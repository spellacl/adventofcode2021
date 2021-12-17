#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "limits.h"

std::map<char, std::string> toBinary = {{'0', "0000"},
                                        {'1', "0001"},
                                        {'2', "0010"},
                                        {'3', "0011"},
                                        {'4', "0100"},
                                        {'5', "0101"},
                                        {'6', "0110"},
                                        {'7', "0111"},
                                        {'8', "1000"},
                                        {'9', "1001"},
                                        {'A', "1010"},
                                        {'B', "1011"},
                                        {'C', "1100"},
                                        {'D', "1101"},
                                        {'E', "1110"},
                                        {'F', "1111"} };

int parse(std::vector<int>::iterator it, int &version_sum)
{
    std::vector<int>::iterator begin = it;

    int version = (*(it++)   << 2) | (*(it++) << 1) | (*(it++));
    printf("version %d\n", version);
    version_sum += version;

    int type = (*(it++) << 2) | (*(it++) << 1) | (*(it++));
    printf("type %d\n", type);

    if(type == 4) // literal value
    {
        int start;
        int value = 0;
        do
        {
            printf("start %d\n", *(it));
            start = *(it++);
            for(int i = 0; i < 4; i++)
            {
                printf("%d\n", *it);
                value = (value << 1) | *(it++);
            }
            if(start == 0) break;
        } while(start == 1);
        printf("value %d\n", value);
        return it - begin;
    }
    else // operator
    {
        int length_id_type = *(it++);

        if(length_id_type == 0) // next 15 bits are total length in bits of subpackets
        {
            int length_subpacks = 0;
            for(int i = 0; i < 15; i++)
            {
                length_subpacks = (length_subpacks << 1 ) | *(it++);
            }
            printf("length_subpacks %d\n", length_subpacks);
            int len = 0, len_total = 0;
            while (len_total < length_subpacks)
            {
                len = parse(it, version_sum);
                it += len;
                len_total += len;
            };
            return it - begin;
        }
        else if(length_id_type == 1)// next 11 bits are number of sub-packets
        {
            int num_subpacks = 0;
            for(int i = 0; i < 11; i++)
            {
                num_subpacks = (num_subpacks << 1 ) | *(it++);
            }
            printf("num_subpacks %d\n", num_subpacks);
            int len = 0;
            for(int i = 0; i < num_subpacks; i++)
            {
                len = parse(it, version_sum);
                it += len;
            }
            return it - begin;
        }
    }

}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[4096];

        fgets(line, sizeof(line), file);
        std::cout << line;
        line[strlen(line)-1] = '\0';

        std::string str(line, strlen(line));
        int num_bits = 4*(strlen(line));

        std::vector<int> input;

        for(auto &c : str)
        {
            for(auto &b : toBinary.at(c))
                input.push_back(int(b - '0'));
        }

        for(auto &b : input)
        {
            std::cout << b;
        }
        std::cout << std::endl;

        int version_sum = 0;
        parse(input.begin(), version_sum);
        printf("VERSION SUM: %d\n", version_sum);

        fclose(file);

    }
    return 0;
}
