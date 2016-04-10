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
#define INF 1e100
#define eps 1e-15
#define pi (long double)3.14159265358979323846
#define pb push_back
#define mp make_pair
#define ft first
#define sd second
#define sz(a) a.size()
#define loop(i, n) for(long long (i) = 0; (i) < (n) ; ++ (i))
#define pii pair<int,int>
#define pll pair<long long,long long>
#define pld pair<long double, long double>
#define vii vector<int>
#define vll vector<long long> 
typedef long long ll;
typedef long double ld;

using namespace std;

/*@Sergey_Miller*/

struct point{
    ld x,y;
    point(ld _x,ld _y) {
        x = _x;
        y = _y;
    }
    point() {
        x = y = 0;
    }
};

ld dist(point v) {
    return v.x * v.x + v.y * v.y;
}

bool cmp(const pair<ld, point>& a, const pair<ld, point>& b) {
    return a.first < b.first;
}

ld scal(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

int n;

void normalize(point& v) {
    ld d = sqrt(dist(v));
    v.x /= d;
    v.y /= d;
}

ld fi_value(vector <point>& poligon, point v) {
    ld max_v = -INF, max_n = -INF, min_n = INF, min_v = INF;
    //normalize(v);
    point norm(v.y, -v.x);
    loop(i,n) {
        max_v = max(max_v, scal(v, poligon[i]));
        min_v = min(min_v, scal(v, poligon[i]));
        max_n = max(max_n, scal(norm, poligon[i]));
        min_n = min(min_n, scal(norm, poligon[i]));
    }

    ld d_v = max_v - min_v;
    ld d_n = max_n - min_n;
    return d_v * d_n;
}

point get_vect_fi(ld fi) {
    return point(cos(fi), sin(fi));
}



pld tern(ld left, ld right, vector <point>& poligon, int mod) {
    if(abs(right - left) < eps) {
        ld fi = (left + right)/2;
        ld area = fi_value(poligon, get_vect_fi(fi));
        return make_pair(fi, area);
    }
    ld m_1 = (2*left + right)/3;
    ld m_2 = (left + 2*right)/3;
    if(fi_value(poligon, get_vect_fi(m_1))*mod > fi_value(poligon, get_vect_fi(m_2))*mod) {
        return tern(left, m_2, poligon, mod);
    } else {
        return tern(m_1, right, poligon, mod);
    }
}

ld mult = 10000;

void solve() {
    vector <point> poligon(n);
    loop(i,n) {
        cin >> poligon[i].x >> poligon[i].y;
        //poligon[i].x *= mult;
        //poligon[i].y *= mult;
    }

    ld left_bound = 0;
    //ld right_bound = 2*pi;
    int numb = 10;
    ld step = (2*pi)/(3*numb);
    vector <ld> vals(numb + 1);
    ld now = left_bound;
    //ld mid_val;
    ld max_val = -INF;
    ld min_val = INF;

    vector <ld> bounds;

    loop(i,numb + 1) {
        //cout << now << " " << vals[i] << endl;
        bounds.pb(now);
        now += step;
    }
    bounds.pb(2*pi/3);

    //mid_val = (max_val + min_val)/2;
    int last_max = 0;
    int last_min = 0;
    //cout << "OK" << endl;

    now = left_bound;


    ld max_fi = -1;
    ld min_fi = -1;
    ld max_area = -INF;
    ld min_area = INF;

    loop(i, sz(bounds)-1) {
        pld data_area_max = tern(bounds[i], bounds[i+1], poligon, 1);
        pld data_area_min = tern(bounds[i], bounds[i+1], poligon, -1);
        if(data_area_max.sd > max_area) {
            max_area = data_area_max.sd;
            max_fi = data_area_max.ft;
        }

        if(data_area_min.sd < min_area) {
            min_area = data_area_min.sd;
            min_fi = data_area_min.ft;
        }
    }

    // cout << "min:" << endl;
    // cout << min_fi << " " << min_area << endl;

    // cout << "max:" << endl;
    // cout << max_fi << " " << max_area << endl;

    cout << "Minimum area = " << min_area << endl;
    cout << "Maximum area = " << max_area << endl;
    cout << endl;
}

int main () {
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    freopen("gift.in", "r", stdin);
    freopen("gift.out", "w", stdout);
    cout<<fixed;
    cout.precision(3);
    int i = 0;
    while(1) {
        ++i;
        cin >> n;
        if(!n) {
            break;
        }
        cout << "Gift " << i << endl; 
        solve();
        //break;
    }


    return 0;
}

