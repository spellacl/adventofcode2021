#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

bool compare( std::pair<int, int>& a, std::pair<int, int>&  b)
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
        int position = 0;
        int depth = 0;

        int num_lines = 0;
        int len_lines = 0;
        std::vector<int> matrix;

        while(fgets(line, sizeof(line), file))
        {
            len_lines = strlen(line);
            num_lines ++;
            if(line[len_lines - 1] == '\n') line[len_lines-1] = '\0';
            len_lines = strlen(line);

            std::string str(line, len_lines);
            for(auto it = str.begin(); it != str.end(); it++)
            {
                matrix.push_back(int(*it - '0'));
            }
        };
        fclose(file);


        std::map<int, int> basin_id_to_size;
        std::vector<int> basins(num_lines * len_lines);
        printf("%d %d\n", num_lines, len_lines);

        int ans = 0;
        int up, down, left, right, me, ind;

        for(int i = 0; i < num_lines; i ++)
        {
            for(int j = 0; j < len_lines; j++)
            {
                ind = i * len_lines + j;

                printf("%d", matrix.at(ind));
                me = matrix.at(ind);

                up    = (i == 0)            ? 10 : matrix.at((i-1) * len_lines + j);
                down  = (i == num_lines -1) ? 10 : matrix.at((i+1) * len_lines + j);
                left  = (j == 0)            ? 10 : matrix.at(i * len_lines + (j-1));
                right = (j == len_lines-1)  ? 10 : matrix.at(i * len_lines + (j+1));

                if( me < up && me < down && me < left & me < right)
                {
                    ans += (me + 1);
                    basins[ind] = ind;
                    basin_id_to_size[ind] = 1;
                }
            }
            printf("\n");
        }
        printf("\n");
        printf("Num_basins %d\n", ans);


        bool found = true;
        while(found == true)
        {
            found = false;
            for(int i = 0; i < num_lines; i ++)
            {
                for(int j = 0; j < len_lines; j++)
                {
                    ind = i * len_lines + j;
                    me = basins.at(ind);
                    if( me == 0 )
                        continue;

                    me = matrix.at(i * len_lines + j);
                    up    = (i == 0)            ? -1 : matrix.at((i-1) * len_lines + j);
                    down  = (i == num_lines -1) ? -1 : matrix.at((i+1) * len_lines + j);
                    left  = (j == 0)            ? -1 : matrix.at(i * len_lines + (j-1));
                    right = (j == len_lines-1)  ? -1 : matrix.at(i * len_lines + (j+1));

                    if( up    > me && up    != 9 && basins.at((i-1) * len_lines + j) == 0)
                    {
                        basins.at((i-1) * len_lines + j) = basins.at(ind);
                        basin_id_to_size[basins.at(ind)] += 1;
                        found = true;
                    }
                    if( down  > me && down  != 9 && basins.at((i+1) * len_lines + j) == 0 )
                    {
                        basins.at((i+1) * len_lines + j) = basins.at(ind);
                        basin_id_to_size[basins.at(ind)] += 1;
                        found = true;
                    }
                    if( left  > me && left  != 9 && basins.at(i * len_lines + (j-1)) == 0 )
                    {
                        basins.at(i * len_lines + (j-1)) = basins.at(ind);
                        basin_id_to_size[basins.at(ind)] += 1;
                        found = true;
                    }
                    if( right > me && right != 9 && basins.at(i * len_lines + (j+1)) == 0 )
                    {
                        basins.at(i * len_lines + (j+1)) = basins.at(ind);
                        basin_id_to_size[basins.at(ind)] += 1;
                        found = true;
                    }
                }
            }

            for(int i = 0; i < num_lines; i ++)
            {
                for(int j = 0; j < len_lines; j++)
                {
                    printf("%5d ", basins.at(i * len_lines + j));
                }
                printf("\n");
            }
            printf("\n");
        };

        std::vector<std::pair<int, int>> temp_to_sort;
        for(auto& it : basin_id_to_size)
        {
            temp_to_sort.push_back(it);
        }
        sort(temp_to_sort.begin(), temp_to_sort.end(), compare);

        for(auto [first, second] : temp_to_sort)
        {
            std::cout << first << " " << second << std::endl;
        }

        printf("%d\n", (*(temp_to_sort.end()-1)).second * (*(temp_to_sort.end()-2)).second * (*(temp_to_sort.end()-3)).second);

    }

    return 0;
}
