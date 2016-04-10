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
#include <cassert>
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

bool cmp(const point& a, const point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

vector <point> p;
vector <point> conv;
int n;

void convex(int step, int start) {
    stack <point> st;
    int now = start;
    st.push(p[now]);

    while(1) {
        now += step;
        if(now < 0 || now > n - 1) {
            break;
        }
        point p0 = p[now];
        while(1) {
            if(sz(st) < 2) {
                break;
            }
            point p1 = st.top();
            st.pop();
            point p2 = st.top();
            point v1(p1.x - p2.x, p1.y - p2.y);
            point v0(p0.x - p2.x, p0.y - p2.y);
            if(sgnv(v0, v1) < 0) {
                st.push(p1);
                break;
            }
        }
        st.push(p0);
    }
    while(st.size() > 1) {
        conv.pb(st.top());
        st.pop();
    }
}



int main () {
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    freopen("hull.in", "r", stdin);
    freopen("hull.out", "w", stdout);
    cin >> n;
    p.resize(n);
    loop(i,n) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p.begin(), p.end(), cmp);

    convex(1, 0);
    convex(-1, n-1);

    vector <point> ans;

    loop(i,sz(conv)) {
        int n1 = (i+1)%sz(conv);
        int n2 = (i+2)%sz(conv);
        point v1(conv[n1].x - conv[i].x, conv[n1].y - conv[i].y);
        point v2(conv[n2].x - conv[n1].x, conv[n2].y - conv[n1].y);
        if(sgnv(v1,v2)) {
            ans.pb(conv[n1]);
        }
    }
    assert(sz(ans) > 2);
    cout << sz(ans) << endl;
     // ld per = 0;
     // ld sum = 0;
    loop(i, sz(ans)) {
        //per += sqrt(dist(ans[i], ans[(i+1)%sz(ans)]));
        //sum += vect(ans[i], ans[(i+1)%sz(ans)]);
        cout << ll(ans[i].x) << " " << ll(ans[i].y) << endl;
    }

    // cout<<fixed;
    // cout.precision(10);
    // cout << per << endl;
    // cout << abs(sum/2) << endl;

    return 0;
}
