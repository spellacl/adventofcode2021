#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <map>

std::vector<std::pair<int, int>> neighbours = {{-1,-1},{-1,0},{-1,1},
                                               {0,-1}, {0,0}, {0,1},
                                               {1,-1}, {1,0}, {1,1}};

void print(std::vector<char> matrix, int N)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            printf("%c", matrix.at(i*N + j));
        }
        printf("\n");
    }
    printf("\n");
}

void update(std::vector<char> &matrix, std::string algorithm, int &N, int sweep)
{
    std::vector<char> tmp((N+2*sweep)*(N+2*sweep));

    for(int i = -1*sweep; i < N+sweep; i++)
    {
        for(int j = -1*sweep; j < N+sweep; j++)
        {
            std::bitset<9> alg;
            int count = 8;
            for(auto &n : neighbours)
            {
                int XX = i + n.first;
                int YY = j + n.second;

                if(XX >= 0 && XX < N && YY >=0 && YY < N)
                {
                    char c = matrix.at(XX * N + YY);
                    alg.set(count, (c == '#') ? 1 : 0);
                }
                else
                {
                    alg.set(count, 0);
                }
                count -= 1;
            }
            tmp.at((i+sweep)*(N+(2*sweep))+(j+sweep)) = algorithm.at(alg.to_ulong());
        }
    }

    matrix = tmp;
    N = N + (2*sweep);
}

int reduce(std::vector<char> &matrix, int running_N, int &N, int sweep)
{
    int answer = 0;
    std::vector<char> tmp(running_N * running_N);

    int pos = 0;
    for(int i = 2*(sweep-1); i < N - 2*sweep+2 ; i++)
    {
        for(int j = 2*(sweep-1); j < N - 2*sweep+2; j++)
        {
            tmp.at(pos) = matrix.at(i*N+j);
            if(matrix.at(i*N+j) == '#') answer += 1;
            pos += 1;
        }
    }
    matrix = tmp;
    N = running_N;

    return answer;
}

int main(int argc, char *argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[4096];

        std::vector<char> matrix;

        fgets(line, sizeof(line), file);
        line[strlen(line)-1] = '\0';
        std::cout << line << std::endl;

        std::string algorithm(line, strlen(line));
        if(algorithm.size() != 512)
        {
            std::cout << "fuck" << std::endl;
            return 0;
        }

        fgets(line, sizeof(line), file);
        int N = 0;
        int count = 0;
        while(fgets(line, sizeof(line), file))
        {
            line[strlen(line)-1] = '\0';
            std::string str(line, strlen(line));

            for(auto &c : str)
            {
                matrix.push_back(c);
                count += (c == '#') ? 1 : 0;
            }
            N++;
        };
        int running_N = N;
        for(int i = 1; i <= 50; i++)
        {
            running_N += 2;
            update(matrix, algorithm, N, 10);
            print(matrix, N);
            if(i % 2 == 0)
            {
                printf("%d\n", reduce(matrix, running_N, N, 10));
            }
            print(matrix, N);
        }
        fclose(file);
    }

    return 0;
}
