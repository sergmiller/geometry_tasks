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
#define eps 1e-12
#define pi (long double)3.1415926535
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

int n,m;
vector <point> z1;
vector <point> z2;
vector <pair <ld, point> > fi1;
vector <pair <ld, point> > fi2;
point c2;

ld dist(point v) {
    return v.x * v.x + v.y * v.y;
}

ld get_fi(point v) {
    ld r = sqrt(dist(v));
    v.x /= r;
    v.y /= r;
    if(v.x >= 0 && v.y >= 0) {
        return asin(v.y);
    }

    if(v.x >= 0 && v.y <= 0) {
        return 2*pi + asin(v.y);
    }

    if(v.x <= 0 && v.y >= 0) {
        return acos(v.x);
    }

    if(v.x <= 0 && v.y <= 0) {
        return pi + acos(-v.x);
    }
    return 0;
}

bool cmp(const pair<ld, point>& a, const pair<ld, point>& b) {
    return a.first < b.first;
}

ld scal(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

point min_vect_to_point(point p, point v1, point v2) {
    point vec1, vec2, vec3;
    vec1.x = p.x - v1.x;
    vec1.y = p.y - v1.y;
    vec2.x = p.x - v2.x;
    vec2.y = p.y - v2.y;
    vec3.x = v1.x - v2.x;
    vec3.y = v1.y - v2.y;
    ld ans;
    if(scal(vec2, vec3) < 0) {
        return vec2;
    } else {
        if(scal(vec1, vec3) > 0) {
            return vec1;
        }else {
            ld a,b,c,d;
            a = v1.y - v2.y;
            b = v2.x - v1.x;
            c = v1.x * v2.y - v1.y * v2.x;
            d = sqrt(a*a + b*b);
            a /= d;
            b /= d;
            c /= d;
            ans = a * p.x + b*p.y + c;
            return point(ans * a, ans * b);
        }
    }
}

point min_dist(point x, vector <point>& poligon) {
    ld min_d = 1e15;
    point min_v;
    loop(i,sz(poligon)) {
        point v = min_vect_to_point(x, poligon[i], poligon[(i+1)%sz(poligon)]);
        if(sqrt(dist(v)) < min_d) {
            min_d = sqrt(dist(v));
            min_v = v;
        }
    }
    return min_v;
}

ld ur(ld a, ld b, ld c, point d) {
    return a*d.x + b*d.y + c;
}

ld gA, gB, gC;

bool check(point v, point shift) {
    point intr;
    intr.x = v.x + shift.x/2;
    intr.y = v.y + shift.y/2;
    gA = shift.x;
    gB = shift.y;
    gC = -gA * intr.x -gB * intr.y;

    bool fg = false;
    bool fl = false;

    loop(i,n) {
        ld pr = ur(gA,gB,gC,z1[i]);
        if(abs(pr) < eps) {
            return false;
        }

        if(pr > 0) {
            fg = true;
        }

        if(pr < 0) {
            fl = true;
        }
    }

    if(fg && fl) {
        return false;
    }

    loop(i,m) {
        ld pr = ur(gA,gB,gC,z2[i]);
        if(abs(pr) < eps) {
            return false;
        }

        if(pr > 0 && fg) {
            return false;
        }

        if(pr < 0 && fl) {
            return false;
        }
    }

    ld d = sqrt(gA*gA + gB*gB);

    gA /= d;
    gB /= d;
    gC /= d;
    cout<<fixed;
    cout.precision(15);
    cout << gA << " " << gB << " " << gC;
    return true;
}

int main () {
    ios::sync_with_stdio(false);
    freopen("rest.in", "r", stdin);
    freopen("rest.out", "w", stdout);
    cin >> n;
    z1.resize(n);
    point c1,c2;
    loop(i,n) {
        cin >> z1[i].x >> z1[i].y;
        c1.x += z1[i].x;
        c1.y += z1[i].y;
    }

    cin >> m;
    z2.resize(m);
    fi1.resize(n);
    fi2.resize(m);
    loop(i,m) {
        cin >> z2[i].x >> z2[i].y;
        z2[i].x *= (-1);
        z2[i].y *= (-1);
        c2.x += z2[i].x;
        c2.y += z2[i].y;
    }

    c1.x /= n;
    c1.y /= n;
    c2.x /= m;
    c2.y /= m;

    loop(i,n) {
        point v;
        int j = (i+1)%n;
        v.x = z1[j].x - z1[i].x;
        v.y = z1[j].y - z1[i].y;
        fi1[i] = make_pair(get_fi(v), v);
    }


    loop(i,m) {
        point v;
        int j = (i+1)%m;
        v.x = z2[j].x - z2[i].x;
        v.y = z2[j].y - z2[i].y;
        fi2[i] = make_pair(get_fi(v), v);
    }

    sort(fi1.begin(), fi1.end(), cmp);
    sort(fi2.begin(), fi2.end(), cmp);

    vector <pair <ld, point> > fi(n+m);

    merge(fi1.begin(), fi1.begin() + n, fi2.begin(), fi2.begin() + m, fi.begin(), cmp);

    point c;
    point now;

    vector <point> mink;

    loop(i,n+m) {
        mink.pb(now);
        c.x += now.x;
        c.y += now.y;
        now.x += fi[i].sd.x;
        now.y += fi[i].sd.y;
        if(i == n + m - 1) {
            assert(now.x == 0 && now.y == 0);
        }
    }

   // cout <<"mink:" << endl;

    c.x /= (n+m);
    c.y /= (n+m);

    point v_d;
    v_d.x = - (c1.x + c2.x + c.x);
    v_d.y = - (c1.y + c2.y + c.y);

    loop(i,n+m) {
        mink[i].x += v_d.x;
        mink[i].y += v_d.y;
    }

    // loop(i,n+m) {
    //     cout <<mink[i].x << " " << mink[i].y << endl;
    // }
    // cout << "*************" << endl;


    point shift = min_dist(point(0,0), mink);

    loop(i,m) {
        z2[i].x *= (-1);
        z2[i].y *= (-1);
    }

    point p11,p12,p21,p22;
    vector <pair <ld, point> > proj1(n);
    vector <pair <ld, point> > proj2(m);

    loop(i,n) {
        proj1[i] = make_pair(scal(shift, z1[i]),z1[i]);
    }


    loop(i,m) {
        proj2[i] = make_pair(scal(shift, z2[i]),z2[i]);
    }

    sort(proj1.begin(), proj1.end(), cmp);
    sort(proj2.begin(), proj2.end(), cmp);

    p11 = proj1[0].sd;
    p12 = proj1[n-1].sd;
    p21 = proj2[0].sd;
    p22 = proj2[m-1].sd;


    point chos[4] = {p11,p12,p21,p22};
    bool fa = false;
    //cout << shift.x << " " << shift.y << endl;
    loop(i,4) {
        //cout << chos[i].x << " " << chos[i].y << endl;
        if(check(chos[i], shift)) {
            fa = true;
            break;
        }
    }

    assert(fa == true);
    return 0;
}

