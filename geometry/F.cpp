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

ll vect(point v1, point v2) {
    return v1.x*v2.y - v1.y*v2.x;
}

int sgnv(point v1, point v2) {
    ll p = vect(v1,v2);
    if(p == 0) {
        return 0;
    }

    if(p > 0) {
        return 1;
    } 
    return -1;
}


int main () {
    ios::sync_with_stdio(false);
     //freopen("input.txt", "r", stdin);
      freopen("area.in", "r", stdin);
      freopen("area.out", "w", stdout);
    int n;
    cin >> n;
    vector <point> p(n);
    vector <point> v(n);
    loop(i,n) {
        cin >> p[i].x >> p[i].y;
        if(i) {
            v[i].x = p[i].x - p[i - 1].x;
            v[i].y = p[i].y - p[i - 1].y;
        }
    }

    v[0].x = p[0].x - p[n-1].x;
    v[0].y = p[0].y - p[n-1].y;

    bool l = 0, r = 0, er = 0;
    ll z;
    ll sum = 0;
    loop(i,n) {
        sum += vect(p[i], p[(i+1)%n]);
    }

    cout << ld(abs(sum))/2;
    return 0;
}
