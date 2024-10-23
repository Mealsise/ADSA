#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

#define edge pair<int, int>

// Parse into the matrix
void parse(vector<vector<int>> &v, string in)
{
    vector<int> currRow;
    for (int i = 0; i < (int)in.length(); i++)
    {
        if (in[i] == ',')
        {
            v.push_back(currRow);
            currRow.clear();
            continue;
        }
        if (in[i] >= '0' && in[i] <= '9')
        {
            currRow.push_back(in[i] - '0');
        }
        else if (in[i] >= 'A' && in[i] <= 'Z')
        {
            currRow.push_back(in[i] - 'A');
        }
        else
        {
            currRow.push_back(in[i] - 'a' + 26);
        }
    }
    v.push_back(currRow);
    return;
}

// Debug
void printMatrix(vector<vector<int>> &v)
{
    for (int i = 0; i < (int)v.size(); i++)
    {
        for (int j = 0; j < (int)v.size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printGraph(vector<pair<int, edge>> &G)
{
    cout << endl;
    for (auto &it : G)
    {
        cout << it.first << " " << it.second.first << " " << it.second.second << endl;
    }
    cout << endl;
}

void printVector(vector<int> &V)
{
    cout << endl;
    for (auto &it : V)
    {
        cout << it << " ";
    }
    cout << endl;
}

class Graph
{
private:
    vector<int> parents;
    vector<pair<int, edge>> G;
    vector<pair<int, edge>> modifiedMST;
    int nodes;

    vector<vector<int>> country;
    vector<vector<int>> build;
    vector<vector<int>> destroy;

    int cost = 0;

public:
    Graph(string in1, string in2, string in3)
    {
        parse(country, in1);
        parse(build, in2);
        parse(destroy, in3);

        nodes = country.size();
        for (int i = 0; i < nodes; i++)
        {
            parents.push_back(i);
        }
    }

    void createWeightedGraph()
    {
        // Loop through country matrix to find connections then access destroy matrix for cost
        for (int r = 0; r < (int)country.size(); r++)
        {
            // For each row i, access col i+1 bc of property of diagonal matrix
            for (int c = r + 1; c < (int)country.size(); c++)
            {
                if (country[r][c] == 1)
                {
                    G.push_back({destroy[r][c], {r, c}});
                }
            }
        }
        return;
    }

    // Recursive find
    int find_ancestor(int i)
    {
        // Base
        if (i == parents[i])
        {
            return i;
        }
        return find_ancestor(parents[i]);
    }

    // Union the sets - combine them into tree so they share ancestors
    void union_sets(int u, int v)
    {
        parents[u] = parents[v];
    }

    // Modified Kruskal algorithm
    void kruskal_first_pass()
    {
        // Use max heap to sort descending
        priority_queue<pair<int, edge>> first_pass_tree(G.begin(), G.end());

        // Create new graph with entry {destroy cost, {start, end}} - since it's undirected so start & end doesn't matter
        int u, v;

        while (!first_pass_tree.empty())
        {
            // Find the parents of the start and end nodes!!!
            u = find_ancestor(first_pass_tree.top().second.first);
            v = find_ancestor(first_pass_tree.top().second.second);

            // If not the same ancestor that means parents are of different trees, so we union the parents
            if (u != v)
            {
                modifiedMST.push_back(first_pass_tree.top());
                union_sets(u, v);
            }
            else
            {
                cost += first_pass_tree.top().first;
            }

            // Remove the top so the next max will be at the top
            first_pass_tree.pop();
        }
        return;
    }

    // Kruskal 2nd pass
    void kruskal_second_pass()
    {
        // Create a new graph that does not have connections
        G.clear();

        // Loop through country matrix to find non-connections then access build matrix for cost
        for (int r = 0; r < (int)build.size(); r++)
        {
            // For each row i, access col i+1 bc of property of diagonal matrix
            for (int c = r + 1; c < (int)build.size(); c++)
            {
                G.push_back({build[r][c], {r, c}});
            }
        }

        modifiedMST.clear();
        // Append G1 to the back of modified mst
        priority_queue<pair<int, edge>, vector<pair<int, edge>>, greater<pair<int, edge>>> pq(G.begin(), G.end());

        int u, v;
        while (!pq.empty())
        {
            // Find the parents of the start and end nodes!!!
            u = find_ancestor(pq.top().second.first);
            v = find_ancestor(pq.top().second.second);

            // If not the same ancestor that means parents are of different trees, so we union the parents
            if (u != v)
            {
                modifiedMST.push_back(pq.top());
                union_sets(u, v);

                cost += pq.top().first;
            }

            // Remove the top so the next max will be at the top
            pq.pop();
        }
        return;
    }

    // Return cost
    int get_cost()
    {
        return cost;
    }
};

int main()
{

    // get in the strings and parse them
    string in1, in2, in3;
    cin >> in1 >> in2 >> in3;

    Graph g1 = Graph(in1, in2, in3);

    g1.createWeightedGraph();

    /*
        First pass -> create a MST (max span tree? lol) that destroys the path with minimum cost
        This means, using Kruskal, sort descending, so that when we build the MST
        we build the ones with the max cost connections, leaving the min cost to be excluded
        This min cost will be the cost to destroy the route and produce a resulting MST
    */

    g1.kruskal_first_pass();

    /*
        Second pass -> build a new graph of unconnected cities to decide which roads to build,
        if the cities are not already connected. This MST will be sorted in ascending order (Min Span Tree)
        and the minimum cost to build the roads will be selected if needed
    */

    g1.kruskal_second_pass();

    cout << g1.get_cost() << endl;

    return 0;
}