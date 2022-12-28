/*

1466. Reorder Routes to Make All Paths Lead to the City Zero
Medium

There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is only one way to travel between two different cities (this network form a tree). Last year, The ministry of transport decided to orient the roads in one direction because they are too narrow.

Roads are represented by connections where connections[i] = [ai, bi] represents a road from city ai to city bi.

This year, there will be a big event in the capital (city 0), and many people want to travel to this city.

Your task consists of reorienting some roads such that each city can visit the city 0. Return the minimum number of edges changed.

It's guaranteed that each city can reach city 0 after reorder.



Example 1:

Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
Output: 3
Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).

Example 2:

Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
Output: 2
Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).

Example 3:

Input: n = 3, connections = [[1,0],[2,0]]
Output: 0



Constraints:

    2 <= n <= 5 * 104
    connections.length == n - 1
    connections[i].length == 2
    0 <= ai, bi <= n - 1
    ai != bi


*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using EDGES = vector<vector<int>>;

class Graph
{
    EDGES edges;
    EDGES rData;
    int mNodeCnt;

    queue<int> q;
    int changedPath;
    int visitedCnt;
    vector<int> visited;

public:
    Graph(int cnt, EDGES &conn) : mNodeCnt(cnt)
    {
        edges.resize(cnt);
        rData.resize(cnt);

        for (auto a : conn)
        {
            int start = a[0];
            int end = a[1];
            edges[start].push_back(end);
            rData[end].push_back(start);
        }
        changedPath = 0;
        visitedCnt = 0;
        visited.resize(cnt, false);
    }

    void DFS(int node)
    {
        if (visitedCnt >= mNodeCnt)
            return;

        if (visited[node])
            return;

        visited[node] = true;
        visitedCnt++;

        for (auto && start : edges[node])
        {
            if (visited[start])
                continue;

            changedPath++;
            rData[node].push_back(start);
        }
        edges[node].clear();

        for (auto && x : rData[node])
        {
            DFS(x);
        }
    }
    int reroute(int startNode)
    {
        q.push(startNode);
        DFS(0);
        return changedPath;
    }
};

class Solution
{
public:
    int minReorder(int n, vector<vector<int>> &connections)
    {
        Graph g(n, connections);
        return g.reroute(0);
    }
};

int main()
{
    if (false)
    {
        cout << "*** Starting test 1" << endl;

        Solution s1;
        int cnt = 6;
        vector<vector<int>> edges = {{0, 1},
                                     {1, 3},
                                     {2, 3},
                                     {4, 0},
                                     {4, 5}};
        int result = s1.minReorder(cnt, edges);

        cout << " output (expected 3): " << result << endl;
    }
    //if (false)
    {
        cout << "*** Starting test 1" << endl;

        Solution s1;
        int cnt = 5;
        vector<vector<int>> edges = {{1, 0},
                                     {1, 2},
                                     {3, 2},
                                     {3, 4}};
        int result = s1.minReorder(cnt, edges);

        cout << " output (expected 2): " << result << endl;
    }
}
