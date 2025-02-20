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
    1. Adjacency Matrix
    2. Adjacency List
    3. Edge List
*/
///############################################################################

void Adjacency_List()
{
    ll node, edge; sli2(node, edge);

    vector<ll> adjacency_list[node];

    for(ll i = 0; i < edge; i++)
    {
        ll u, v; sli2(u,v);
        adjacency_list[u].pb(v);
        adjacency_list[v].pb(u);
    }

    // printing adjacency list
    for(ll i = 0; i < node; i++)
    {
        for(ll j = 0; j < adjacency_list[i].size(); j++)
        {
            cout << adjacency_list[i][j] << " ";
        }
        cout << nl;
    }
}

void Adjacency_Matrix()
{
    ll node, edge; sli2(node, edge);

    ll adjacency_matrix[node][node];
    
    for(ll i = 0; i < edge; i++)
    {
        ll u, v; sli2(u,v);
        adjacency_matrix[u][v] = 1;
        adjacency_matrix[v][u] = 1;
    }

    // printing adjacency matrix
    for(ll i = 0; i < node; i++)
    {
        for(ll j = 0; j < node; j++)
        {
            cout << adjacency_matrix[i][j] << " ";
        }
        cout << nl;
    }
}

void Edge_List()
{
    vector<pr> edge_list;
    ll node, edge; sli2(node, edge);
    
    for(ll i = 0; i < edge; i++)
    {
        ll u, v; sli2(u,v);
        edge_list.pb(mp(u,v));
    }

    // printing edge list
    for(ll i = 0; i < edge_list.size(); i++)
    {
        cout << edge_list[i].ff << " " << edge_list[i].ss << nl;
    }
}

//############################### Main Function ################################
int main()
{
    // FST_IO
    // call and testing

    // Adjacency_List();
    // Adjacency_Matrix();
    // Edge_List();

    return 0;
}