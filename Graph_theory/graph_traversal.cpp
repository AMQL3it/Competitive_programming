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
Graph Traversal:
    1. Breadth-First Search (BFS)
        a. 1D BFS
        b. 2D BFS
        c. 3D BFS
    2.Depth-First Search (DFS)
        a. DFS using Stack
        b. DFS using Recursion
        c. DFS using Timestamp
    3. Graph Path Printing
*/
///############################################################################

#define no_nodes 1000
bool travelled[no_nodes];
ll distance[no_nodes], parent[no_nodes];
vector<ll> adjacency_list[no_nodes];

void breadthFirstSearch(ll source)
{
    queue<ll> q;
    q.push(source);
    travelled[source] = true;
    distance[source] = 0;
    parent[source] = 0; // root parent of source is become 0 or -1

    while(!q.empty())
    {
        ll u = q.front();
        q.pop();
        for(ll i = 0; i < adjacency_list[u].size(); i++)
        {
            ll v = adjacency_list[u][i];
            if(!travelled[v])
            {
                q.push(v);
                travelled[v] = true;
                distance[v] = distance[u] + 1;
                parent[v] = u;
            }
        }
    }
}

//------------------------------------ 2D BFS --------------------------------
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool travelled[no_nodes][no_nodes];
ll distance[no_nodes][no_nodes], parent[no_nodes][no_nodes];

void breadthFirstSearch_2D(ll x, ll y, ll node, ll edge)
{
    queue<pr> q;
    q.push(mp(x,y));
    travelled[x][y] = true;
    distance[x][y] = 0;
    parent[x][y] = 0; // root parent of source is become 0 or -1

    while(!q.empty())
    {
        ll u = q.front().ff;
        ll v = q.front().ss;
        q.pop();
        for(ll i = 0; i < 4; i++)
        {
            ll row = u + dx[i];
            ll col = v + dy[i];
            if(!travelled[x][y] && row >= 0 && col >= 0 && row < node && col < edge)
            {
                q.push(mp(row,col));
                travelled[row][col] = true;
                distance[row][col] = distance[u][v] + 1;
                parent[row][col] = mp(u,v);
            }
        }
    }
}

//----------------------------------- 3D BFS -----------------------------------

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

bool travelled[no_nodes][no_nodes][no_nodes];
ll distance[no_nodes][no_nodes][no_nodes], parent[no_nodes][no_nodes][no_nodes];

void breadthFirstSearch_3D(ll x, ll y, ll z, ll node, ll edge, ll height)
{
    queue<pr> q;
    q.push(mp(x,y,z));
    travelled[x][y][z] = true;
    distance[x][y][z] = 0;
    parent[x][y][z] = 0; // root parent of source is become 0 or -1

    while(!q.empty())
    {
        ll u = q.front().ff;
        ll v = q.front().ss;
        ll w = q.front().ff;
        q.pop();
        for(ll i = 0; i < 6; i++)
        {
            ll row = u + dx[i];
            ll col = v + dy[i];
            ll height = w + dz[i];
            if(!travelled[x][y][z] && row >= 0 && col >= 0 && height >= 0 && row < node && col < edge && height < height)
            {
                q.push(mp(row,col,height));
                travelled[row][col][height] = true;
                distance[row][col][height] = distance[u][v][w] + 1;
                parent[row][col][height] = mp(u,v,w);
            }
        }
    }
}

//----------------------------- DFS (Stack) -------------------------------------
void depthFirstSearch_Stack()
{
    stack<ll> s;
    s.push(source);
    travelled[source] = true;
    while(!s.empty())
    {
        ll u = s.top();
        s.pop();
        for(ll i = 0; i < adjacency_list[u].size(); i++)
        {
            ll v = adjacency_list[u][i];
            if(!travelled[v])
            {
                s.push(v);
                travelled[v] = true;
            }
        }
    }
}

//------------------------------- DFS (Recursion) -------------------------------
void depthFirstSearch_Recursion(ll u)
{
    travelled[u] = true;
    for(ll i = 0; i < adjacency_list[u].size(); i++)
    {
        ll v = adjacency_list[u][i];
        if(!travelled[v])
        {
            depthFirstSearch_Recursion(v);
        }
    }
}

//-------------------------- Depth First Search (DFS) ---------------------------
ll distance[no_nodes], parent[no_nodes], entry_time[no_nodes], exit_time[no_nodes], timestamp = 0;
vector<ll> adjacency_list[no_nodes];
void depthFirstSearch(ll v)
{
    entry_time[v] = ++timestamp;
    for(ll i = 0; i < adjacency_list[v].size(); i++)
    {
        ll u = adjacency_list[v][i];
        if(u != parent[v])
        {
            parent[u] = v;
            distance[u] = distance[v] + 1;
            DepthFirstSearch(u);
        }
    }
    exit_time[v] = ++timestamp;
}

//------------------------------- Graph Path ------------------------------------

void graphPath(ll destination)
{
    vector<ll> path;
    ll current = destination;
    while(current != -1)
    {
        path.pb(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    for(ll i = 0; i < path.size(); i++)
    {
        cout << path[i] << " ";
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