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

ld scal(point a,point b) {
    return a.x * b.x + a.y * b.y;
}

ld dist(point a) {
    return sqrt(a.x*a.x + a.y*a.y);
}



int main () {
    ios::sync_with_stdio(false);
     freopen("distance4.in", "r", stdin);
     freopen("distance4.out", "w", stdout);
    point p,v1,v2;
    cin >> p.x >> p.y >> v1.x >> v1.y >> v2.x >> v2.y;
    point vec1, vec2, vec3;
    vec1.x = p.x - v1.x;
    vec1.y = p.y - v1.y;
    vec2.x = p.x - v2.x;
    vec2.y = p.y - v2.y;
    vec3.x = v1.x - v2.x;
    vec3.y = v1.y - v2.y;
    ld ans;
    if(scal(vec2, vec3) < 0) {
        ans = dist(vec2);
    } else {
        if(scal(vec1, vec3) > 0) {
            ans = dist(vec1);
        }else {
            ld a,b,c,d;
            a = v1.y - v2.y;
            b = v2.x - v1.x;
            c = v1.x * v2.y - v1.y * v2.x;
            d = sqrt(a*a + b*b);
            a /= d;
            b /= d;
            c /= d;
            ans = abs(a * p.x + b*p.y + c);
        }
    }
    cout<<fixed;
    cout.precision(10);
    cout << ans;
    return 0;
}
