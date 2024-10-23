#include <iostream>

#include <string>
#include <map>
#include <vector>
#include <queue>

#include <algorithm>

constexpr int INVALID_INPUT = -1;

int char_to_int(char ch)
{
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 26;
    return INVALID_INPUT;
}

bool char_to_bool(char ch)
{ return ch == '1'; }

bool is_row_end(char ch)
{ return ch == ','; }

void parse_grid_numeric(std::vector<std::vector<int>>& grid, const std::string& input)
{
    std::vector<int> currentRow;
    for (char ch : input)
    {
        if (is_row_end(ch))
        {
            grid.push_back(currentRow);
            currentRow.clear();
        }
        else
        {
            int number = char_to_int(ch);
            if (number != INVALID_INPUT)
            {
                currentRow.push_back(number);
            }
            else
            {
                std::cerr << "ERROR: Invalid character in input aborting program." << std::endl;
                abort();
            }
        }
    }

    if (!currentRow.empty())
    {
        grid.push_back(currentRow);
    }
}

void parse_grid_boolean(std::vector<std::vector<bool>>& grid, const std::string& input)
{
    std::vector<bool> currentRow;
    for (char ch : input)
    {
        if (is_row_end(ch))
        {
            grid.push_back(currentRow);
            currentRow.clear();
        }
        else
        {
            currentRow.push_back(char_to_bool(ch));
        }
    }

    if (!currentRow.empty())
    {
        grid.push_back(currentRow);
    }
}

void read_input(std::vector<std::vector<bool>>& countryGrid, std::vector<std::vector<int>>& buildGrid, std::vector<std::vector<int>>& destroyGrid)
{
    std::string country,   build,   destroy;
    std::cin >> country >> build >> destroy;

    int length = country.length();
    if (length != build.length() || length != destroy.length())
    {
        std::cerr << "ERROR: Input lengths do not match, aborting program." << std::endl;
        abort();
    }

    // Parse the grids
    parse_grid_boolean(countryGrid, country);
    parse_grid_numeric(buildGrid, build);
    parse_grid_numeric(destroyGrid, destroy);
}

struct Connection
{
    int node_1;
    int node_2;
};

struct Edge
{
    int weight;
    Connection connection;
};

class Graph
{
private:
    std::vector<std::vector<bool>> built_roads_grid;
    std::vector<std::vector<int>> build_cost_grid;
    std::vector<std::vector<int>> destroy_cost_grid;
    int nodes;

    std::vector<Edge> weighted_graph;
    std::vector<int> parents;
    std::vector<Edge> modified_spanning_tree;
    int total_cost;

public:
    Graph(
        std::vector<std::vector<bool>> countryGrid,
        std::vector<std::vector<int>> buildGrid,
        std::vector<std::vector<int>> destroyGrid)
        : built_roads_grid(countryGrid),
          build_cost_grid(buildGrid),
          destroy_cost_grid(destroyGrid),
          nodes(countryGrid.size() * countryGrid[0].size()),
          total_cost(0)
    {
            
        }

private:
    inline void add_edge_if_connected(int row, int col)
    {
        bool not_connected = !built_roads_grid[row][col];

        if (not_connected)
            return;

        int destroy_cost = destroy_cost_grid[row][col];
        weighted_graph.push_back({destroy_cost, {row, col}});
    }

    inline int find_ancestor(int index)
    {
        return index == parents[index] ?
            index :
            parents[index] = find_ancestor(parents[index]);
    }

    inline void union_sets(int first_node, int second_node)
    {
        int root_A = find_ancestor(first_node);
        int root_B = find_ancestor(second_node);

        if (root_A == root_B)
            return; // Already union

        parents[root_A] = root_B;
    }

    void process_edge(const Edge& current_edge)
    {
        int start_node = current_edge.connection.node_1;
        int end_node   = current_edge.connection.node_2;

        int root_start = find_ancestor(start_node);
        int root_end   = find_ancestor(end_node);

        if (root_start == root_end)
        {
            total_cost += current_edge.weight;
            return;
        }

        modified_spanning_tree.push_back(current_edge);
        union_sets(root_start, root_end);
    }

    void populate_weighted_graph_for_build()
    {
        weighted_graph.clear();

        for (int row = 0; row < nodes; row++)
        {
            for (int col = row + 1; col < nodes; col++)
            {
                int build_cost = build_cost_grid[row][col];
                weighted_graph.push_back({build_cost, {row, col}});
            }
        }
        std::sort(weighted_graph.begin(), weighted_graph.end(), [](const Edge& a, const Edge& b)
        {
            return a.weight < b.weight;
        });
    }

    void process_edge_for_second_pass(const Edge &edge)
    {
        int start_node = edge.connection.node_1;
        int end_node = edge.connection.node_2;

        int root_start = find_ancestor(start_node);
        int root_end = find_ancestor(end_node);

        if (root_start != root_end)
        {
            modified_spanning_tree.push_back(edge); 
            union_sets(root_start, root_end);
            total_cost += edge.weight;
        }
    }

public:
    void create_weighted_graph()
    {
        parents.resize(nodes);
        for (int node = 0; node < nodes; node++)
        {
            parents[node] = node;
            for (int col = node + 1; col < nodes; col++)
            {
                add_edge_if_connected(node, col);
            }
        }
    }

    void kruskal_first_pass()
    {
        std::vector<Edge> sorted_edges(weighted_graph.begin(), weighted_graph.end());
        std::sort(sorted_edges.begin(), sorted_edges.end(), [](const Edge &a, const Edge &b)
        {
            return a.weight < b.weight;
        });

        for (const Edge &edge : sorted_edges)
        {
            process_edge(edge);
        }
    }

    void kruskal_second_pass()
    {
        populate_weighted_graph_for_build();
        modified_spanning_tree.clear();

        for (const Edge& edge : weighted_graph)
        {
            process_edge_for_second_pass(edge);
        }
    }

    int get_cost()
    {
        return total_cost;
    }
};



int main()
{
    // Grids to store parsed data
    std::vector<std::vector<bool>> countryGrid;
    std::vector<std::vector<int>> buildGrid;
    std::vector<std::vector<int>> destroyGrid;

    // Read and parse input
    read_input(countryGrid, buildGrid, destroyGrid);

    // Initialise Graph
    Graph graph(countryGrid, buildGrid, destroyGrid);

    // Create Weighted
    graph.create_weighted_graph();

    // First pass
    graph.kruskal_first_pass();

    // second pass
    graph.kruskal_second_pass();

    // Print the cost of the shortest path
    std::cout << graph.get_cost() << "\n";

    return 0;
}