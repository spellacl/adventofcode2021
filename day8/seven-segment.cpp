#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <map>

bool sort(std::bitset<7> a, std::bitset<7> b)
{
    return a.count() < b.count();
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        int count = 0;
        while(fgets(line, sizeof(line), file))
        {
            printf("%s", line);
            char * firstHalf = strtok(line, "|");
            char * secondHalf = strtok(NULL, "|");

            std::vector<std::bitset<7>> letters;
            char * token1 = strtok(firstHalf, " ");
            while(token1 != NULL)
            {
                std::bitset<7> a;
                std::string str(token1, strlen(token1));
                for(auto it2 = str.begin(); it2 != str.end(); it2++)
                {
                    a.set(int(*it2 - 'a'), true);
                }

                letters.push_back(std::move(a));
                token1 = strtok(NULL, " ");
            };

            sort(letters.begin(), letters.end(), sort);

            for(auto it = letters.begin(); it != letters.end(); it++)
            {
                std::cout << *it << std::endl;
            }
            std::cout << std::endl;

            /*
             * abc efg = 0
             *   c  f  = 1
             * a cde g = 2
             * a cd fg = 3
             *  bcd f  = 4
             * ab d fg = 5
             * ab defg = 6
             * a c  f  = 7
             * abcdefg = 8
             * abcd fg = 9
             */
            // a = XOR(cf, acf) = XOR(1, 7)
            std::bitset<7> a = letters.at(0) ^ letters.at(1);
            std::bitset<7> c, d, e;

            // c = XOR(6, 8) -> compare against 1 to check
            // d = XOR(0, 8) -> compare against 4 to check
            // e = XOR(9, 8) -> otherwise
            for(int i = 6; i <= 8; i++)
            {
                std::bitset<7> temp = letters.at(i) ^ letters.at(9);
                if( (temp & letters.at(0) ).count() == 1)
                    c = temp;
                else if( (temp & letters.at(2) ).count() == 1)
                    d = temp;
                else
                    e = temp;
            }

            // f = XOR(cf, c)
            std::bitset<7> f = letters.at(0) ^ c;
            // b = XOR(cdf, bcdf)
            std::bitset<7> b = ((c | d | f) ^ letters.at(2));
            // g = XOR(abcdef, abcdefg
            std::bitset<7> g = (a | b | c | d | e | f) ^ letters.at(9);

            std::cout << 'a' << a << std::endl;
            std::cout << 'b' << b << std::endl;
            std::cout << 'c' << c << std::endl;
            std::cout << 'd' << d << std::endl;
            std::cout << 'e' << e << std::endl;
            std::cout << 'f' << f << std::endl;
            std::cout << 'g' << g << std::endl;

            std::map<unsigned long, unsigned long> mapping;
            mapping[ (a | b | c |    e  | f | g ).to_ulong() ] = 0;
            mapping[ (        c         | f     ).to_ulong()] = 1;
            mapping[ (a |     c | d | e |     g ).to_ulong()] = 2;
            mapping[ (a |     c | d     | f | g ).to_ulong()] = 3;
            mapping[ (    b | c | d     | f     ).to_ulong()] = 4;
            mapping[ (a | b |     d     | f | g ).to_ulong()] = 5;
            mapping[ (a | b |     d | e | f | g ).to_ulong()] = 6;
            mapping[ (a     | c |         f     ).to_ulong()] = 7;
            mapping[ (a | b | c | d | e | f | g ).to_ulong()] = 8;
            mapping[ (a | b | c | d     | f | g ).to_ulong()] = 9;

            char * token = strtok(secondHalf, "| ");
            int mult = 1000;
            while(token != NULL)
            {
                int len = strlen(token);
                if(token[len-1] == '\n')
                {
                    token[len-1] = '\0';
                    len = strlen(token);
                }
                // part 1
                // if( len == 1 || len == 4 || len == 6 || len == 7)
                // count += 1;

                std::bitset<7> x;
                std::string str(token, strlen(token));
                for(auto it2 = str.begin(); it2 != str.end(); it2++)
                {
                    x.set(int(*it2 - 'a'), true);
                }

                count += mult * mapping[x.to_ulong()];
                mult /= 10;
                token = strtok(NULL, "| ");
            };
            std::cout << std::endl;
        };

        printf("%d\n", count);

        fclose(file);
    }

    return 0;
}
