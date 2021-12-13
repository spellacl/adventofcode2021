#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

void update(std::map<std::string, std::vector<std::string> > adj, 
            std::string start, 
            std::string end, 
            std::map<std::string, bool> visited, int& count)
{
    if( std::all_of( start.begin(), start.end(), islower ) && start != std::string("start") && start != std::string("end") )
        visited[start] = true;

    if(start == end)
        count += 1;
    else
    {
        for(auto &neighbour : adj[start])
        {
            if(!visited[neighbour] && neighbour != std::string("start"))
            {
                std::cout << start << "->" << neighbour << std::endl;
                update(adj, neighbour, end, visited, count); 
            }
        }
    }
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        std::map<std::string, std::vector<std::string> > adj;
        std::vector<std::string> nodesList;

        while(fgets(line, sizeof(line), file))
        {
            char *token = strtok(line, "-");
            char *token2 = strtok(NULL, "-");
            std::string str(token, strlen(token));
            std::string str2(token2, strlen(token2)-1);
            adj[str].push_back(str2);
            adj[str2].push_back(str);
        };
        fclose(file);
    
        std::map<std::string, bool > visited;
        int count = 0;
        update(adj, std::string("start"), std::string("end"), visited, count);
 
        std::cout << "paths " << count << std::endl;
    }
    return 0;
}
