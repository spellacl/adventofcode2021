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

int parse(std::vector<int>::iterator it, int &version_sum, int type_id, unsigned long long& answer_value)
{
    std::vector<int>::iterator begin = it;
    unsigned long long int value;

    int version = (*(it++)   << 2) | (*(it++) << 1) | (*(it++));
//    printf("version %d\n", version);
    version_sum += version;

    int type = (*(it++) << 2) | (*(it++) << 1) | (*(it++));
//    printf("type %d\n", type);

    if(type == 4) // literal value
    {
        int start;
        value = 0;
        do
        {
            start = *(it++);
            for(int i = 0; i < 4; i++)
            {
                value = (value << 1) | *(it++);
            }
            if(start == 0) break;
        } while(start == 1);
        printf("- %llu\n", value);
    }
    else // operator
    {
        if(type == 0)       // sum
            value = 0;
        else if(type == 1)  // product
            value = 1;
        else if(type == 2)  // minimum
            value = ULLONG_MAX;
        else if(type == 3)  // maximum
            value = 0;
        else if(type == 5 || type == 6 || type == 7)
            value = 0;

        int length_id_type = *(it++);

        if(length_id_type == 0) // next 15 bits are total length in bits of subpackets
        {
            int length_subpacks = 0;
            for(int i = 0; i < 15; i++)
            {
                length_subpacks = (length_subpacks << 1 ) | *(it++);
            }
            printf("Type %d: length_subpacks %d value %llu \n", type, length_subpacks, value);
            int len = 0, len_total = 0;
            while (len_total < length_subpacks)
            {
                len = parse(it, version_sum, type, value);
                it += len;
                len_total += len;
            };
            printf("subpacks ----> value %llu\n", value);
        }
        else if(length_id_type == 1)// next 11 bits are number of sub-packets
        {
            int num_subpacks = 0;
            for(int i = 0; i < 11; i++)
            {
                num_subpacks = (num_subpacks << 1 ) | *(it++);
            }
            printf("Type %d: -- >num_subpacks %d value %llu\n", type, num_subpacks, value);
            int len = 0;
            for(int i = 0; i < num_subpacks; i++)
            {
                len = parse(it, version_sum, type, value);
                it += len;
            }
            printf("num_subpacks %d----> value %llu\n", type, value);
        }
    }

    switch(type_id)
    {
        case 0: //sum
        {
            answer_value += value;
            break;
        }
        case 1: //product
        {
            answer_value *= value;
            break;
        }
        case 2: //minimum
        {
            if(value < answer_value)
                answer_value = value;
            break;
        }
        case 3: //maximum
        {
            if(value > answer_value)
                answer_value = value;
            break;
        }
        case 5: // in first case, assign answer, then is first packet > second packet
        {
            if(answer_value == 0)
                answer_value = value;
            else
                answer_value = (answer_value > value);
            break;
        }
        case 6: // in first case, assign answer, then is first packet < second packet
        {
            if(answer_value == 0)
                answer_value = value;
            else
                answer_value =  (answer_value < value);
            break;
        }
        case 7: // in first case, assign answer, then is first packet == second packet
        {
            if(answer_value == 0)
                answer_value = value;
            else
                answer_value = (value == answer_value);
            break;
        }
    }
    return it - begin;
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
        unsigned long long int answer = 0;
        parse(input.begin(), version_sum, 0, answer);
        printf("VERSION SUM: %d\n", version_sum);
        printf("ANSWER: %llu\n", answer);

        fclose(file);

    }
    return 0;
}
