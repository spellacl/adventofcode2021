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
#include <queue>

std::vector<std::pair<int, int>> neighbours = {{-1,0}, {0,-1}, {1, 0}, {0, 1}};

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
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


int h(std::pair<int, int> x, std::pair<int, int> end)
{
    return abs(x.first - end.first) + abs(x.second - end.second);
}

int Astar(std::vector<int> matrix, int N)
{
    std::pair<int, int> start = std::make_pair(0,0);
    std::pair<int, int> end = std::make_pair(5*N-1,5*N-1);

    std::map<std::pair<int, int>, int> gScore;
    std::map<std::pair<int, int>, int> fScore;
    for(int i = 0; i < 5*N; i++)
    {
        for(int j = 0; j < 5*N; j++)
        {
            gScore[std::make_pair(i,j)] = INT_MAX;
            fScore[std::make_pair(i,j)] = INT_MAX;
        }
    }
    gScore[start] = 0;
    fScore[start] = h(start, end);

    auto cmp = [&fScore](std::pair<int, int> left, std::pair<int, int> right)
    {
        return fScore.at(left) > fScore.at(right);
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> Q(cmp);
    Q.push(start);
    std::set<std::pair<int, int>> Q_tracker;
    Q_tracker.insert(start);

    unsigned long int iters = 0;
    while(!Q.empty())
    {
        iters ++;
        std::pair<int, int> current = Q.top();
        printf("%lu (%d, %d)\n", iters, current.first, current.second);
        if(current == end)
            return gScore.at(current);

        for(auto & neighbour : neighbours)
        {
            std::pair<int, int> u = current + neighbour;
            if(u.first >= 0 && u.second >= 0 && u.first <= 5*N-1 && u.second <= 5*N-1)
            {
                int xx = u.first  % N;
                int yy = u.second % N;
                int mult_x = u.first / N;
                int mult_y = u.second / N;

                int value = (matrix.at(xx * N + yy) + mult_x + mult_y);
                value = (value > 9) ? value - 9: value;

                int tentative_gScore = gScore.at(current) + value;
                if(tentative_gScore < gScore.at(u))
                {
                    gScore.at(u) = tentative_gScore;
                    fScore.at(u) = tentative_gScore + h(u, end);

                    if(Q_tracker.count(u) == 0)
                    {
                        Q.push(u);
                        Q_tracker.insert(u);
                    }
                }
            }
        }

        Q.pop();
        Q_tracker.erase(current);
    };

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

        //update(matrix, N);
        std::cout << "distance(N-1, N-1) " << Astar(matrix, N) << std::endl;

    }
    return 0;
}
