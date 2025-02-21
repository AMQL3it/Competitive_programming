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
Minimum Spanning Tree (MST):
    1. Kruskal's Algorithm
    2. Prim's Algorithm
*/
///############################################################################

//----------------------------- Kruskal's Algorithm ---------------------------
/*
    time complexity: O(ElogE)
    space complexity: O(E)

    Limitations:
        1. The graph must be connected.
        2. The graph must not contain negative weights.
*/

struct Edge {
    int u, v, weight;
    bool operator<(const Edge &other) const {
        return weight < other.weight; // Sort by weight
    }
};

// Union-Find (Disjoint Set Union - DSU)
struct DSU {
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false; // Cycle detected

        // Union by rank
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

void kruskalMST(int V, vector<Edge> &edges) {
    sort(edges.begin(), edges.end()); // Sort edges by weight
    DSU dsu(V);

    vector<Edge> mst;
    int mstWeight = 0;

    for (const auto &edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mst.push_back(edge);
            mstWeight += edge.weight;
        }
    }

    // Output the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : mst) {
        cout << edge.u << " - " << edge.v << " (Weight: " << edge.weight << ")\n";
    }
    cout << "Total Weight of MST: " << mstWeight << endl;
}

//------------------------------- Prim's Algorithm ----------------------------
/*
    time complexity: O(ElogV)
    space complexity: O(V)

    Limitations:
        1. The graph must be connected.
        2. The graph must not contain negative weights.
*/

void primMST(int V, vector<Edge> &edges) {
    vector<bool> visited(V, false);
    vector<Edge> mst;
    int mstWeight = 0;

    priority_queue<Edge> pq;
    pq.push({0, 0, 0}); // Start from vertex 0

    while (!pq.empty()) {
        Edge currentEdge = pq.top();
        pq.pop();

        int u = currentEdge.u, v = currentEdge.v, weight = currentEdge.weight;

        if (visited[u] || visited[v]) continue; // Skip visited vertices

        visited[u] = visited[v] = true;
        mst.push_back(currentEdge);
        mstWeight += weight;

        for (const auto &edge : edges) {
            if (!visited[edge.u] && !visited[edge.v])
                pq.push(edge);
        }
    }

    // Output the MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (const auto &edge : mst) {
        cout << edge.u << " - " << edge.v << " (Weight: " << edge.weight << ")\n";
    }
    cout << "Total Weight of MST: " << mstWeight << endl;
}

//############################### Main Function ################################
int main()
{
    // FST_IO
    // call and testing
    int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges[i] = {u, v, weight};
    } 

    // kruskalMST(V, edges);
    // primMST(V, edges);

    return 0;
}