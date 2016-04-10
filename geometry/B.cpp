#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <cmath>
#include <map>
#include <set>
#define MOD 1e9 + 7
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define sz(a) a.size()
#define loop(i, n) for(long long (i) = 0; (i) < (n) ; ++ (i))
#define pii pair<int,int>
#define pll pair<long long,long long>
#define vii vector<int>
#define vll vector<long long>  
typedef long long ll;
typedef long double ld;

using namespace std;


/*@Sergey_Miller*/

struct point{
    ld x,y;
};

ld det(ld x11, ld x12, ld x21, ld x22) {
    return x11*x22 - x12*x21;
}


int main () {
    ios::sync_with_stdio(false);
    freopen("intersec1.in", "r", stdin);
    freopen("intersec1.out", "w", stdout);
    ld a1,b1,c1,a2,b2,c2;
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
    ld d = det(a1,b1,a2,b2);
    ld d1 = det(c1,b1,c2,b2);
    ld d2 = det(a1,c1,a2,c2);
    cout<<fixed;
    cout.precision(10);
    cout << -d1*(1/d) << " " << -d2*(1/d) << endl;
    return 0;
}
