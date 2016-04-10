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
#define eps 1e-14
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
    point(ld _x, ld _y) {
        x = _x;
        y = _y;
    }
    point() {
        x = y = 0;
    }
    bool operator == (point b) {
        return (x == b.x && y == b.y);
    }

};



ld dist(point p1, point p2) {
    return (p1.x - p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}

void solve() {
    point c, p;
    ld r;
    cin >> c.x >> c.y >> r >> p.x >> p.y;
    ld d2 = dist(c,p);
    if(d2 < r*r - eps) {
        cout << 0 << endl;
        return;
    }

    if(abs(d2 - r*r) < eps) {
        cout << 1 << endl;
        cout << p.x << " " << p.y << endl;
        return;
    }

    cout << 2 << endl;

    ld k2 = d2 - r*r;
    ld y2 = r*r*k2/d2;
    ld x2 = k2 - y2;

    point vpc(c.x - p.x, c.y - p.y);
    ld q1 = sqrt(x2/d2);
    point p3(p.x + q1*vpc.x, p.y + q1*vpc.y);
    cout << p3.x << " " << p3.y << endl;
    cout << sqrt(x2) << " " << sqrt(y2) << endl;
    point Nvpc(-vpc.y, vpc.x);
    ld q2 = sqrt(y2/d2);
    point a1(p3.x + Nvpc.x * q2, p3.y + Nvpc.y * q2);
    point a2(p3.x - Nvpc.x * q2, p3.y - Nvpc.y * q2);
    cout << a1.x << " " << a1.y << endl;
    cout << a2.x << " " << a2.y << endl;
}

int main () {
    ios::sync_with_stdio(false);
     //freopen("input.txt", "r", stdin);
    freopen("tangent.in", "r", stdin);
    freopen("tangent.out", "w", stdout);
    cout << fixed;
    cout.precision(13);
    solve();
    return 0;
}
