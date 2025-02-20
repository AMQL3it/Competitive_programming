/******************************************************************************
 *----------------------------------------------------------------------------*
 *                                                                            *
 *        If the plan does not work, change the plan but not the goal.        *
 *----------------------------------------------------------------------------*
 *        Life is just a life. Lead it, Feel it & Enjoy It Properly.          *
 *        Nothing is impossible. Just believe in yourself & Almighty.         *
 *----------------------------------------------------------------------------*
 *                                                                            *
 *----------------------------------------------------------------------------*
 ******************************************************************************/

#include<bits/stdc++.h>
using namespace std;

///############################# Typedef Section #############################

typedef unsigned int ui;
typedef long long int ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

///############################################################################

///############################# Define Section ###############################
#define FST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define READ          freopen("in.txt","r",stdin)
#define WRITE         freopen("out.txt","w",stdout);
#define nl            "\n"
#define pi            acos(-1.0)
#define mem(arr,val)  memset(arr,val,sizeof(arr))
#define pb            push_back
#define mp            make_pair
#define pr            pair<ll,ll>
#define ff            first
#define ss            second
// #define mod           1000000007
#define INF           1e18
///############################################################################

///############################# Input Section ################################

#define si1(x)        scanf("%d",&x)
#define si2(x,y)      scanf("%d %d", &x, &y)
#define si3(x,y,z)    scanf("%d %d %d", &x, &y, &z)

#define sd1(x)        scanf("%lf",&x)
#define sd2(x,y)      scanf("%lf %lf", &x, &y)
#define sd3(x,y,z)    scanf("%lf %lf %lf", &x, &y, &z)

#define sli1(x)       scanf("%lld",&x)
#define sli2(x,y)     scanf("%lld %lld", &x, &y)
#define sli3(x,y,z)   scanf("%lld %lld %lld", &x, &y, &z)

///############################### Index Section ##############################
/*
Graph Representation:
    1. Dijkstra's Algorithm (for weighted graphs, no negative weights)
    2. Bellman-Ford Algorithm (handles negative weights)
    3. Floyd-Warshall Algorithm (all-pairs shortest paths)
    4. Johnson's Algorithm (optimized all-pairs shortest paths with negative weights) 
*/
///############################################################################

//-------------------------- Dijkstra's Algorithm -----------------------------
/*
    Time Complexity: Adjacency List + Min-Heap -> O((V+E)*logV)
    Space Complexity: O(V)

    Limitations:
        1. The graph must be connected.
        2. The graph must not contain negative weights.
*/

#define no_nodes 1000
ll distance[no_nodes], parent[no_nodes];
vector<pr> adjacency_list[no_nodes];

void dijkstra(ll source, ll node)
{
    priority_queue<ll> pq;
    pq.push(source);
    for(ll i = 0; i < node; i++) distance[i] = INF;
    distance[source] = 0;
    parent[source] = 0; // root parent of source is become 0 or -1

    while(!pq.empty())
    {
        ll u = pq.top();
        pq.pop();
        for(ll i = 0; i < adjacency_list[u].size(); i++)
        {
            ll v = adjacency_list[u][i].ff;
            ll cost = adjacency_list[u][i].ss;
            if(distance[v] > distance[u] + cost)
            {
                distance[v] = distance[u] + cost;
                parent[v] = u;
                pq.push(v);
            }
        }
    }
}

//-------------------------- Bellman-Ford Algorithm -----------------------------
/*
    Time Complexity: Adjacency List + Bellman-Ford Algorithm -> O(V*E)
    Space Complexity: O(V)

    Limitations:
        1. The graph can contain negative weights.
        2. The graph can contain cycles.
*/

struct Edge {
    long long from, to, weight; // Edge properties: start node, end node, weight
};

void bellmanFord(ll nodes, ll edges, ll startNode, const vector<Edge>& edgeList) {
    // Step 1: Initialize distance and parent arrays
    vector<ll> distance(nodes + 1, INF); // Distance from startNode to each node
    vector<ll> parent(nodes + 1, -1);   // Tracks the parent node for path reconstruction

    distance[startNode] = 0; // Distance to the start node is 0

    // Step 2: Relax edges up to (nodes - 1) times
    for (ll iteration = 1; iteration <= nodes - 1; iteration++) {
        bool anyUpdate = false;

        for (const auto& edge : edgeList) {
            if (distance[edge.from] != INF && distance[edge.to] > distance[edge.from] + edge.weight) {
                distance[edge.to] = distance[edge.from] + edge.weight;
                parent[edge.to] = edge.from; // Update the parent for the current node
                anyUpdate = true;
            }
        }

        // Early stopping if no edges are updated in this iteration
        if (!anyUpdate) break;
    }

    // Step 3: Check for negative weight cycles
    for (const auto& edge : edgeList) {
        if (distance[edge.from] != INF && distance[edge.to] > distance[edge.from] + edge.weight) {
            cout << "Negative weight cycle detected!" << endl;
            return;
        }
    }

    // Step 4: Output the results
    cout << "Shortest distances from node " << startNode << ":" << endl;
    for (ll i = 1; i <= nodes; i++) {
        if (distance[i] == INF) {
            cout << "Node " << i << ": Unreachable" << endl;
        } else {
            cout << "Node " << i << ": Distance = " << distance[i] << endl;
        }
    }

    // Optionally: Output the paths
    cout << "\nPaths from " << startNode << ":" << endl;
    for (ll i = 1; i <= nodes; i++) {
        if (distance[i] != INF && i != startNode) {
            vector<ll> path;
            for (ll v = i; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());
            cout << "Path to " << i << ": ";
            for (ll v : path) cout << v << " ";
            cout << endl;
        }
    }
}


//---------------------------- Floyd-Warshall Algorithm ------------------------

/*
    Time Complexity: O(V^3)
    Space Complexity: O(V^2)
    Limitations:
        1. The graph can contain negative weights.
        2. The graph can contain cycles.
*/

ll distance[no_node][no_node];

void floydWarshall(ll node)
{
    for(ll i = 0; i < node; i++)
    {
        for(ll j = 0; j < node; j++)
        {
            distance[i][j] = (i == j) ? 0 : INF;
            for(ll k = 0; k < node; k++)
            {
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }
}

//---------------------------- Johnson's Algorithm -----------------------------
/*
    Time Complexity: O(V^2*LogV + V*E)
    Space Complexity: O(V^2)

    Limitations:
        1. The graph can contain negative weights.
        2. The graph can contain cycles.
*/

void johnsonsAlgorithm(vector<vector<tuple<int, int>>> &adj, int V) {
    // Step 1: Add a new source vertex connected to all others with weight 0
    vector<vector<tuple<int, int>>> newAdj(V + 1);
    for (int u = 0; u < V; u++) {
        for (auto [v, weight] : adj[u]) {
            newAdj[u].push_back({v, weight});
        }
        newAdj[V].push_back({u, 0});
    }

    // Step 2: Run Bellman-Ford from the new source vertex to detect negative weight cycles
    vector<int> h(V + 1, INF);
    if (!bellmanFord(newAdj, h, V + 1, V)) {
        cout << "Negative weight cycle detected. Algorithm terminated.\n";
        return;
    }

    // Step 3: Reweight the graph to ensure all weights are non-negative
    for (int u = 0; u < V; u++) {
        for (auto &[v, weight] : adj[u]) {
            weight += h[u] - h[v];
        }
    }

    // Step 4: Run Dijkstra's algorithm from each vertex
    cout << "Shortest distances between all pairs of vertices:\n";
    for (int u = 0; u < V; u++) {
        vector<int> dist(V, INF);
        dijkstra(adj, dist, V, u);

        for (int v = 0; v < V; v++) {
            if (dist[v] == INF)
                cout << "INF ";
            else
                cout << dist[v] + h[v] - h[u] << " "; // Undo the reweighting
        }
        cout << endl;
    }
}

//############################### Main Function ################################
int main()
{
    // FST_IO
    // call and testing

    ll node, edge; sli2(node, edge);

    for(ll i = 0; i < edge; i++)
    {
        ll u, v; sli2(u,v);
        adjacency_list[u].pb(v);
        adjacency_list[v].pb(u);
    }

    // call graph traversal function

    return 0;
}