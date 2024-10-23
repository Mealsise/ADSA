#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <vector>
#include <sstream>

// Function to split a string based on a delimiter
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

// Convert character to cost: 'A' to 'Z' -> 0 to 25, 'a' to 'z' -> 26 to 51
int charToCost(char c) {
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A';
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 26;
    }
    return -1; // Invalid character
}

bool containsConsecutiveChars(const std::string& path, char first, char second) {
    // Iterate through the string and check for consecutive characters
    for (size_t index = 0; index < path.length() - 1; ++index) {
        if (path[index] == first && path[index + 1] == second) {
            return true; // Found consecutive characters
        }
    }
    return false; // Consecutive characters not found
}




// class Graph {
// public:
//     struct Edge {
//         bool has_road;
//         int deconstruction_cost;
//         int build_cost;
//         int start_node; // the index to the end of the edge
//         int end_node;   // the index to the end of the edge
//     };
// private:
//     std::vector<Edge> edges;
//     int nodes;
//     int count = 0;

// public:
//     Graph(int n) :
//         nodes(n)
//         // edges(std::vector<Edge>)
//         {}
//     void print_length()
//     {
//         std::cout << "Number of nodes: " << nodes << std::endl;
//         std::cout << "Number of edges: " << count << std::endl;
//     }

//     void addEdge(int start, int end, bool has_road, int build, int destroy)
//     {
//         edges.push_back({has_road, charToCost(build), charToCost(destroy), start, end});
//         count++;
//     }

//     int findMinimalCost()
//     {
//         int min_cost = INT_MAX;

//         // Create a string containing the first 'n' characters of the alphabet
//         std::string base = "abcdefghijklmnopqrstuvwxyz";
//         base = base.substr(0, nodes);

//         // Generate all permutations of the 'base' string
//         std::sort(base.begin(), base.end());
//         do {
//             int cost = calculateCost(base);
//             if (cost < min_cost) {
//                 min_cost = cost;
//             }
//         } while (std::next_permutation(base.begin(), base.end()));

//         return min_cost;
//     }


// private:
//     int calculateCost(const std::string& path) {
//         int total_cost = 0;

//         for (const auto& edge : edges) {
//             // Check if the edge connects consecutive characters in the given path
//             bool will_be_road = containsConsecutiveChars(path, edge.start_node + 'a', edge.end_node + 'a');

//             if (will_be_road) {
//                 // If the road is needed but doesn't exist, add the build cost
//                 if (!edge.has_road) {
//                     total_cost += edge.build_cost;
//                     std::cout << "Building road: " << edge.build_cost << std::endl;
//                 }
//                 else 
//                 {
//                     std::cout << "No need to build road." << std::endl;
//                 }
//             } else {
//                 // If the road is not needed but exists, add the deconstruction cost
//                 if (edge.has_road) {
//                     total_cost += edge.deconstruction_cost;
//                     std::cout << "Destroying road: " << edge.deconstruction_cost << std::endl;
//                 }
//                 else 
//                 {
//                     std::cout << "No need to destroy road." << std::endl;
//                 }
//             }
//         }
//         std::cout << path << " : " << total_cost << std::endl;

//         return total_cost;
//     }
// };







class Graph
{
private:
    std::vector<std::vector<int>> edges;
    int num_nodes;
    int initial_cost;

public:
    Graph(int n) : num_nodes(n), edges(n, std::vector<int>(n, INT_MAX)), initial_cost(0) {}

    void addEdge(int start, int end, bool has_road, int build_cost, int destroy_cost)
    {
        if (has_road)
        {
            initial_cost += destroy_cost;
            build_cost = -destroy_cost;
        }
    edges[start][end] = build_cost;
    edges[end][start] = build_cost;
    }

    int findMinimalCost()
    {
        int found = INT_MAX;
        for (int i = 0; i < num_nodes; i++)
        {
            std::vector<int> selected = {i};
            int cost_ = find_next_step(selected, initial_cost);
            found = cost_ < found ? cost_ : found;
        }
        return found;
    }



    int find_next_step(std::vector<int> selected, int cost) {
        if (selected.size() == num_nodes) {
            std::cout << "Reached complete set: ";
            for (int node : selected) {
                std::cout << node << " ";
            }
            std::cout << "with cost: " << cost << std::endl;
            return cost; // Return this complete path's cost
        }

        std::cout << "Current selected: ";
        for (int node : selected) {
            std::cout << node << " ";
        }
        std::cout << "with current cost: " << cost << std::endl;

        int found = INT_MAX; // Start with a large value to find the minimum

        // Iterate through potential end nodes
        for (int end = 0; end < num_nodes; end++) {
            std::cout << "Checking end node: " << end << std::endl;

            if (std::find(selected.begin(), selected.end(), end) == selected.end()) {
                // If 'end' is not in the selected set
                bool valid_edge_found = false;
                for (int start : selected) {
                    if (edges[start][end] == INT_MAX) {
                        std::cout << "Skipping invalid edge (" << start << ", " << end << ")" << std::endl;
                        continue; // Skip invalid edges
                    }

                    std::cout << "Connecting " << start << " to " << end << " with edge cost: " << edges[start][end] << std::endl;

                    selected.push_back(end); // Add 'end' to the selected set
                    int new_cost = cost + edges[start][end];
                    // Recursive call to find the next step's cost
                    int cost_ = find_next_step(selected, new_cost);
                    // Update 'found' with the minimum of current 'found' and 'cost_'
                    found = std::min(found, cost_);
                    valid_edge_found = true;
                    selected.pop_back(); // Backtrack
                    std::cout << "Backtracking: removed " << end << " from selected" << std::endl;
                }

                // If no valid edges were found, continue to check other nodes
                if (!valid_edge_found) {
                    continue;
                }
            }
        }

        if (found == INT_MAX) {
            return cost;
        }


        return found; // Return the minimum cost found after all iterations
    }

};





















int main() {
    // Example input string
    std::string input;
    std::getline(std::cin, input);

    // Split the input into three parts: existing roads, build costs, and destroy costs
    std::vector<std::string> parts = splitString(input, ' ');

    // Check if input format is correct
    if (parts.size() != 3) {
        std::cerr << "Invalid input format." << std::endl;
        return 1;
    }


    // Parse the existing roads, build costs, and destroy costs
    std::vector<std::string> existing_roads = splitString(parts[0], ',');
    std::vector<std::string> build_costs = splitString(parts[1], ',');
    std::vector<std::string> destroy_costs = splitString(parts[2], ',');

    Graph cities(existing_roads.size());

    for (int x = 0; x < existing_roads.size(); x++)
    {
        for (int y = 0; y < existing_roads.size(); y++)
        {

            cities.addEdge(x, y, existing_roads[x][y]==1, charToCost(build_costs[x][y]), charToCost(destroy_costs[x][y]));
                //    addEdge(int start, int end, bool has_road, int build_cost, int destroy_cost)
        }
    }
    // cities.print_length();

    std::cout << cities.findMinimalCost() << std::endl;
}