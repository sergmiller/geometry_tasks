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

struct pcircle{
    ll x,y,r;
    int num;
    bool left;
    pcircle(){
        x=y=0;
        left = 0;
    }
};

int n;
vector <pcircle> parts;

bool comp(const pcircle& a, const pcircle& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.left == false && b.left == true) || 
         (a.x == b.x && a.y == b.y && a.left == b.left && a.r > b.r);
}

struct classcomp{
    bool operator () (const pcircle& a, const pcircle& b) const{
         return a.y < b.y || (a.y == b.y && a.left < b.left) || (a.y == b.y && a.left == b.left && a.r < b.r) || 
         (a.y == b.y && a.left == b.left && a.r == b.r && a.x < b.x);
    }
};

void print(pcircle a) {
    cout << a.x << " " << a.y << " " << a.r << endl;
    cout << a.left << " " << endl;
    cout << "**********" << endl;
}

bool overcircle(pcircle a, pcircle b) {
    a.x += a.r;
    b.x += b.r;
    ll dist2 = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
    return dist2 <= a.r * a.r + b.r * b.r - 2 * a.r * b.r + eps;
}

ll area(pcircle a) {
    return a.r * a.r;
}

int main () {
    ios::sync_with_stdio(false);
    //freopen("input.txt", "r", stdin);
    freopen("circles.in", "r", stdin);
    freopen("circles.out", "w", stdout);
    cin >> n;
    set <pair<pll, ll> > ch;
    parts.resize(2*n);
    loop(i,n) {
        ll x,y,r;
        cin >> x >> y >> r;
        pair <pll ,ll> f = make_pair(make_pair(x,y),r);
        if(ch.find(f) == ch.end()) {
            ch.insert(f);
        } else {
            r = 0;
        }
        parts[2*i].num = parts[2*i+1].num = i;
        parts[2*i].x = x-r;
        parts[2*i].y = y;
        parts[2*i].r = r;
        parts[2*i].left = true;
        parts[2*i + 1].x = x+r;
        parts[2*i + 1].y = y;
        parts[2*i + 1].r = r;
        parts[2*i + 1].left = false;
    }

    sort(parts.begin(), parts.end(), comp);

    set <pcircle,classcomp> scan;

    vector <ll> ans_num;

    loop(i,2*n) {
        if(!parts[i].left) {
            pcircle _left = parts[i];
            _left.left = true;
            _left.x -= 2*_left.r;
            if(scan.find(_left) != scan.end()) {
                scan.erase(_left);
            }
            continue;
        }

        scan.insert(parts[i]);
        auto it = scan.find(parts[i]);
        auto l = scan.begin();
        bool fl = 0, fr = 0;
        if(it != scan.begin()) {
            --it;
            l = it;
            ++it;
            fl = true;
        }

        auto r = scan.begin();
        if(++it != scan.end()) {
            r = it;
            fr = true;
        }
        --it;

        if((fl && overcircle(*l, *it)) || (fr && overcircle(*r, *it))){
            scan.erase(it);
        } else {
            ans_num.pb((*it).r *(*it).r);
        }
    }

    ll sum = 0;
    loop(i,sz(ans_num)) {
        sum += ans_num[i];
    }

    cout<<fixed;
    cout.precision(15);
    cout << pi * (long double)sum;


    return 0;
}
