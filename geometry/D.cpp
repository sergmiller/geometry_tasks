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
    ld r1,r2;
    ll x1,y1,x2,y2, rc1,rc2;
    cin >> x1 >> y1 >> rc1;
    cin >> x2 >> y2 >> rc2;
    point c1(x1,y1);
    point c2(x2,y2);
    r1 = rc1;
    r2 = rc2;
    //cin >> c1.x >> c1.y >> r1;
    //cin >> c2.x >> c2.y >> r2;
    bool f= 0;
    if(rc2 > rc1) {
        swap(r1,r2);
        swap(c1,c2);
        swap(x1,x2);
        swap(y1,y2);
        swap(rc1,rc2);
        f =  1;
    }

    ld d = dist(c1, c2);
    ll gd = (x1 - x2)*(x1 - x2) + (y1- y2)*(y1 - y2);
    point v12(c2.x - c1.x, c2.y - c1.y);

    if(gd > rc1*rc1 + rc2*rc2 + 2*rc1*rc2) {
        cout << 0 << endl;
        return;
    }

    if(gd < rc1*rc1 + rc2*rc2 - 2*rc1*rc2) {
        cout << 0 << endl;
        return;
    }

    if(gd == (rc1*rc1 + rc2*rc2 + 2*rc1*rc2)) {
        ld quef = r1*(1/(r1+r2));
        point intrs(c1.x + quef*v12.x, c1.y + quef*v12.y);
        cout << 1 << endl;
        cout << intrs.x << " " << intrs.y << endl;
        return;
    }

    if(gd == (rc1*rc1 + rc2*rc2 - 2*rc1*rc2)) {
        if(r1 == r2 && c1 == c2) {
            cout << 3 << endl;
            return;
        }
        ld quef = r1*(1/(r1 - r2));
        point intrs(c1.x + quef*v12.x, c1.y + quef*v12.y);
        cout << 1 << endl;
        cout << intrs.x << " " << intrs.y << endl;
        return;
    }

    cout << 2 << endl;

        ld len2 = ld((rc1*rc1 + gd - rc2*rc2)*(rc1*rc1 + gd - rc2*rc2))/(4*d);

        ld h2 = ld(rc1 *rc1) - len2;

        ld q = sqrt(len2/d);

        point H(c1.x + q*v12.x, c1.y + q*v12.y);

        ld q1 = sqrt(h2/d);

        point va1(H.x - v12.y * q1, H.y + v12.x * q1);
        point va2(H.x + v12.y * q1, H.y - v12.x * q1);

        cout << H.x << " " << H.y << endl;
        //cout << sqrt(len2) << " " << sqrt(h2) << endl;
        cout << (f ? abs(sqrt(d) - sqrt(len2)) : sqrt(len2)) << " " << sqrt(h2) << endl;
        cout << va1.x << " " << va1.y << endl;
        cout << va2.x << " " << va2.y << endl;
}

int main () {
    ios::sync_with_stdio(false);
     //freopen("input.txt", "r", stdin);
       freopen("intersec4.in", "r", stdin);
       freopen("intersec4.out", "w", stdout);
    ll t;
    cin >> t;
    cout<<fixed;
    cout.precision(13);
    loop(i,t) {
        solve();
    }
    return 0;
}
