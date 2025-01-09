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

///######################### Index Section ###########################

///    1.Bits Manipulation
///    2.GCD & LCM
///    3.Divisor
///    4.Primality test
///    5.Probably Prime Fermat
///    6.Miller Rabin
///    7.Bitwise Sieve
///    8.Segment Sieve
///    9.Prime Factorization
///    10.Big Mod & Inverse Mod
///    11.Extended Euclid
///    12.Euler's totient function
///    13.Matrix Exponentiation
///    14.Fast Doubling Method

///###################################################################

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
#define mod           1000000007
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

///############################################################################
///########################### Bits Manipulation ##############################

int BitSetUp(int x, int idx){ return x = x | (1<<idx); }
int BitUnSet(int x, int idx){ return x = x & (~(1<<idx)); }
bool BitCheking(int x, int idx){ return x & (1<<idx); }
bool BitToggling(int x, int idx){ return x = x ^ (1<<idx); }
bool PowerOfTwo(int x){ return (x && !(x&(x-1))); }

vector<vector<int>> generateSubsets(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> subsets;

    for (int i = 0; i < (1 << n); i++) {
        vector<int> subset;
        for (int j = 0; j < n; j++) {
            // Check if the j-th bit in i is set (1)
            if (i & (1 << j)) {
                subset.push_back(arr[j]);
            }
        }
        subsets.push_back(subset);
    }

    return subsets;
}

///############################################################################

int main()
{
    // FST_IO
    // call and testing

    return 0;
}

///############################### Solution ##W################################
