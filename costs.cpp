#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <sstream>


int charToCost(char c) {
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A';
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a';
    }
    return -1; // Invalid character
}

std::vector<std::string> splitString(const std::string &input, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, delimiter))
    {
        result.push_back(item);
    }

    return result;
}




class CostingGraph
{
private:
    std::vector<std::vector<int>> edges;
    int num_nodes;
    int initial_cost;

public:
    CostingGraph(int n) : num_nodes(n), edges(n, std::vector<int>(n, INT_MAX)), initial_cost(0) {}

    void add_edge(int start, int end, bool has_road, int build_cost, int destroy_cost)
    {
        if (has_road)
        {
            initial_cost += destroy_cost;
            build_cost = -destroy_cost;
        }

        edges[start][end] = build_cost;
        edges[end][start] = build_cost;
    }

    int find_minimal_cost()
    {
        // std::cout << "A" << std::endl;
        int found = INT_MAX;

        for (int first_choice = 0; first_choice < num_nodes; first_choice++)
        {
            int* visited = new int(num_nodes);
            visited[0] = first_choice;
            // std::cout << "First choice " << first_choice << std::endl;
            int cost = find_next_step(visited, 1, initial_cost);
            found = cost < found ? cost : found;
        }

        return found;
    }

    int find_next_step(int* visited, int count, int cost)
    {
        if (count == num_nodes)
        {
            for (int start_index = 0; start_index < count; start_index++)
                std::cout << " " << visited[start_index];
            std::cout << " " << cost << "\n ";
            return cost;
        }

        int found = INT_MAX;

        for (int end = 0; end < num_nodes; end++)
        {
            if (is_in(visited, count, end)) continue;


            for (int start_index = 0; start_index < count; start_index++)
            {
                int start = visited[start_index];
                int edge_cost = edges[start][end];
                visited[count] = end;
                int cost_ = find_next_step(visited, count+1, cost+edge_cost);
                found = cost_ < found ? cost_ : found;
            }
        }

        return found;
    }

    bool is_in(int* array, int size, int value)
    {
        for (int i = 0; i < size; i++)
        {
            if (array[i] == value)
                return true;
        }
        return false;
    }
};





int main(void)
{
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> parts = splitString(input, ' ');

    // Parse the existing roads, build costs, and destroy costs
    std::vector<std::string> existing_roads = splitString(parts[0], ',');
    std::vector<std::string> build_costs = splitString(parts[1], ',');
    std::vector<std::string> destroy_costs = splitString(parts[2], ',');

    CostingGraph cities(existing_roads.size());

    for (int x = 0; x < existing_roads.size(); x++)
    {
        for (int y = 0; y < existing_roads.size(); y++)
        {

            cities.add_edge(x, y, existing_roads[x][y]==1, charToCost(build_costs[x][y]), charToCost(destroy_costs[x][y]));
                //    addEdge(int start, int end, bool has_road, int build_cost, int destroy_cost)
        }
    }
    // cities.print_length();
    std::cout << std::endl;
    std::cout << cities.find_minimal_cost() << std::endl;
}










