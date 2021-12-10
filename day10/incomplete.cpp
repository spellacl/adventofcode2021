#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>


int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];
        int len_lines = 0;

        std::map<char, int> scoring = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
        std::vector<unsigned long> all_scores;

        int answer = 0, count = 0;
        while(fgets(line, sizeof(line), file))
        {
            len_lines = strlen(line);
            if(line[len_lines - 1] == '\n') line[len_lines-1] = '\0';
            len_lines = strlen(line);

            std::vector<char> stack;
            std::string str(line, len_lines);
            count = 0;
            for(auto &c : str)
            {
                if( c == '{' || c == '(' || c == '<' || c == '[')
                {
                    stack.push_back(c);
                }
                else if(stack.empty())
                {
                    break;
                }
                else
                {
                    char pop_c = stack.back();
                    stack.pop_back();
                    if( (pop_c == '{' && c != '}')
                     || (pop_c == '[' && c != ']')
                     || (pop_c == '<' && c != '>')
                     || (pop_c == '(' && c != ')'))
                    {
                        break;
                    }
                }
                count += 1;
            }
            if(count == len_lines)
            {
                unsigned long score = 0;
                for(auto rit = stack.rbegin(); rit != stack.rend(); rit++)
                {
                    score *= 5;
                    score += scoring.at(*rit);
                }
                all_scores.push_back(score);
            }
        };

        sort(all_scores.begin(), all_scores.end());
        for(auto& s: all_scores)
            std::cout << s << std::endl;

        std::cout << "Answer: " << all_scores.at(all_scores.size()/(2)) << std::endl;

        fclose(file);

    }

    return 0;
}
