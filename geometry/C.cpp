nclude <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <cmath>
#include <map>
#include <set>
#define eps 1e-9
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
    point(ld _x, ld _y) {
        x = _x;
        y = _y;
    }
    point() {
        x = y = 0;
    }
};

ld det(ld x11, ld x12, ld x21, ld x22) {
    return x11*x22 - x12*x21;
}

vector <ld> get_quef(point v1, point v2) {
    ld a,b,c,d;
    a = v1.y - v2.y;
    b = v2.x - v1.x;
    c = v1.x * v2.y - v1.y * v2.x;
    vector <ld> ans;
    ans.pb(a);
    ans.pb(b);
    ans.pb(c);
    return ans;
}

ld sgnr(ld a, ld b ,ld c, point v) {
    return a*v.x + b*v.y + c;
}

ld dist(point a,point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int main () {
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    freopen("intersec2.in", "r", stdin);
    freopen("intersec2.out", "w", stdout);
    point p1,p2,p3,p4;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;

    vector <ld> quef1 = get_quef(p1,p2);
    vector <ld> quef2 = get_quef(p3,p4);

    point c1((p1.x + p2.x)/2, (p1.y+p2.y)/2);
    point c2((p3.x + p4.x)/2, (p3.y+p4.y)/2);
    ld distcen = dist(c1,c2);
    ld hsumd = (dist(p1,p2) + dist(p3,p4))/2;
    
    if(sgnr(quef1[0],quef1[1],quef1[2], p3) * sgnr(quef1[0],quef1[1],quef1[2], p4) <= 0 &&
        sgnr(quef2[0],quef2[1],quef2[2], p1) * sgnr(quef2[0],quef2[1],quef2[2], p2) <= 0 && distcen < hsumd + eps) {
        cout << "YES";
    } else {
        cout <<"NO";
    }
    return 0;
}
