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

///############################# Index Section ###############################

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

///###########################################################################

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

/*
    get bit
    set bit
    clear bit
    invert bit
    is power of 2
    lsb
    count set bit
    largest power
    generate subsets
*/

bool getBit(int x, int pos){ return x & (1 << pos); }
int setBit(int x, int pos){ return x = x | (1 << pos); }
int clearBit(int x, int pos){ return x = x & (~(1 << pos)); }

bool invertBit(int x, int pos){ return x = x ^ (1 << pos); }
bool isPowerOfTwo(int x){ return (x > 0 && !(x & (x - 1))); }
int lsb(int x){ return x = x & (-x); }

// int countSetBit(int x){ return __builtin_popcount(x); }
int countSetBit(int x){  int cnt = 0; while(x){ x = x & (x - 1); cnt++; } return cnt;}

int largestPower(int n)
{    
    /// Find the largest power of 2 less than or equal to n
    n = n | (n>>1);
    n = n | (n>>2);
    n = n | (n>>4);
    n = n | (n>>8); // for 16 bit
    n = n | (n>>16); // for 32 bit
    // n = n | (n>>32); // for 64 bit

    return (n + 1) >> 1;
}

///-------------------------- Generate Subsets -------------------------------
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

///-------------------------- GCD & LCM -------------------------------------

ll GCD(ll a, ll b){ return b == 0 ? a : GCD(b, a % b); }
ll LCM(ll a, ll b) { return (a / GCD(a, b)) * b; }

///------------------------ Big Mod & Inverse Mod ----------------------------


ll BigPower(ll b, ll p)
{
    ll res = 1;
    p = p % mod;
    //if(p==0) return 1;
    while(p)
    {
        if(p & 1) res = (res * b) % mod;
        b = (b * b) % mod;
        p = p >> 1;
    }
    return res;
}

ll Inverse_Mod(ll b)
{
    return BigMod(b, mod-2);
}

///-------------------------- Extended Euclid -------------------------------
ll gcdExtended(ll a, ll b, ll& x, ll& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;

    return d;
}

///-------------------------- Modular Inverse -------------------------------
ll modInverse(ll a)
{
    ll x, y;
    ll g = gcdExtended(a, mod, x, y);
    if (g != 1)
        return -1; // No modular inverse exists
    else
    {
        ll res = (x % mod + mod) % mod;
        return res;
    }
}

///-------------------------- Binomial Coefficient ---------------------------
ll binomialCoeff(int n, int k)
{
    ll C[n + 1][k + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= min(i, k); j++)
        {
            if (j == 0 || j == i)
                C[i][j] = 1;
            else
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    return C[n][k];
}

///-------------------------- Euler's totient function -----------------------
ll Phi_Functoin(ll n)
{
    ll ret=n;
    for(ll i=2; i*i<=n; i++)
        if(n%i==0)
        {
            while(n%i==0) n /= i;
            ret -= ret / i;
        }
    if(n>1) ret-=ret/n;
    return ret;
}

ll phi[M];
void Phi_table()
{
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= M; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= M/2; i++)
        for (int j = 2 * i; j <= M; j += i)
              phi[j] -= phi[i];
}

///-------------------------- Diophantine Check -----------------------------
bool Diophantine_Check(ll a, ll b, ll c) {
    ll x, y, g;
    g = GCD(abs(a), abs(b));
    if (c % g) {
        return false;
    }

    x *= c / g;
    y *= c / g;
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    return true;
}

///-------------------------- Matrix Exponentiation ---------------------------
vector<vector<int>> matrixMultiply(vector<vector<int>>& A, vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
                C[i][j] %= mod;
            }
        }
    }
    return C;
}

vector<vector<int>> matrixPower(vector<vector<int>>& A, ll p) {
    int n = A.size();
    vector<vector<int>> identity(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        identity[i][i] = 1;
    }
    vector<vector<int>> result = identity;
    while (p > 0) {
        if (p & 1) {
            result = matrixMultiply(result, A);
        }
        A = matrixMultiply(A, A);
        p >>= 1;
    }
    return result;
}

///-------------------------- Prime Check -----------------------------------
bool Primality(ll n)
{
    if(n < 2) return false;
    if(n == 2) return true;
    if(!(n & 1)) return false;

    for(ll i = 3; i * i <= n; i += 2)
        if(n % i == 0) return false;

    return true;
}

bool Wheel(ll n){
    bool chk = true;
    ll b[8] = {7, 11, 13, 17, 19, 23, 29, 31};
    if(n%2 == 0 || n%3 == 0 || n%5 == 0) return false;

    for(ll i = 0; i < sqrt(n); i += 30){
        for(ll j = 0; j < 8; j++){
            if(b[j]>sqrt(n)) break;
            else{
                if(n%(b[j]+i)==0){
                    chk = false;
                    break;
                }
            }
        }
        if(!chk) break;
    }
    return chk;
}

ll Carmichael_numbers[] = [561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041, 46657, 52633, 62745, 63973, 75361, 101101, 115921, 126217, 162401, 172081, 188461, 252601, 278545, 294409, 314821, 334153, 340561, 399001, 410041, 449065, 488881, 512461, 530881, 552721, 656601, 658801, 670033, 748657, 825265, 838201, 852841, 997633, 1024651, 1033669, 1050985, 1073371, 1152271, 1193221, 1461241, 1481761, 1524181, 1526815, 1621021, 1670761, 1681321, 1723681, 1880281, 1935161, 2010961, 2043169, 2063137, 2077153, 2096125, 2151529, 2193589, 2203961, 2243551, 2310625, 2366341, 2424673, 2456929, 2531845, 2730301, 2800837, 2967841, 3007121, 3034645, 3061831, 3080113, 3088969, 3113025, 3118721, 3160741, 3161761, 3244201, 3442425, 3581761, 3669073, 3828001, 3973375, 3982645, 4049137, 4086493, 4303537, 4335241, 4557601, 4562353, 4588609, 4676689, 4724461, 4866529, 5049801, 5193293, 5272853, 5295769, 5479591, 5531761, 5673601, 5887561, 6008825, 6093601, 6247753, 6424057, 6630433, 6718921, 6940369, 7217005, 7340329, 7439077, 7560193, 7779241, 7792789, 7851457, 7920385, 7958113, 8074321, 8350721, 8569705, 8617393, 8714257, 9019825, 9060469, 9364861, 9592529, 9607921, 9641857, 9902413, 9932977];

bool ProbablyPrimeFermat(ll n, int iter=5) {
    /// Fastest Primality check
    /// Work in 10^9 easily
    /// Fail in Carmichael numbers
    if (n < 4)
        return n == 2 || n == 3;

    for (ll i = 0; i < iter; i++) {
        ll a = 2 + rand() % (n - 3);
        if (BigMod(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

ll mult(ll a, ll b, ll mod) {
    ll result = 0;
    while(b){
        if(b & 1) result = (result + a) % mod;
        a=(a + a)%mod;
        b>>=1;
    }
    return result;
}

ll bigMod(ll a, ll b, ll mod) {
    ll result=1;
    while (b){
        if (b&1) result = mult(result,a,mod);
        a=mult(a,a,mod);
        b >>= 1;
    }
    return result;
}

bool check_composite(ll n, ll a, ll d, int s) {
    ll x = bigMod(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = mult(x, x, n);
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(ll n) { 
    if (n < 2) return false;
    if(n == 2) return true;
    if(!(n & 1)) return false;

    int r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

///----------------------- 7.Bitwise Sieve ---------------------------

#define M 100000000
int marked[M/64 + 2];

#define on(x) (marked[x/64] & (1<<((x%64)/2)))
#define mark(x)  marked[x/64] |= (1<<((x%64)/2))

void sieve(ll n) {
  for (ll i = 3; i * i < n; i += 2) {
    if (!on(i)) {
      for (ll j = i * i; j <= n; j += i + i) {
        mark(j);
      }
    }
  }
}
bool isPrime(ll num) {
  return num > 1 && (num == 2 || ((num & 1) && !on(num)));
}
vector<ll>ArP;
void Prime_Store()
{
    sieve(M);
    /// Store Prime 10^8
    for(ll i=2; i<=M; i++)
        if(isPrime(i)) ArP.push_back(i);
}

///-------------------------------------------------------------------

///-------------------------- 8.Segment Sieve ------------------------

ll Segment_Sieve(ll l, ll r){
    bool isPrime[r - l + 1]; //filled by true
    for (long long i = 2; i * i <= r; ++i) {
        for (long long j = max(i * i, (l + (i - 1)) / i * i); j <= r; j += i) {
            isPrime[j - l] = false;
        }
    }
    ll cnt = 0;
    for (long long i = max(l, 2); i <= r; ++i) {
        if (isPrime[i - l]) {
            cnt++;//then i is prime
        }
    }
    return cnt;
}

///-------------------------------------------------------------------

///----------------------- 9.Prime Factorization ---------------------

void Prime_Factorization(ll n)
{
    map<ll,ll>m;   // work on this line
    for(ll j=2;j*j<=n;j++) while(n%j==0) n/=j,m[j]++;
		if(n>1) m[n]++;
    map<ll,ll>::iterator it;
	for(it=m.begin(); it!=m.end(); it++)
        cout << it->first << "^" << it->second << nl;
}


vector<ll> Wheel_factoriation(ll n) {
    vector<ll> factorization;
    for (int d : {2, 3, 5}) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    int increments[8] = {4, 2, 4, 2, 4, 6, 2, 6};
    int i = 0;
    for (long long d = 7; d * d <= n; d += increments[i++]) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
        if (i == 8)
            i = 0;
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
///-------------------------------------------------------------------
ll fermat(ll n) {
    ll a = ceil(sqrt(n));
    ll b2 = a*a - n;
    ll b = round(sqrt(b2));
    while (b * b != b2) {
        a = a + 1;
        b2 = a*a - n;
        b = round(sqrt(b2));
    }
    return a - b;
}

ll pollards_p_minus_1(ll n) {
    ll B = 10;
    ll g = 1;
    while (B <= 1000000 && g < n) {
        long long a = 2 + rand() %  (n - 3);
        g = gcd(a, n);
        if (g > 1)
            return g;

        /// compute a^M
        for (ll p : primes) {
            if (p >= B)
                continue;
            long long p_power = 1;
            while (p_power * p <= B)
                p_power *= p;
            a = BigMod(a, p_power, n);

            g = gcd(a - 1, n);
            if (g > 1 && g < n)
                return g;
        }
        B *= 2;
    }
    return 1;
}


///############################################################################

int main()
{
    // FST_IO
    // call and testing

    return 0;
}

///############################### Solution ##W################################
