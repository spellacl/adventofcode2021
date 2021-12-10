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

        std::map<char, int> score = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

        int answer = 0;
        while(fgets(line, sizeof(line), file))
        {
            std::cout << line;
            len_lines = strlen(line);
            if(line[len_lines - 1] == '\n') line[len_lines-1] = '\0';
            len_lines = strlen(line);

            std::vector<char> stack;
            std::string str(line, len_lines);
            for(auto &c : str)
            {
                if( c == '{' || c == '(' || c == '<' || c == '[')
                {
                    stack.push_back(c);
                }
                else if(stack.empty())
                {
                    answer += score[c];
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
                        answer += score[c];
                        break;
                    }
                }

            }
        };

        printf("Answer %d\n", answer);
        fclose(file);

    }

    return 0;
}
