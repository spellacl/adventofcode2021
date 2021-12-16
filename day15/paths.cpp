#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "limits.h"
#include <set>

std::vector<std::pair<int, int>> neighbours = {{-1,0}, {0,-1}, {1, 0}, {0, 1}};

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
}

int min(int a, int b)
{
    return a < b ? a : b;
}

void print(std::vector<int>& matrix, int N)
{
    int ind;
    for(int i = 0; i < N; i ++)
    {
        for(int j = 0; j < N; j++)
        {
            ind = i * N + j;
            if(matrix.at(ind) == 0)
                printf("\e[0m%d  \e[0m", matrix.at(ind));
            else
                printf("%d  ", matrix.at(ind));
        }
        printf("\n");
    }
    printf("\n");
}

std::pair<int, int> min(std::map<std::pair<int, int>, int> distance, std::set<std::pair<int, int>> Q)
{
    std::pair<int, int> v;
    int min = INT_MAX;

    for(auto& [key, val] : distance)
    {
        if( val < min && Q.count(key) == 1)
        {
            min = val;
            v = key;
        }
    }
    return v;
}

void update(std::vector<int> matrix, int N)
{
    std::map<std::pair<int, int>, int> distance;
    std::set<std::pair<int, int>> Q;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            Q.insert(std::make_pair(i,j));
            distance[std::make_pair(i,j)] = INT_MAX;
        }
    }
    distance.at(std::make_pair(0,0)) = 0;
    Q.erase(std::make_pair(0,0));

    while(!Q.empty())
    {
        std::pair<int, int> v = min(distance, Q);
        Q.erase(v);

        for(auto & neighbour : neighbours)
        {
            std::pair<int, int> u = v + neighbour;
            if(Q.count(u) == 1
                && u.first >= 0 && u.second >= 0 && u.first <= N-1 && u.second <= N-1)
            {
                int alt = distance.at(v) + matrix.at(u.first * N + u.second);
                if( alt < distance.at(u))
                    distance.at(u) = alt;
            }
        }
    }

    std::cout << "distance(N-1, N-1) " << distance.at(std::make_pair(N-1, N-1)) << std::endl;
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        std::vector<int> matrix;

        int N = 0;
        while(fgets(line, sizeof(line), file))
        {
            line[strlen(line)-1] = '\0';
            std::string str(line, strlen(line));
            N += 1;

            for(auto &c : str)
                matrix.push_back(int(c - '0'));
        };
        fclose(file);

        print(matrix, N);

        update(matrix, N);
    }
    return 0;
}
